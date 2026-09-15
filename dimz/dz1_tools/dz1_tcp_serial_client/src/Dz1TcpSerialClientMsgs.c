//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientMsgs.h"

Dz1TcpSerialClientMsgDefault *Dz1TcpSerialClientMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgDefault *__internal_ret = (Dz1TcpSerialClientMsgDefault *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgDefault_delAndSetNull, (void *)&__internal_ret);

		if (dummy && (__internal_ret->dummy = Dz1u32_clone(dummy, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgDefault_del(Dz1TcpSerialClientMsgDefault *p)
{
	if (p == NULL) return;
	if (p->dummy) Dz1Free(p->dummy);
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgDefault_dump(Dz1TcpSerialClientMsgDefault *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	if (p->dummy == NULL) Dz1Thread_printf(Dz1T("dummy = NULL\n"));
	else {Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); }
}

Dz1TcpSerialClientMsgOpen *Dz1TcpSerialClientMsgOpen_new(s32_t portNum, 
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
														 void *ret, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgOpen *__internal_ret = (Dz1TcpSerialClientMsgOpen *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgOpen), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgOpen_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->portNum = portNum;
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
		__internal_ret->ret = ret;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgOpen_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgOpen_del(Dz1TcpSerialClientMsgOpen *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgOpen_dump(Dz1TcpSerialClientMsgOpen *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("portNum = ")); Dz1s32_dump(&p->portNum, tab);

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

	if (p->ret == NULL) Dz1Thread_tprintf(tab, Dz1T("ret = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("ret = %p\n"), p->ret);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialClientMsgPort *Dz1TcpSerialClientMsgPort_new(s32_t portNum, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgPort *__internal_ret = (Dz1TcpSerialClientMsgPort *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgPort), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->portNum = portNum;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgPort_del(Dz1TcpSerialClientMsgPort *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgPort_dump(Dz1TcpSerialClientMsgPort *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("portNum = ")); Dz1s32_dump(&p->portNum, tab);
}

Dz1TcpSerialClientMsgPin *Dz1TcpSerialClientMsgPin_new(s32_t portNum, Dz1SerialPinState pin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgPin *__internal_ret = (Dz1TcpSerialClientMsgPin *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgPin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->portNum = portNum;
		__internal_ret->pin = pin;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgPin_del(Dz1TcpSerialClientMsgPin *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgPin_dump(Dz1TcpSerialClientMsgPin *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("portNum = ")); Dz1s32_dump(&p->portNum, tab);

	Dz1Thread_tprintf(tab, Dz1T("pin = %s(%d)\n"), Dz1SerialPinStateStr(p->pin), p->pin);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialClientMsgChunk *Dz1TcpSerialClientMsgChunk_new(s32_t portNum, 
														   Dz1Binary *stream, 
														   ssize_t ret, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgChunk *__internal_ret = (Dz1TcpSerialClientMsgChunk *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgChunk), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgChunk_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->portNum = portNum;
		__internal_ret->stream = stream;
		__internal_ret->ret = ret;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgChunk_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgChunk_del(Dz1TcpSerialClientMsgChunk *p)
{
	if (p == NULL) return;
	if (p->stream) Dz1Binary_del(p->stream);
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgChunk_dump(Dz1TcpSerialClientMsgChunk *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("portNum = ")); Dz1s32_dump(&p->portNum, tab);

	if (p->stream == NULL) Dz1Thread_tprintf(tab, Dz1T("stream = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("stream = ")); Dz1Binary_dump(p->stream, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("ret = ")); ssize_t_dump(&p->ret, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialClientMsgSetByteConsume *Dz1TcpSerialClientMsgSetByteConsume_new(s32_t portNum, 
																			 Dz1SerialByteConsume byteConsume, 
																			 void *byteConsumeParam, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgSetByteConsume *__internal_ret = (Dz1TcpSerialClientMsgSetByteConsume *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgSetByteConsume), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgSetByteConsume_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->portNum = portNum;
		__internal_ret->byteConsume = byteConsume;
		__internal_ret->byteConsumeParam = byteConsumeParam;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgSetByteConsume_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgSetByteConsume_del(Dz1TcpSerialClientMsgSetByteConsume *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgSetByteConsume_dump(Dz1TcpSerialClientMsgSetByteConsume *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("portNum = ")); Dz1s32_dump(&p->portNum, tab);

/* Dz1SerialByteConsume isn't have dump api */

	if (p->byteConsumeParam == NULL) Dz1Thread_tprintf(tab, Dz1T("byteConsumeParam = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("byteConsumeParam = %p\n"), p->byteConsumeParam);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialClientMsgReceived *Dz1TcpSerialClientMsgReceived_new(Dz1SockAddr *peer, 
																 Dz1SockAddr *local, 
																 Dz1Binary *stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientMsgReceived *__internal_ret = (Dz1TcpSerialClientMsgReceived *)Dz1Calloc(sizeof(Dz1TcpSerialClientMsgReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->stream = stream;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientMsgReceived_del(Dz1TcpSerialClientMsgReceived *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->stream) Dz1Binary_del(p->stream);
	Dz1Free(p);
}

void Dz1TcpSerialClientMsgReceived_dump(Dz1TcpSerialClientMsgReceived *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	if (p->stream == NULL) Dz1Thread_tprintf(tab, Dz1T("stream = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("stream = ")); Dz1Binary_dump(p->stream, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

