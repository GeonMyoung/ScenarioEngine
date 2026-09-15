//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientEnv.h"

Dz1TcpSerialClientPort *Dz1TcpSerialClientPort_new(s32_t port, 
												   u32_t baud, 
												   s32_t bitPerByte, 
												   Dz1SerialParity parity, 
												   Dz1SerialStopBit stopBit, 
												   bool_t fullDuplex, 
												   Dz1SerialRTSCTS flowRTSCTS, 
												   Dz1SerialDSRDTR flowDSRDTR, 
												   Dz1SerialXONXOFF flowXONXOFF, 
												   Dz1SerialByteConsume byteConsume, 
												   void *byteConsumeParam, 
												   Dz1SerialPinChanged ringInd, 
												   void *ringIndParam, 
												   Dz1SerialPinChanged ctsChanged, 
												   void *ctsChangedParam, 
												   Dz1SerialPinChanged dsrChanged, 
												   void *dsrChangedParam, 
												   Dz1SerialException exception, 
												   void *exceptionParam, 
												   void *req_sg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientPort *__internal_ret = (Dz1TcpSerialClientPort *)Dz1Calloc(sizeof(Dz1TcpSerialClientPort), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientPort_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->baud = baud;
		__internal_ret->bitPerByte = bitPerByte;
		__internal_ret->parity = parity;
		__internal_ret->stopBit = stopBit;
		__internal_ret->fullDuplex = fullDuplex;
		__internal_ret->flowRTSCTS = flowRTSCTS;
		__internal_ret->flowDSRDTR = flowDSRDTR;
		__internal_ret->flowXONXOFF = flowXONXOFF;
		__internal_ret->byteConsume = byteConsume;
		__internal_ret->byteConsumeParam = byteConsumeParam;
		__internal_ret->ringInd = ringInd;
		__internal_ret->ringIndParam = ringIndParam;
		__internal_ret->ctsChanged = ctsChanged;
		__internal_ret->ctsChangedParam = ctsChangedParam;
		__internal_ret->dsrChanged = dsrChanged;
		__internal_ret->dsrChangedParam = dsrChangedParam;
		__internal_ret->exception = exception;
		__internal_ret->exceptionParam = exceptionParam;
		__internal_ret->req_sg = req_sg;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientPort_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientPort_del(Dz1TcpSerialClientPort *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientPort_dump(Dz1TcpSerialClientPort *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("port = ")); Dz1s32_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, Dz1T("baud = ")); Dz1u32_dump(&p->baud, tab);

	Dz1Thread_tprintf(tab, Dz1T("bitPerByte = ")); Dz1s32_dump(&p->bitPerByte, tab);

	Dz1Thread_tprintf(tab, Dz1T("parity = %s(%d)\n"), Dz1SerialParityStr(p->parity), p->parity);

	Dz1Thread_tprintf(tab, Dz1T("stopBit = %s(%d)\n"), Dz1SerialStopBitStr(p->stopBit), p->stopBit);

	Dz1Thread_tprintf(tab, Dz1T("fullDuplex = ")); Dz1Bool_dump(&p->fullDuplex, tab);

	Dz1Thread_tprintf(tab, Dz1T("flowRTSCTS = %s(%d)\n"), Dz1SerialRTSCTSStr(p->flowRTSCTS), p->flowRTSCTS);

	Dz1Thread_tprintf(tab, Dz1T("flowDSRDTR = %s(%d)\n"), Dz1SerialDSRDTRStr(p->flowDSRDTR), p->flowDSRDTR);

	Dz1Thread_tprintf(tab, Dz1T("flowXONXOFF = %s(%d)\n"), Dz1SerialXONXOFFStr(p->flowXONXOFF), p->flowXONXOFF);

/* Dz1SerialByteConsume isn't have dump api */

	if (p->byteConsumeParam == NULL) Dz1Thread_tprintf(tab, Dz1T("byteConsumeParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("byteConsumeParam = %p\n"), p->byteConsumeParam);

/* Dz1SerialPinChanged isn't have dump api */

	if (p->ringIndParam == NULL) Dz1Thread_tprintf(tab, Dz1T("ringIndParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("ringIndParam = %p\n"), p->ringIndParam);

/* Dz1SerialPinChanged isn't have dump api */

	if (p->ctsChangedParam == NULL) Dz1Thread_tprintf(tab, Dz1T("ctsChangedParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("ctsChangedParam = %p\n"), p->ctsChangedParam);

/* Dz1SerialPinChanged isn't have dump api */

	if (p->dsrChangedParam == NULL) Dz1Thread_tprintf(tab, Dz1T("dsrChangedParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("dsrChangedParam = %p\n"), p->dsrChangedParam);

/* Dz1SerialException isn't have dump api */

	if (p->exceptionParam == NULL) Dz1Thread_tprintf(tab, Dz1T("exceptionParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("exceptionParam = %p\n"), p->exceptionParam);

	if (p->req_sg == NULL) Dz1Thread_tprintf(tab, Dz1T("req_sg = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("req_sg = %p\n"), p->req_sg);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

int Dz1TcpSerialClientPort_cmp(Dz1TcpSerialClientPort *a, Dz1TcpSerialClientPort *b)
{
	int ret = 0;
	if ((ret = Dz1s32_cmp(&a->port, &b->port)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1TcpSerialClientPortList_add(Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *data)
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

static void Dz1TcpSerialClientPortList_remove(Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1TcpSerialClientPort *Dz1TcpSerialClientPortList_extract(Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key)
{
	return (Dz1TcpSerialClientPort *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TcpSerialClientPortListMkArrArg
{
	Dz1TcpSerialClientPort **arr;
	unsigned int idx;
} Dz1TcpSerialClientPortListMkArrArg;

static Dz1Error _Dz1TcpSerialClientPortList_get_array(void *ptr, Dz1TcpSerialClientPort *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSerialClientPortListMkArrArg *arg = (Dz1TcpSerialClientPortListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TcpSerialClientPort **Dz1TcpSerialClientPortList_get_array(Dz1TcpSerialClientPortList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TcpSerialClientPort **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpSerialClientPort **)Dz1Calloc(sizeof(Dz1TcpSerialClientPort *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialClientPortListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TcpSerialClientPortList_get_array, (void *)&arg);
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

static Dz1Error Dz1TcpSerialClientPortList_travelForward(Dz1TcpSerialClientPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialClientPort *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TcpSerialClientPortList_travelBackward(Dz1TcpSerialClientPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialClientPort *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TcpSerialClientPort *Dz1TcpSerialClientPortList_find(Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key)
{
	return (Dz1TcpSerialClientPort *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TcpSerialClientPortList_count(Dz1TcpSerialClientPortList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TcpSerialClientPortList *Dz1TcpSerialClientPortList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientPortList *ret = (Dz1TcpSerialClientPortList *)Dz1Calloc(sizeof(Dz1TcpSerialClientPortList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientPortList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TcpSerialClientPort_cmp,
				(Dz1DelFunc)Dz1TcpSerialClientPort_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1TcpSerialClientPortList_add;
			ret->remove = Dz1TcpSerialClientPortList_remove;
			ret->extract = Dz1TcpSerialClientPortList_extract;
			ret->get_array = Dz1TcpSerialClientPortList_get_array;
			ret->travel = Dz1TcpSerialClientPortList_travelForward;
			ret->travelForward = Dz1TcpSerialClientPortList_travelForward;
			ret->travelBackward = Dz1TcpSerialClientPortList_travelBackward;
			ret->find = Dz1TcpSerialClientPortList_find;
			ret->cmp = Dz1TcpSerialClientPort_cmp;
			ret->count = Dz1TcpSerialClientPortList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientPortList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialClientPortList_del(Dz1TcpSerialClientPortList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TcpSerialClientPortList_dump(void *ptr, Dz1TcpSerialClientPort *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int *)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1TcpSerialClientPort_dump(p, tab);
	return err;
}

void Dz1TcpSerialClientPortList_dump(Dz1TcpSerialClientPortList *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1TcpSerialClientPortList_dump, (void *)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialClientEnv *Dz1TcpSerialClientEnv_new(void *tSelf, 
												 Dz1TcpClientSocket *sock, 
												 u32_t rcvr, 
												 Dz1SocketBuf *rxBuf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientEnv *__internal_ret = (Dz1TcpSerialClientEnv *)Dz1Calloc(sizeof(Dz1TcpSerialClientEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientEnv_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->ports = Dz1TcpSerialClientPortList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->sock = sock;
			__internal_ret->rcvr = rcvr;
			__internal_ret->rxBuf = rxBuf;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientEnv_del(Dz1TcpSerialClientEnv *p)
{
	if (p == NULL) return;
	if (p->sock) Dz1TcpClientSocket_del(p->sock);
	if (p->rxBuf) Dz1SocketBuf_del(p->rxBuf);
	if (p->ports) Dz1TcpSerialClientPortList_del(p->ports);
	Dz1Free(p);
}

void Dz1TcpSerialClientEnv_dump(Dz1TcpSerialClientEnv *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->tSelf == NULL) Dz1Thread_tprintf(tab, Dz1T("tSelf = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);

	if (p->sock == NULL) Dz1Thread_tprintf(tab, Dz1T("sock = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock); /* no way to dump */ }

	Dz1Thread_tprintf(tab, Dz1T("rcvr = ")); Dz1u32_dump(&p->rcvr, tab);

	if (p->rxBuf == NULL) Dz1Thread_tprintf(tab, Dz1T("rxBuf = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("rxBuf = ")); Dz1SocketBuf_dump(p->rxBuf, tab); /* using dump func */ }

	if (p->ports == NULL) Dz1Thread_tprintf(tab, Dz1T("ports = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("ports = ")); Dz1TcpSerialClientPortList_dump(p->ports, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

