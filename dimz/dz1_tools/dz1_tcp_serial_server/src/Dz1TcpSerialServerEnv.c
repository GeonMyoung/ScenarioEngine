//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerEnv.h"

Dz1TcpSerialServerPresetPort *Dz1TcpSerialServerPresetPort_new(u32_t presetPortNum, u32_t thid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerPresetPort *__internal_ret = (Dz1TcpSerialServerPresetPort *)Dz1Calloc(sizeof(Dz1TcpSerialServerPresetPort), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPresetPort_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->presetPortNum = presetPortNum;
		__internal_ret->thid = thid;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPresetPort_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerPresetPort_del(Dz1TcpSerialServerPresetPort *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialServerPresetPort_dump(Dz1TcpSerialServerPresetPort *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("presetPortNum = ")); Dz1u32_dump(&p->presetPortNum, tab);

	Dz1Thread_tprintf(tab, Dz1T("thid = ")); Dz1u32_dump(&p->thid, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

int Dz1TcpSerialServerPresetPort_cmp(Dz1TcpSerialServerPresetPort *a, Dz1TcpSerialServerPresetPort *b)
{
	int ret = 0;
	if ((ret = Dz1u32_cmp(&a->presetPortNum, &b->presetPortNum)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1TcpSerialServerPresetPortList_add(Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *data)
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

static void Dz1TcpSerialServerPresetPortList_remove(Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1TcpSerialServerPresetPort *Dz1TcpSerialServerPresetPortList_extract(Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key)
{
	return (Dz1TcpSerialServerPresetPort *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TcpSerialServerPresetPortListMkArrArg
{
	Dz1TcpSerialServerPresetPort **arr;
	unsigned int idx;
} Dz1TcpSerialServerPresetPortListMkArrArg;

static Dz1Error _Dz1TcpSerialServerPresetPortList_get_array(void *ptr, Dz1TcpSerialServerPresetPort *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSerialServerPresetPortListMkArrArg *arg = (Dz1TcpSerialServerPresetPortListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TcpSerialServerPresetPort **Dz1TcpSerialServerPresetPortList_get_array(Dz1TcpSerialServerPresetPortList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TcpSerialServerPresetPort **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpSerialServerPresetPort **)Dz1Calloc(sizeof(Dz1TcpSerialServerPresetPort *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialServerPresetPortListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TcpSerialServerPresetPortList_get_array, (void *)&arg);
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

static Dz1Error Dz1TcpSerialServerPresetPortList_travelForward(Dz1TcpSerialServerPresetPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPresetPort *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TcpSerialServerPresetPortList_travelBackward(Dz1TcpSerialServerPresetPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPresetPort *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TcpSerialServerPresetPort *Dz1TcpSerialServerPresetPortList_find(Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key)
{
	return (Dz1TcpSerialServerPresetPort *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TcpSerialServerPresetPortList_count(Dz1TcpSerialServerPresetPortList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TcpSerialServerPresetPortList *Dz1TcpSerialServerPresetPortList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerPresetPortList *ret = (Dz1TcpSerialServerPresetPortList *)Dz1Calloc(sizeof(Dz1TcpSerialServerPresetPortList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPresetPortList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TcpSerialServerPresetPort_cmp,
				(Dz1DelFunc)Dz1TcpSerialServerPresetPort_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1TcpSerialServerPresetPortList_add;
			ret->remove = Dz1TcpSerialServerPresetPortList_remove;
			ret->extract = Dz1TcpSerialServerPresetPortList_extract;
			ret->get_array = Dz1TcpSerialServerPresetPortList_get_array;
			ret->travel = Dz1TcpSerialServerPresetPortList_travelForward;
			ret->travelForward = Dz1TcpSerialServerPresetPortList_travelForward;
			ret->travelBackward = Dz1TcpSerialServerPresetPortList_travelBackward;
			ret->find = Dz1TcpSerialServerPresetPortList_find;
			ret->cmp = Dz1TcpSerialServerPresetPort_cmp;
			ret->count = Dz1TcpSerialServerPresetPortList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPresetPortList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialServerPresetPortList_del(Dz1TcpSerialServerPresetPortList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TcpSerialServerPresetPortList_dump(void *ptr, Dz1TcpSerialServerPresetPort *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int *)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1TcpSerialServerPresetPort_dump(p, tab);
	return err;
}

void Dz1TcpSerialServerPresetPortList_dump(Dz1TcpSerialServerPresetPortList *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1TcpSerialServerPresetPortList_dump, (void *)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerSerialArg *Dz1TcpSerialServerSerialArg_new(u32_t dstQueueID, 
															 Dz1SockAddr *peer, 
															 Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerSerialArg *__internal_ret = (Dz1TcpSerialServerSerialArg *)Dz1Calloc(sizeof(Dz1TcpSerialServerSerialArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerSerialArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->dstQueueID = dstQueueID;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerSerialArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerSerialArg_del(Dz1TcpSerialServerSerialArg *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpSerialServerSerialArg_dump(Dz1TcpSerialServerSerialArg *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("dstQueueID = ")); Dz1u32_dump(&p->dstQueueID, tab);

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerSerial *Dz1TcpSerialServerSerial_new(s32_t port, 
													   void *io, 
													   Dz1TcpSerialServerSerialArg *ioArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerSerial *__internal_ret = (Dz1TcpSerialServerSerial *)Dz1Calloc(sizeof(Dz1TcpSerialServerSerial), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerSerial_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->io = io;
		__internal_ret->ioArg = ioArg;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerSerial_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerSerial_del(Dz1TcpSerialServerSerial *p)
{
	if (p == NULL) return;
	if (p->ioArg) Dz1TcpSerialServerSerialArg_del(p->ioArg);
	Dz1Free(p);
}

void Dz1TcpSerialServerSerial_dump(Dz1TcpSerialServerSerial *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("port = ")); Dz1s32_dump(&p->port, tab);

	if (p->io == NULL) Dz1Thread_tprintf(tab, Dz1T("io = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("io = %p\n"), p->io);

	if (p->ioArg == NULL) Dz1Thread_tprintf(tab, Dz1T("ioArg = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("ioArg = ")); Dz1TcpSerialServerSerialArg_dump(p->ioArg, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerSession *Dz1TcpSerialServerSession_new(Dz1SockAddr *peer, 
														 Dz1SockAddr *local, 
														 Dz1TcpClientSocket *sock, 
														 Dz1SocketBuf *rxBuf, 
														 Dz1SocketFifo2 *txFifo, 
														 bool_t isPresetPort, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerSession *__internal_ret = (Dz1TcpSerialServerSession *)Dz1Calloc(sizeof(Dz1TcpSerialServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerSession_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rxBuf = rxBuf;
		__internal_ret->txFifo = txFifo;
		__internal_ret->isPresetPort = isPresetPort;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerSession_del(Dz1TcpSerialServerSession *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->sock) Dz1TcpClientSocket_del(p->sock);
	if (p->rxBuf) Dz1SocketBuf_del(p->rxBuf);
	if (p->txFifo) Dz1SocketFifo2_del(p->txFifo);
	if (p->serial) Dz1TcpSerialServerSerial_del(p->serial);
	Dz1Free(p);
}

void Dz1TcpSerialServerSession_dump(Dz1TcpSerialServerSession *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	if (p->sock == NULL) Dz1Thread_tprintf(tab, Dz1T("sock = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock); /* no way to dump */ }

	if (p->rxBuf == NULL) Dz1Thread_tprintf(tab, Dz1T("rxBuf = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("rxBuf = ")); Dz1SocketBuf_dump(p->rxBuf, tab); /* using dump func */ }

	if (p->txFifo == NULL) Dz1Thread_tprintf(tab, Dz1T("txFifo = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("txFifo = ")); Dz1SocketFifo2_dump(p->txFifo, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("isPresetPort = ")); Dz1Bool_dump(&p->isPresetPort, tab);

	if (p->serial == NULL) Dz1Thread_tprintf(tab, Dz1T("serial = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1TcpSerialServerSerial_dump(p->serial, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

int Dz1TcpSerialServerSession_cmp(Dz1TcpSerialServerSession *a, Dz1TcpSerialServerSession *b)
{
	int ret = 0;
	if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1TcpSerialServerSessionList_add(Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *data)
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

static void Dz1TcpSerialServerSessionList_remove(Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1TcpSerialServerSession *Dz1TcpSerialServerSessionList_extract(Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key)
{
	return (Dz1TcpSerialServerSession *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TcpSerialServerSessionListMkArrArg
{
	Dz1TcpSerialServerSession **arr;
	unsigned int idx;
} Dz1TcpSerialServerSessionListMkArrArg;

static Dz1Error _Dz1TcpSerialServerSessionList_get_array(void *ptr, Dz1TcpSerialServerSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSerialServerSessionListMkArrArg *arg = (Dz1TcpSerialServerSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TcpSerialServerSession **Dz1TcpSerialServerSessionList_get_array(Dz1TcpSerialServerSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TcpSerialServerSession **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpSerialServerSession **)Dz1Calloc(sizeof(Dz1TcpSerialServerSession *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialServerSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TcpSerialServerSessionList_get_array, (void *)&arg);
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

static Dz1Error Dz1TcpSerialServerSessionList_travelForward(Dz1TcpSerialServerSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerSession *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TcpSerialServerSessionList_travelBackward(Dz1TcpSerialServerSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerSession *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TcpSerialServerSession *Dz1TcpSerialServerSessionList_find(Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key)
{
	return (Dz1TcpSerialServerSession *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TcpSerialServerSessionList_count(Dz1TcpSerialServerSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TcpSerialServerSessionList *Dz1TcpSerialServerSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerSessionList *ret = (Dz1TcpSerialServerSessionList *)Dz1Calloc(sizeof(Dz1TcpSerialServerSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TcpSerialServerSession_cmp,
				(Dz1DelFunc)Dz1TcpSerialServerSession_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1TcpSerialServerSessionList_add;
			ret->remove = Dz1TcpSerialServerSessionList_remove;
			ret->extract = Dz1TcpSerialServerSessionList_extract;
			ret->get_array = Dz1TcpSerialServerSessionList_get_array;
			ret->travel = Dz1TcpSerialServerSessionList_travelForward;
			ret->travelForward = Dz1TcpSerialServerSessionList_travelForward;
			ret->travelBackward = Dz1TcpSerialServerSessionList_travelBackward;
			ret->find = Dz1TcpSerialServerSessionList_find;
			ret->cmp = Dz1TcpSerialServerSession_cmp;
			ret->count = Dz1TcpSerialServerSessionList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialServerSessionList_del(Dz1TcpSerialServerSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TcpSerialServerSessionList_dump(void *ptr, Dz1TcpSerialServerSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int *)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1TcpSerialServerSession_dump(p, tab);
	return err;
}

void Dz1TcpSerialServerSessionList_dump(Dz1TcpSerialServerSessionList *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1TcpSerialServerSessionList_dump, (void *)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerEnv *Dz1TcpSerialServerEnv_new(void *tSelf, u32_t emulator, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerEnv *__internal_ret = (Dz1TcpSerialServerEnv *)Dz1Calloc(sizeof(Dz1TcpSerialServerEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerEnv_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->presets = Dz1TcpSerialServerPresetPortList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->sessions = Dz1TcpSerialServerSessionList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->emulator = emulator;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerEnv_del(Dz1TcpSerialServerEnv *p)
{
	if (p == NULL) return;
	if (p->presets) Dz1TcpSerialServerPresetPortList_del(p->presets);
	if (p->sessions) Dz1TcpSerialServerSessionList_del(p->sessions);
	Dz1Free(p);
}

void Dz1TcpSerialServerEnv_dump(Dz1TcpSerialServerEnv *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->tSelf == NULL) Dz1Thread_tprintf(tab, Dz1T("tSelf = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);

	Dz1Thread_tprintf(tab, Dz1T("emulator = ")); Dz1u32_dump(&p->emulator, tab);

	if (p->presets == NULL) Dz1Thread_tprintf(tab, Dz1T("presets = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("presets = ")); Dz1TcpSerialServerPresetPortList_dump(p->presets, tab); /* using dump func */ }

	if (p->sessions == NULL) Dz1Thread_tprintf(tab, Dz1T("sessions = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("sessions = ")); Dz1TcpSerialServerSessionList_dump(p->sessions, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

