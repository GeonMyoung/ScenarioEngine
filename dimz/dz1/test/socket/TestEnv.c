#include <dz1_str.h>
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "TestEnv.h"

ReceiverEntry *ReceiverEntry_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			u32_t rcvr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ReceiverEntry *__internal_ret = (ReceiverEntry *)Dz1Calloc(sizeof(ReceiverEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ReceiverEntry_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->rcvr = rcvr;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ReceiverEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ReceiverEntry_del(ReceiverEntry *p)
{
	if (!p) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void ReceiverEntry_dump(ReceiverEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	Dz1Thread_tprintf(tab, "rcvr = "); Dz1u32_dump(&p->rcvr, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

int ReceiverEntry_cmp(ReceiverEntry *a, ReceiverEntry *b)
{
	int ret = 0;
	if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else return ret;
}

static Dz1Error ReceiverList_add(ReceiverList *p, ReceiverEntry *data)
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

static void ReceiverList_remove(ReceiverList *p, ReceiverEntry *key)
{
	Dz1AATree_remove(p->storage, key);
}

static ReceiverEntry *ReceiverList_extract(ReceiverList *p, ReceiverEntry *key)
{
	return (ReceiverEntry *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error ReceiverList_travelForward(ReceiverList *p, Dz1Error (*func)(void *ptr, ReceiverEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ReceiverList_travelBackward(ReceiverList *p, Dz1Error (*func)(void *ptr, ReceiverEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ReceiverEntry *ReceiverList_find(ReceiverList *p, ReceiverEntry *key)
{
	return (ReceiverEntry *)Dz1AATree_find(p->storage, key);
}

void _ReceiverList_dump(ReceiverEntry *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		ReceiverEntry_dump(p, tab);
	}
}

ReceiverList *ReceiverList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ReceiverList *ret = (ReceiverList *)Dz1Calloc(sizeof(ReceiverList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ReceiverList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ReceiverEntry_cmp,
				(Dz1DelFunc)ReceiverEntry_del,
				(Dz1DumpFunc)_ReceiverList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = ReceiverList_add;
			ret->remove = ReceiverList_remove;
			ret->extract = ReceiverList_extract;
			ret->travel = ReceiverList_travelForward;
			ret->travelForward = ReceiverList_travelForward;
			ret->travelBackward = ReceiverList_travelBackward;
			ret->find = ReceiverList_find;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ReceiverList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ReceiverList_del(ReceiverList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void ReceiverList_dump(ReceiverList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

AcceptorEntry *AcceptorEntry_new(u16_t port, u32_t acceptor, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	AcceptorEntry *__internal_ret = (AcceptorEntry *)Dz1Calloc(sizeof(AcceptorEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(AcceptorEntry_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->acceptor = acceptor;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (AcceptorEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void AcceptorEntry_del(AcceptorEntry *p)
{
	if (!p) return;
	Dz1Free(p);
}

void AcceptorEntry_dump(AcceptorEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1u16_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, "acceptor = "); Dz1u32_dump(&p->acceptor, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

int AcceptorEntry_cmp(AcceptorEntry *a, AcceptorEntry *b)
{
	int ret = 0;
	if ((ret = (int)((a->port) - (b->port))) != 0) return ret;
	else return ret;
}

static Dz1Error AcceptorList_add(AcceptorList *p, AcceptorEntry *data)
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

static void AcceptorList_remove(AcceptorList *p, AcceptorEntry *key)
{
	Dz1AATree_remove(p->storage, key);
}

static AcceptorEntry *AcceptorList_extract(AcceptorList *p, AcceptorEntry *key)
{
	return (AcceptorEntry *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error AcceptorList_travelForward(AcceptorList *p, Dz1Error (*func)(void *ptr, AcceptorEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error AcceptorList_travelBackward(AcceptorList *p, Dz1Error (*func)(void *ptr, AcceptorEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static AcceptorEntry *AcceptorList_find(AcceptorList *p, AcceptorEntry *key)
{
	return (AcceptorEntry *)Dz1AATree_find(p->storage, key);
}

void _AcceptorList_dump(AcceptorEntry *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		AcceptorEntry_dump(p, tab);
	}
}

AcceptorList *AcceptorList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	AcceptorList *ret = (AcceptorList *)Dz1Calloc(sizeof(AcceptorList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(AcceptorList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)AcceptorEntry_cmp,
				(Dz1DelFunc)AcceptorEntry_del,
				(Dz1DumpFunc)_AcceptorList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = AcceptorList_add;
			ret->remove = AcceptorList_remove;
			ret->extract = AcceptorList_extract;
			ret->travel = AcceptorList_travelForward;
			ret->travelForward = AcceptorList_travelForward;
			ret->travelBackward = AcceptorList_travelBackward;
			ret->find = AcceptorList_find;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (AcceptorList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void AcceptorList_del(AcceptorList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void AcceptorList_dump(AcceptorList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

