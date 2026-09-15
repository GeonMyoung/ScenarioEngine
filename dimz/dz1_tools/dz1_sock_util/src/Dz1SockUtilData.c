////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1SockUtilData.h"

#include "Dz1SockUtilBulkConnector.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorArg
Dz1SockUtilAcceptorArg *Dz1SockUtilAcceptorArg_new(u32_t parentQueueID, 
												   u32_t acceptorID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilAcceptorArg *__internal_ret = (Dz1SockUtilAcceptorArg *)Dz1Calloc(sizeof(Dz1SockUtilAcceptorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilAcceptorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->parentQueueID = parentQueueID;
		__internal_ret->acceptorID = acceptorID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilAcceptorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilAcceptorArg_purge(Dz1SockUtilAcceptorArg *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilAcceptorArg_del(Dz1SockUtilAcceptorArg *p)
{
	if (p == NULL) return;
	Dz1SockUtilAcceptorArg_purge(p);
	Dz1Free(p);
}

// Dz1SockUtilAcceptorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeustIndex
static Dz1Error Dz1SockUtilBulkConnectReqeustIndex_add(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1SockUtilBulkConnectReqeust *data)
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

static bool_t Dz1SockUtilBulkConnectReqeustIndex_remove(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1SockUtilBulkConnectReqeust *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeustIndex_extract(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1SockUtilBulkConnectReqeust *key)
{
	return (Dz1SockUtilBulkConnectReqeust *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1SockUtilBulkConnectReqeustIndexMkArrArg
{
	Dz1SockUtilBulkConnectReqeust **arr;
	unsigned int idx;
} Dz1SockUtilBulkConnectReqeustIndexMkArrArg;

static Dz1Error _Dz1SockUtilBulkConnectReqeustIndex_get_array(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockUtilBulkConnectReqeustIndexMkArrArg *arg = (Dz1SockUtilBulkConnectReqeustIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1SockUtilBulkConnectReqeust **Dz1SockUtilBulkConnectReqeustIndex_get_array(Dz1SockUtilBulkConnectReqeustIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1SockUtilBulkConnectReqeust **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SockUtilBulkConnectReqeust **)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectReqeust *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockUtilBulkConnectReqeustIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1SockUtilBulkConnectReqeustIndex_get_array, (void *)&arg);
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

static Dz1Error Dz1SockUtilBulkConnectReqeustIndex_travelForward(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectReqeust *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1SockUtilBulkConnectReqeustIndex_travelBackward(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectReqeust *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeustIndex_find(Dz1SockUtilBulkConnectReqeustIndex *p, Dz1SockUtilBulkConnectReqeust *key)
{
	return (Dz1SockUtilBulkConnectReqeust *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1SockUtilBulkConnectReqeustIndex_count(Dz1SockUtilBulkConnectReqeustIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1SockUtilBulkConnectReqeustIndex *Dz1SockUtilBulkConnectReqeustIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectReqeustIndex *ret = (Dz1SockUtilBulkConnectReqeustIndex *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectReqeustIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectReqeustIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1SockUtilBulkConnectReqeust_cmp,
				(Dz1DelFunc)Dz1SockUtilBulkConnectReqeust_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1SockUtilBulkConnectReqeustIndex_count;
			ret->travel = Dz1SockUtilBulkConnectReqeustIndex_travelForward;
			ret->travelForward = Dz1SockUtilBulkConnectReqeustIndex_travelForward;
			ret->travelBackward = Dz1SockUtilBulkConnectReqeustIndex_travelBackward;
			ret->get_array = Dz1SockUtilBulkConnectReqeustIndex_get_array;
			ret->add = Dz1SockUtilBulkConnectReqeustIndex_add;
			ret->remove = Dz1SockUtilBulkConnectReqeustIndex_remove;
			ret->find = Dz1SockUtilBulkConnectReqeustIndex_find;
			ret->extract = Dz1SockUtilBulkConnectReqeustIndex_extract;
			ret->cmp = Dz1SockUtilBulkConnectReqeust_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectReqeustIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SockUtilBulkConnectReqeustIndex_purge(Dz1SockUtilBulkConnectReqeustIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1SockUtilBulkConnectReqeustIndex_del(Dz1SockUtilBulkConnectReqeustIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1SockUtilBulkConnectReqeustIndexA_dump(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1SockUtilBulkConnectReqeustA_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectReqeustIndexA_dump(Dz1SockUtilBulkConnectReqeustIndex *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectReqeustIndexA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1SockUtilBulkConnectReqeustIndexW_dump(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1SockUtilBulkConnectReqeustW_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectReqeustIndexW_dump(Dz1SockUtilBulkConnectReqeustIndex *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectReqeustIndexW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectReqeustIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeustFifo
static Dz1Error Dz1SockUtilBulkConnectReqeustFifo_add(Dz1SockUtilBulkConnectReqeustFifo *p, Dz1SockUtilBulkConnectReqeust *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeustFifo_extract(Dz1SockUtilBulkConnectReqeustFifo *p, Dz1SockUtilBulkConnectReqeust *ptr)
{
	return (Dz1SockUtilBulkConnectReqeust *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct Dz1SockUtilBulkConnectReqeustFifoMkArrArg
{
	Dz1SockUtilBulkConnectReqeust **arr;
	unsigned int idx;
} Dz1SockUtilBulkConnectReqeustFifoMkArrArg;

static Dz1Error _Dz1SockUtilBulkConnectReqeustFifo_get_array(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockUtilBulkConnectReqeustFifoMkArrArg *arg = (Dz1SockUtilBulkConnectReqeustFifoMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1SockUtilBulkConnectReqeust **Dz1SockUtilBulkConnectReqeustFifo_get_array(Dz1SockUtilBulkConnectReqeustFifo *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1SockUtilBulkConnectReqeust **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SockUtilBulkConnectReqeust **)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectReqeust *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockUtilBulkConnectReqeustFifoMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1SockUtilBulkConnectReqeustFifo_get_array, (void *)&arg);
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

static Dz1Error Dz1SockUtilBulkConnectReqeustFifo_travelForward(Dz1SockUtilBulkConnectReqeustFifo *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectReqeust *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1SockUtilBulkConnectReqeustFifo_travelBackward(Dz1SockUtilBulkConnectReqeustFifo *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectReqeust *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeustFifo_getHead(Dz1SockUtilBulkConnectReqeustFifo *p)
{
	return (Dz1SockUtilBulkConnectReqeust *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int Dz1SockUtilBulkConnectReqeustFifo_count(Dz1SockUtilBulkConnectReqeustFifo *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1SockUtilBulkConnectReqeustFifo *Dz1SockUtilBulkConnectReqeustFifo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectReqeustFifo *ret = (Dz1SockUtilBulkConnectReqeustFifo *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectReqeustFifo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectReqeustFifo_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1SockUtilBulkConnectReqeustFifo_count;
			ret->travel = Dz1SockUtilBulkConnectReqeustFifo_travelForward;
			ret->travelForward = Dz1SockUtilBulkConnectReqeustFifo_travelForward;
			ret->travelBackward = Dz1SockUtilBulkConnectReqeustFifo_travelBackward;
			ret->get_array = Dz1SockUtilBulkConnectReqeustFifo_get_array;
			ret->add = Dz1SockUtilBulkConnectReqeustFifo_add;
			ret->extract = Dz1SockUtilBulkConnectReqeustFifo_extract;
			ret->getHead = Dz1SockUtilBulkConnectReqeustFifo_getHead;
			ret->cmp = Dz1SockUtilBulkConnectReqeust_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectReqeustFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1SockUtilBulkConnectReqeustFifo_clone(void *ptr, Dz1SockUtilBulkConnectReqeust *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockUtilBulkConnectReqeustFifo *p = (Dz1SockUtilBulkConnectReqeustFifo *)ptr;
	Dz1SockUtilBulkConnectReqeust *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1SockUtilBulkConnectReqeustFifo *Dz1SockUtilBulkConnectReqeustFifo_clone(Dz1SockUtilBulkConnectReqeustFifo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectReqeustFifo *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SockUtilBulkConnectReqeustFifo_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectReqeustFifo_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1SockUtilBulkConnectReqeustFifo_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectReqeustFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SockUtilBulkConnectReqeustFifo_purge(Dz1SockUtilBulkConnectReqeustFifo *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1SockUtilBulkConnectReqeustFifo_del(Dz1SockUtilBulkConnectReqeustFifo *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1SockUtilBulkConnectReqeustFifoA_dump(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1SockUtilBulkConnectReqeustA_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectReqeustFifoA_dump(Dz1SockUtilBulkConnectReqeustFifo *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectReqeustFifoA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1SockUtilBulkConnectReqeustFifoW_dump(void *ptr, Dz1SockUtilBulkConnectReqeust *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1SockUtilBulkConnectReqeustW_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectReqeustFifoW_dump(Dz1SockUtilBulkConnectReqeustFifo *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectReqeustFifoW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectReqeustFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectingEntry
Dz1SockUtilBulkConnectingEntry *Dz1SockUtilBulkConnectingEntry_new(Dz1SockUtilBulkConnectReqeust *req/*_ref*/, 
																   u32_t thid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectingEntry *__internal_ret = (Dz1SockUtilBulkConnectingEntry *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectingEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->req = req;
		__internal_ret->thid = thid;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilBulkConnectingEntry_purge(Dz1SockUtilBulkConnectingEntry *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilBulkConnectingEntry_del(Dz1SockUtilBulkConnectingEntry *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectingEntry_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectingEntryA_dump(Dz1SockUtilBulkConnectingEntry *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "req = "); Dz1SockUtilBulkConnectReqeustA_dump(p->req, tab); 
		Dz1ThreadA_tprintf(tab, "thid = "); Dz1u32A_dump(&p->thid, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectingEntryW_dump(Dz1SockUtilBulkConnectingEntry *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"req = "); Dz1SockUtilBulkConnectReqeustW_dump(p->req, tab); 
		Dz1ThreadW_tprintf(tab, L"thid = "); Dz1u32W_dump(&p->thid, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
int Dz1SockUtilBulkConnectingEntry_cmp(Dz1SockUtilBulkConnectingEntry *a, Dz1SockUtilBulkConnectingEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->req == NULL && b->req == NULL) ret = 0;
	else if (a->req == NULL /*&& b->req != NULL*/) ret = -1;
	else if (/*a->req != NULL &&*/ b->req == NULL) ret = 1;
	else if ((ret = Dz1SockUtilBulkConnectReqeust_cmp(a->req, b->req)) != 0) { }
	return ret;
}
// Dz1SockUtilBulkConnectingEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectingList
static Dz1Error Dz1SockUtilBulkConnectingList_add(Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *data)
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

static bool_t Dz1SockUtilBulkConnectingList_remove(Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1SockUtilBulkConnectingEntry *Dz1SockUtilBulkConnectingList_extract(Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key)
{
	return (Dz1SockUtilBulkConnectingEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1SockUtilBulkConnectingListMkArrArg
{
	Dz1SockUtilBulkConnectingEntry **arr;
	unsigned int idx;
} Dz1SockUtilBulkConnectingListMkArrArg;

static Dz1Error _Dz1SockUtilBulkConnectingList_get_array(void *ptr, Dz1SockUtilBulkConnectingEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockUtilBulkConnectingListMkArrArg *arg = (Dz1SockUtilBulkConnectingListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1SockUtilBulkConnectingEntry **Dz1SockUtilBulkConnectingList_get_array(Dz1SockUtilBulkConnectingList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1SockUtilBulkConnectingEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SockUtilBulkConnectingEntry **)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectingEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockUtilBulkConnectingListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1SockUtilBulkConnectingList_get_array, (void *)&arg);
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

static Dz1Error Dz1SockUtilBulkConnectingList_travelForward(Dz1SockUtilBulkConnectingList *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectingEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1SockUtilBulkConnectingList_travelBackward(Dz1SockUtilBulkConnectingList *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectingEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1SockUtilBulkConnectingEntry *Dz1SockUtilBulkConnectingList_find(Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key)
{
	return (Dz1SockUtilBulkConnectingEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1SockUtilBulkConnectingList_count(Dz1SockUtilBulkConnectingList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1SockUtilBulkConnectingList *Dz1SockUtilBulkConnectingList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectingList *ret = (Dz1SockUtilBulkConnectingList *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectingList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectingList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1SockUtilBulkConnectingEntry_cmp,
				(Dz1DelFunc)Dz1SockUtilBulkConnectingEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1SockUtilBulkConnectingList_count;
			ret->travel = Dz1SockUtilBulkConnectingList_travelForward;
			ret->travelForward = Dz1SockUtilBulkConnectingList_travelForward;
			ret->travelBackward = Dz1SockUtilBulkConnectingList_travelBackward;
			ret->get_array = Dz1SockUtilBulkConnectingList_get_array;
			ret->add = Dz1SockUtilBulkConnectingList_add;
			ret->remove = Dz1SockUtilBulkConnectingList_remove;
			ret->find = Dz1SockUtilBulkConnectingList_find;
			ret->extract = Dz1SockUtilBulkConnectingList_extract;
			ret->cmp = Dz1SockUtilBulkConnectingEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectingList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SockUtilBulkConnectingList_purge(Dz1SockUtilBulkConnectingList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1SockUtilBulkConnectingList_del(Dz1SockUtilBulkConnectingList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1SockUtilBulkConnectingListA_dump(void *ptr, Dz1SockUtilBulkConnectingEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1SockUtilBulkConnectingEntryA_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectingListA_dump(Dz1SockUtilBulkConnectingList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectingListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1SockUtilBulkConnectingListW_dump(void *ptr, Dz1SockUtilBulkConnectingEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1SockUtilBulkConnectingEntryW_dump(p, tab);
	return err;
}

void Dz1SockUtilBulkConnectingListW_dump(Dz1SockUtilBulkConnectingList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1SockUtilBulkConnectingListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectingList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectEnv
Dz1SockUtilBulkConnectEnv *Dz1SockUtilBulkConnectEnv_new(u8_t maxConcurrency, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectEnv *__internal_ret = (Dz1SockUtilBulkConnectEnv *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectEnv_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->index = Dz1SockUtilBulkConnectReqeustIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->requestFifo = Dz1SockUtilBulkConnectReqeustFifo_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->connectingList = Dz1SockUtilBulkConnectingList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->maxConcurrency = maxConcurrency;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilBulkConnectEnv_purge(Dz1SockUtilBulkConnectEnv *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectReqeustIndex_del(p->index);
	Dz1SockUtilBulkConnectReqeustFifo_del(p->requestFifo);
	Dz1SockUtilBulkConnectingList_del(p->connectingList);
}

void Dz1SockUtilBulkConnectEnv_del(Dz1SockUtilBulkConnectEnv *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectEnv_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectEnvA_dump(Dz1SockUtilBulkConnectEnv *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "maxConcurrency = "); Dz1u8A_dump(&p->maxConcurrency, tab); 
		Dz1ThreadA_tprintf(tab, "index = "); Dz1SockUtilBulkConnectReqeustIndexA_dump(p->index, tab); 
		Dz1ThreadA_tprintf(tab, "requestFifo = "); Dz1SockUtilBulkConnectReqeustFifoA_dump(p->requestFifo, tab); 
		Dz1ThreadA_tprintf(tab, "connectingList = "); Dz1SockUtilBulkConnectingListA_dump(p->connectingList, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectEnvW_dump(Dz1SockUtilBulkConnectEnv *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"maxConcurrency = "); Dz1u8W_dump(&p->maxConcurrency, tab); 
		Dz1ThreadW_tprintf(tab, L"index = "); Dz1SockUtilBulkConnectReqeustIndexW_dump(p->index, tab); 
		Dz1ThreadW_tprintf(tab, L"requestFifo = "); Dz1SockUtilBulkConnectReqeustFifoW_dump(p->requestFifo, tab); 
		Dz1ThreadW_tprintf(tab, L"connectingList = "); Dz1SockUtilBulkConnectingListW_dump(p->connectingList, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectMsg
Dz1SockUtilBulkConnectMsg *Dz1SockUtilBulkConnectMsg_new(Dz1SockAddr *peer, 
														 Dz1TcpClientSocket *sock, 
														 Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectMsg *__internal_ret = (Dz1SockUtilBulkConnectMsg *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->sock = sock;
		__internal_ret->local = local;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilBulkConnectMsg_purge(Dz1SockUtilBulkConnectMsg *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1TcpClientSocket_del(p->sock);
	Dz1SockAddr_del(p->local);
}

void Dz1SockUtilBulkConnectMsg_del(Dz1SockUtilBulkConnectMsg *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectMsg_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectMsgA_dump(Dz1SockUtilBulkConnectMsg *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "sock = %p\n", p->sock);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectMsgW_dump(Dz1SockUtilBulkConnectMsg *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"sock = %p\n", p->sock);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectMsg
////////////////////////////////////////////////////////////////////////////////

