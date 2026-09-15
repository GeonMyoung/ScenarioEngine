#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpSerialMsgDef.h"

Dz1TcpSerialMsgOpen *Dz1TcpSerialMsgOpen_new(s32_t port, 
											 u32_t baud, 
											 Dz1SerialParity parity, 
											 Dz1SerialStopBit stopBit, 
											 bool_t fullDuplex, 
											 Dz1SerialRTSCTS flowRTSCTS, 
											 Dz1SerialDSRDTR flowDSRDTR, 
											 Dz1SerialXONXOFF flowXONXOFF, 
											 bool_t useRingInd, 
											 bool_t useCtsChanged, 
											 bool_t useDsrChanged, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgOpen *__internal_ret = (Dz1TcpSerialMsgOpen *)Dz1Calloc(sizeof(Dz1TcpSerialMsgOpen), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgOpen_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->baud = baud;
		__internal_ret->parity = parity;
		__internal_ret->stopBit = stopBit;
		__internal_ret->fullDuplex = fullDuplex;
		__internal_ret->flowRTSCTS = flowRTSCTS;
		__internal_ret->flowDSRDTR = flowDSRDTR;
		__internal_ret->flowXONXOFF = flowXONXOFF;
		__internal_ret->useRingInd = useRingInd;
		__internal_ret->useCtsChanged = useCtsChanged;
		__internal_ret->useDsrChanged = useDsrChanged;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgOpen_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialMsgOpen *Dz1TcpSerialMsgOpen_clone(Dz1TcpSerialMsgOpen *src, Dz1Error *err)
{
	Dz1TcpSerialMsgOpen *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialMsgOpen *)Dz1Calloc(sizeof(Dz1TcpSerialMsgOpen), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgOpen_delAndSetNull, (void *)&ret);

		ret->port = src->port;
		ret->baud = src->baud;
		ret->parity = src->parity;
		ret->stopBit = src->stopBit;
		ret->fullDuplex = src->fullDuplex;
		ret->flowRTSCTS = src->flowRTSCTS;
		ret->flowDSRDTR = src->flowDSRDTR;
		ret->flowXONXOFF = src->flowXONXOFF;
		ret->useRingInd = src->useRingInd;
		ret->useCtsChanged = src->useCtsChanged;
		ret->useDsrChanged = src->useDsrChanged;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgOpen_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsgOpen_del(Dz1TcpSerialMsgOpen *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialMsgOpen_dump(Dz1TcpSerialMsgOpen *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1s32_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, "baud = "); Dz1u32_dump(&p->baud, tab);

	Dz1Thread_tprintf(tab, "parity = %s(%d)\n", Dz1SerialParityStr(p->parity), p->parity);

	Dz1Thread_tprintf(tab, "stopBit = %s(%d)\n", Dz1SerialStopBitStr(p->stopBit), p->stopBit);

	Dz1Thread_tprintf(tab, "fullDuplex = "); Dz1Bool_dump(&p->fullDuplex, tab);

	Dz1Thread_tprintf(tab, "flowRTSCTS = %s(%d)\n", Dz1SerialRTSCTSStr(p->flowRTSCTS), p->flowRTSCTS);

	Dz1Thread_tprintf(tab, "flowDSRDTR = %s(%d)\n", Dz1SerialDSRDTRStr(p->flowDSRDTR), p->flowDSRDTR);

	Dz1Thread_tprintf(tab, "flowXONXOFF = %s(%d)\n", Dz1SerialXONXOFFStr(p->flowXONXOFF), p->flowXONXOFF);

	Dz1Thread_tprintf(tab, "useRingInd = "); Dz1Bool_dump(&p->useRingInd, tab);

	Dz1Thread_tprintf(tab, "useCtsChanged = "); Dz1Bool_dump(&p->useCtsChanged, tab);

	Dz1Thread_tprintf(tab, "useDsrChanged = "); Dz1Bool_dump(&p->useDsrChanged, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSerialMsgPin *Dz1TcpSerialMsgPin_new(s32_t port, Dz1SerialPinState v, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgPin *__internal_ret = (Dz1TcpSerialMsgPin *)Dz1Calloc(sizeof(Dz1TcpSerialMsgPin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgPin_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->v = v;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgPin_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialMsgPin *Dz1TcpSerialMsgPin_clone(Dz1TcpSerialMsgPin *src, Dz1Error *err)
{
	Dz1TcpSerialMsgPin *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialMsgPin *)Dz1Calloc(sizeof(Dz1TcpSerialMsgPin), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgPin_delAndSetNull, (void *)&ret);

		ret->port = src->port;
		ret->v = src->v;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgPin_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsgPin_del(Dz1TcpSerialMsgPin *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialMsgPin_dump(Dz1TcpSerialMsgPin *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1s32_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, "v = %s(%d)\n", Dz1SerialPinStateStr(p->v), p->v);

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSerialMsgPinResult *Dz1TcpSerialMsgPinResult_new(s32_t port, 
													   Dz1SerialPinState v, 
													   s32_t status, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgPinResult *__internal_ret = (Dz1TcpSerialMsgPinResult *)Dz1Calloc(sizeof(Dz1TcpSerialMsgPinResult), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgPinResult_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->v = v;
		__internal_ret->status = status;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgPinResult_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialMsgPinResult *Dz1TcpSerialMsgPinResult_clone(Dz1TcpSerialMsgPinResult *src, Dz1Error *err)
{
	Dz1TcpSerialMsgPinResult *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialMsgPinResult *)Dz1Calloc(sizeof(Dz1TcpSerialMsgPinResult), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgPinResult_delAndSetNull, (void *)&ret);

		ret->port = src->port;
		ret->v = src->v;
		ret->status = src->status;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgPinResult_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsgPinResult_del(Dz1TcpSerialMsgPinResult *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialMsgPinResult_dump(Dz1TcpSerialMsgPinResult *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1s32_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, "v = %s(%d)\n", Dz1SerialPinStateStr(p->v), p->v);

	Dz1Thread_tprintf(tab, "status = "); Dz1s32_dump(&p->status, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSerialMsgStream *Dz1TcpSerialMsgStream_new(s32_t port, Dz1Binary *stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgStream *__internal_ret = (Dz1TcpSerialMsgStream *)Dz1Calloc(sizeof(Dz1TcpSerialMsgStream), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgStream_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->stream = stream;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgStream_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialMsgStream *Dz1TcpSerialMsgStream_clone(Dz1TcpSerialMsgStream *src, Dz1Error *err)
{
	Dz1TcpSerialMsgStream *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialMsgStream *)Dz1Calloc(sizeof(Dz1TcpSerialMsgStream), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgStream_delAndSetNull, (void *)&ret);

		if (src->stream && (ret->stream = Dz1Binary_clone(src->stream, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->port = src->port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgStream_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsgStream_del(Dz1TcpSerialMsgStream *p)
{
	if (p == NULL) return;
	if (p->stream) Dz1Binary_del(p->stream);
	Dz1Free(p);
}

void Dz1TcpSerialMsgStream_dump(Dz1TcpSerialMsgStream *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1s32_dump(&p->port, tab);

	if (p->stream == NULL) Dz1Thread_tprintf(tab, "stream = NULL\n");
	else { Dz1Thread_tprintf(tab, "stream = "); Dz1Binary_dump(p->stream, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSerialMsgReply *Dz1TcpSerialMsgReply_new(s32_t port, s32_t status, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgReply *__internal_ret = (Dz1TcpSerialMsgReply *)Dz1Calloc(sizeof(Dz1TcpSerialMsgReply), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgReply_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		__internal_ret->status = status;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgReply_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialMsgReply *Dz1TcpSerialMsgReply_clone(Dz1TcpSerialMsgReply *src, Dz1Error *err)
{
	Dz1TcpSerialMsgReply *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialMsgReply *)Dz1Calloc(sizeof(Dz1TcpSerialMsgReply), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsgReply_delAndSetNull, (void *)&ret);

		ret->port = src->port;
		ret->status = src->status;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsgReply_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsgReply_del(Dz1TcpSerialMsgReply *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialMsgReply_dump(Dz1TcpSerialMsgReply *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "port = "); Dz1s32_dump(&p->port, tab);

	Dz1Thread_tprintf(tab, "status = "); Dz1s32_dump(&p->status, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

static struct Dz1TcpSerialMsgPresentMapA
{
	str_t str;
	Dz1TcpSerialMsgPresent v;
} Dz1TcpSerialMsgPresentMapA[] =
{
	{ "openPortReq", Dz1TcpSerialMsgPresent_openPortReq },
	{ "openPortRsp", Dz1TcpSerialMsgPresent_openPortRsp },
	{ "closePortReq", Dz1TcpSerialMsgPresent_closePortReq },
	{ "closePortRsp", Dz1TcpSerialMsgPresent_closePortRsp },
	{ "writePortReq", Dz1TcpSerialMsgPresent_writePortReq },
	{ "writePortRsp", Dz1TcpSerialMsgPresent_writePortRsp },
	{ "writeDoneReq", Dz1TcpSerialMsgPresent_writeDoneReq },
	{ "writeDoneRsp", Dz1TcpSerialMsgPresent_writeDoneRsp },
	{ "setRTSReq", Dz1TcpSerialMsgPresent_setRTSReq },
	{ "setRTSRsp", Dz1TcpSerialMsgPresent_setRTSRsp },
	{ "getCTSReq", Dz1TcpSerialMsgPresent_getCTSReq },
	{ "getCTSRsp", Dz1TcpSerialMsgPresent_getCTSRsp },
	{ "setDTRReq", Dz1TcpSerialMsgPresent_setDTRReq },
	{ "setDTRRsp", Dz1TcpSerialMsgPresent_setDTRRsp },
	{ "getDSRReq", Dz1TcpSerialMsgPresent_getDSRReq },
	{ "getDSRRsp", Dz1TcpSerialMsgPresent_getDSRRsp },
	{ "received", Dz1TcpSerialMsgPresent_received },
	{ "ringIndicated", Dz1TcpSerialMsgPresent_ringIndicated },
	{ "ctsChanged", Dz1TcpSerialMsgPresent_ctsChanged },
	{ "dsrChanged", Dz1TcpSerialMsgPresent_dsrChanged },
	{ NULL, Dz1TcpSerialMsgPresent_max }
};

str_t Dz1TcpSerialMsgPresentStrA(Dz1TcpSerialMsgPresent v)
{
	struct Dz1TcpSerialMsgPresentMapA *i = NULL;
	for (i = Dz1TcpSerialMsgPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpSerialMsgPresent Dz1TcpSerialMsgPresentFromStrA(str_t str)
{
	struct Dz1TcpSerialMsgPresentMapA *i = NULL;
	for (i = Dz1TcpSerialMsgPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1TcpSerialMsgPresent_max;
}

static struct Dz1TcpSerialMsgPresentMapW
{
	wstr_t str;
	Dz1TcpSerialMsgPresent v;
} Dz1TcpSerialMsgPresentMapW[] =
{
	{ L"openPortReq", Dz1TcpSerialMsgPresent_openPortReq },
	{ L"openPortRsp", Dz1TcpSerialMsgPresent_openPortRsp },
	{ L"closePortReq", Dz1TcpSerialMsgPresent_closePortReq },
	{ L"closePortRsp", Dz1TcpSerialMsgPresent_closePortRsp },
	{ L"writePortReq", Dz1TcpSerialMsgPresent_writePortReq },
	{ L"writePortRsp", Dz1TcpSerialMsgPresent_writePortRsp },
	{ L"writeDoneReq", Dz1TcpSerialMsgPresent_writeDoneReq },
	{ L"writeDoneRsp", Dz1TcpSerialMsgPresent_writeDoneRsp },
	{ L"setRTSReq", Dz1TcpSerialMsgPresent_setRTSReq },
	{ L"setRTSRsp", Dz1TcpSerialMsgPresent_setRTSRsp },
	{ L"getCTSReq", Dz1TcpSerialMsgPresent_getCTSReq },
	{ L"getCTSRsp", Dz1TcpSerialMsgPresent_getCTSRsp },
	{ L"setDTRReq", Dz1TcpSerialMsgPresent_setDTRReq },
	{ L"setDTRRsp", Dz1TcpSerialMsgPresent_setDTRRsp },
	{ L"getDSRReq", Dz1TcpSerialMsgPresent_getDSRReq },
	{ L"getDSRRsp", Dz1TcpSerialMsgPresent_getDSRRsp },
	{ L"received", Dz1TcpSerialMsgPresent_received },
	{ L"ringIndicated", Dz1TcpSerialMsgPresent_ringIndicated },
	{ L"ctsChanged", Dz1TcpSerialMsgPresent_ctsChanged },
	{ L"dsrChanged", Dz1TcpSerialMsgPresent_dsrChanged },
	{ NULL, Dz1TcpSerialMsgPresent_max }
};

wstr_t Dz1TcpSerialMsgPresentStrW(Dz1TcpSerialMsgPresent v)
{
	struct Dz1TcpSerialMsgPresentMapW *i = NULL;
	for (i = Dz1TcpSerialMsgPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpSerialMsgPresent Dz1TcpSerialMsgPresentFromStrW(wstr_t str)
{
	struct Dz1TcpSerialMsgPresentMapW *i = NULL;
	for (i = Dz1TcpSerialMsgPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1TcpSerialMsgPresent_max;
}

Dz1TcpSerialMsgPresent *Dz1TcpSerialMsgPresent_new(Dz1TcpSerialMsgPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsgPresent *__internal_ret = (Dz1TcpSerialMsgPresent *)Dz1Calloc(sizeof(Dz1TcpSerialMsgPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1TcpSerialMsgPresent_dump(Dz1TcpSerialMsgPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1TcpSerialMsgPresentStrA(*v));
}

Dz1TcpSerialMsg *Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialMsg *ret = (Dz1TcpSerialMsg *)Dz1Calloc(sizeof(Dz1TcpSerialMsg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1TcpSerialMsgPresent_openPortReq:
				ret->x.openPortReq = (Dz1TcpSerialMsgOpen *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_openPortRsp:
				ret->x.openPortRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_closePortReq:
				if (ptr) ret->x.closePortReq = *(s32_t *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_closePortRsp:
				ret->x.closePortRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_writePortReq:
				ret->x.writePortReq = (Dz1TcpSerialMsgStream *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_writePortRsp:
				ret->x.writePortRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_writeDoneReq:
				if (ptr) ret->x.writeDoneReq = *(s32_t *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_writeDoneRsp:
				ret->x.writeDoneRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_setRTSReq:
				ret->x.setRTSReq = (Dz1TcpSerialMsgPin *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_setRTSRsp:
				ret->x.setRTSRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_getCTSReq:
				if (ptr) ret->x.getCTSReq = *(s32_t *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_getCTSRsp:
				ret->x.getCTSRsp = (Dz1TcpSerialMsgPinResult *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_setDTRReq:
				ret->x.setDTRReq = (Dz1TcpSerialMsgPin *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_setDTRRsp:
				ret->x.setDTRRsp = (Dz1TcpSerialMsgReply *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_getDSRReq:
				if (ptr) ret->x.getDSRReq = *(s32_t *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_getDSRRsp:
				ret->x.getDSRRsp = (Dz1TcpSerialMsgPinResult *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_received:
				ret->x.received = (Dz1TcpSerialMsgStream *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_ringIndicated:
				ret->x.ringIndicated = (Dz1TcpSerialMsgPin *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_ctsChanged:
				ret->x.ctsChanged = (Dz1TcpSerialMsgPin *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_dsrChanged:
				ret->x.dsrChanged = (Dz1TcpSerialMsgPin *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpSerialMsgPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TcpSerialMsg *Dz1TcpSerialMsg_clone(Dz1TcpSerialMsg *src, Dz1Error *err)
{
	Dz1TcpSerialMsg *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TcpSerialMsg *)Dz1Calloc(sizeof(Dz1TcpSerialMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&ret);

		ret->present = src->present;
		switch(ret->present)
		{
			case Dz1TcpSerialMsgPresent_openPortReq:
				if (src->x.openPortReq && (ret->x.openPortReq = Dz1TcpSerialMsgOpen_clone(src->x.openPortReq, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_openPortRsp:
				if (src->x.openPortRsp && (ret->x.openPortRsp = Dz1TcpSerialMsgReply_clone(src->x.openPortRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_closePortReq:
				ret->x.closePortReq = src->x.closePortReq;
				break;
			case Dz1TcpSerialMsgPresent_closePortRsp:
				if (src->x.closePortRsp && (ret->x.closePortRsp = Dz1TcpSerialMsgReply_clone(src->x.closePortRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_writePortReq:
				if (src->x.writePortReq && (ret->x.writePortReq = Dz1TcpSerialMsgStream_clone(src->x.writePortReq, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_writePortRsp:
				if (src->x.writePortRsp && (ret->x.writePortRsp = Dz1TcpSerialMsgReply_clone(src->x.writePortRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_writeDoneReq:
				ret->x.writeDoneReq = src->x.writeDoneReq;
				break;
			case Dz1TcpSerialMsgPresent_writeDoneRsp:
				if (src->x.writeDoneRsp && (ret->x.writeDoneRsp = Dz1TcpSerialMsgReply_clone(src->x.writeDoneRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_setRTSReq:
				if (src->x.setRTSReq && (ret->x.setRTSReq = Dz1TcpSerialMsgPin_clone(src->x.setRTSReq, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_setRTSRsp:
				if (src->x.setRTSRsp && (ret->x.setRTSRsp = Dz1TcpSerialMsgReply_clone(src->x.setRTSRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_getCTSReq:
				ret->x.getCTSReq = src->x.getCTSReq;
				break;
			case Dz1TcpSerialMsgPresent_getCTSRsp:
				if (src->x.getCTSRsp && (ret->x.getCTSRsp = Dz1TcpSerialMsgPinResult_clone(src->x.getCTSRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_setDTRReq:
				if (src->x.setDTRReq && (ret->x.setDTRReq = Dz1TcpSerialMsgPin_clone(src->x.setDTRReq, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_setDTRRsp:
				if (src->x.setDTRRsp && (ret->x.setDTRRsp = Dz1TcpSerialMsgReply_clone(src->x.setDTRRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_getDSRReq:
				ret->x.getDSRReq = src->x.getDSRReq;
				break;
			case Dz1TcpSerialMsgPresent_getDSRRsp:
				if (src->x.getDSRRsp && (ret->x.getDSRRsp = Dz1TcpSerialMsgPinResult_clone(src->x.getDSRRsp, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_received:
				if (src->x.received && (ret->x.received = Dz1TcpSerialMsgStream_clone(src->x.received, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_ringIndicated:
				if (src->x.ringIndicated && (ret->x.ringIndicated = Dz1TcpSerialMsgPin_clone(src->x.ringIndicated, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_ctsChanged:
				if (src->x.ctsChanged && (ret->x.ctsChanged = Dz1TcpSerialMsgPin_clone(src->x.ctsChanged, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1TcpSerialMsgPresent_dsrChanged:
				if (src->x.dsrChanged && (ret->x.dsrChanged = Dz1TcpSerialMsgPin_clone(src->x.dsrChanged, errp)) == NULL) { ERR_OUT(errp); }
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialMsg_del(Dz1TcpSerialMsg *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1TcpSerialMsgPresent_openPortReq:
			if (p->x.openPortReq) Dz1TcpSerialMsgOpen_del(p->x.openPortReq);
			break;
		case Dz1TcpSerialMsgPresent_openPortRsp:
			if (p->x.openPortRsp) Dz1TcpSerialMsgReply_del(p->x.openPortRsp);
			break;
		case Dz1TcpSerialMsgPresent_closePortReq:
			break;
		case Dz1TcpSerialMsgPresent_closePortRsp:
			if (p->x.closePortRsp) Dz1TcpSerialMsgReply_del(p->x.closePortRsp);
			break;
		case Dz1TcpSerialMsgPresent_writePortReq:
			if (p->x.writePortReq) Dz1TcpSerialMsgStream_del(p->x.writePortReq);
			break;
		case Dz1TcpSerialMsgPresent_writePortRsp:
			if (p->x.writePortRsp) Dz1TcpSerialMsgReply_del(p->x.writePortRsp);
			break;
		case Dz1TcpSerialMsgPresent_writeDoneReq:
			break;
		case Dz1TcpSerialMsgPresent_writeDoneRsp:
			if (p->x.writeDoneRsp) Dz1TcpSerialMsgReply_del(p->x.writeDoneRsp);
			break;
		case Dz1TcpSerialMsgPresent_setRTSReq:
			if (p->x.setRTSReq) Dz1TcpSerialMsgPin_del(p->x.setRTSReq);
			break;
		case Dz1TcpSerialMsgPresent_setRTSRsp:
			if (p->x.setRTSRsp) Dz1TcpSerialMsgReply_del(p->x.setRTSRsp);
			break;
		case Dz1TcpSerialMsgPresent_getCTSReq:
			break;
		case Dz1TcpSerialMsgPresent_getCTSRsp:
			if (p->x.getCTSRsp) Dz1TcpSerialMsgPinResult_del(p->x.getCTSRsp);
			break;
		case Dz1TcpSerialMsgPresent_setDTRReq:
			if (p->x.setDTRReq) Dz1TcpSerialMsgPin_del(p->x.setDTRReq);
			break;
		case Dz1TcpSerialMsgPresent_setDTRRsp:
			if (p->x.setDTRRsp) Dz1TcpSerialMsgReply_del(p->x.setDTRRsp);
			break;
		case Dz1TcpSerialMsgPresent_getDSRReq:
			break;
		case Dz1TcpSerialMsgPresent_getDSRRsp:
			if (p->x.getDSRRsp) Dz1TcpSerialMsgPinResult_del(p->x.getDSRRsp);
			break;
		case Dz1TcpSerialMsgPresent_received:
			if (p->x.received) Dz1TcpSerialMsgStream_del(p->x.received);
			break;
		case Dz1TcpSerialMsgPresent_ringIndicated:
			if (p->x.ringIndicated) Dz1TcpSerialMsgPin_del(p->x.ringIndicated);
			break;
		case Dz1TcpSerialMsgPresent_ctsChanged:
			if (p->x.ctsChanged) Dz1TcpSerialMsgPin_del(p->x.ctsChanged);
			break;
		case Dz1TcpSerialMsgPresent_dsrChanged:
			if (p->x.dsrChanged) Dz1TcpSerialMsgPin_del(p->x.dsrChanged);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

void Dz1TcpSerialMsg_dump(Dz1TcpSerialMsg *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1TcpSerialMsgPresent_openPortReq:
			if (p->x.openPortReq == NULL) Dz1Thread_tprintf(tab, "openPortReq = NULL\n");
			else { Dz1Thread_tprintf(tab, "openPortReq = "); Dz1TcpSerialMsgOpen_dump(p->x.openPortReq, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_openPortRsp:
			if (p->x.openPortRsp == NULL) Dz1Thread_tprintf(tab, "openPortRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "openPortRsp = "); Dz1TcpSerialMsgReply_dump(p->x.openPortRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_closePortReq:
			Dz1Thread_tprintf(tab, "closePortReq = "); Dz1s32_dump(&p->x.closePortReq, tab); // Value Primitive Scalar Type
			break;
		case Dz1TcpSerialMsgPresent_closePortRsp:
			if (p->x.closePortRsp == NULL) Dz1Thread_tprintf(tab, "closePortRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "closePortRsp = "); Dz1TcpSerialMsgReply_dump(p->x.closePortRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_writePortReq:
			if (p->x.writePortReq == NULL) Dz1Thread_tprintf(tab, "writePortReq = NULL\n");
			else { Dz1Thread_tprintf(tab, "writePortReq = "); Dz1TcpSerialMsgStream_dump(p->x.writePortReq, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_writePortRsp:
			if (p->x.writePortRsp == NULL) Dz1Thread_tprintf(tab, "writePortRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "writePortRsp = "); Dz1TcpSerialMsgReply_dump(p->x.writePortRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_writeDoneReq:
			Dz1Thread_tprintf(tab, "writeDoneReq = "); Dz1s32_dump(&p->x.writeDoneReq, tab); // Value Primitive Scalar Type
			break;
		case Dz1TcpSerialMsgPresent_writeDoneRsp:
			if (p->x.writeDoneRsp == NULL) Dz1Thread_tprintf(tab, "writeDoneRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "writeDoneRsp = "); Dz1TcpSerialMsgReply_dump(p->x.writeDoneRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_setRTSReq:
			if (p->x.setRTSReq == NULL) Dz1Thread_tprintf(tab, "setRTSReq = NULL\n");
			else { Dz1Thread_tprintf(tab, "setRTSReq = "); Dz1TcpSerialMsgPin_dump(p->x.setRTSReq, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_setRTSRsp:
			if (p->x.setRTSRsp == NULL) Dz1Thread_tprintf(tab, "setRTSRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "setRTSRsp = "); Dz1TcpSerialMsgReply_dump(p->x.setRTSRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_getCTSReq:
			Dz1Thread_tprintf(tab, "getCTSReq = "); Dz1s32_dump(&p->x.getCTSReq, tab); // Value Primitive Scalar Type
			break;
		case Dz1TcpSerialMsgPresent_getCTSRsp:
			if (p->x.getCTSRsp == NULL) Dz1Thread_tprintf(tab, "getCTSRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "getCTSRsp = "); Dz1TcpSerialMsgPinResult_dump(p->x.getCTSRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_setDTRReq:
			if (p->x.setDTRReq == NULL) Dz1Thread_tprintf(tab, "setDTRReq = NULL\n");
			else { Dz1Thread_tprintf(tab, "setDTRReq = "); Dz1TcpSerialMsgPin_dump(p->x.setDTRReq, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_setDTRRsp:
			if (p->x.setDTRRsp == NULL) Dz1Thread_tprintf(tab, "setDTRRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "setDTRRsp = "); Dz1TcpSerialMsgReply_dump(p->x.setDTRRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_getDSRReq:
			Dz1Thread_tprintf(tab, "getDSRReq = "); Dz1s32_dump(&p->x.getDSRReq, tab); // Value Primitive Scalar Type
			break;
		case Dz1TcpSerialMsgPresent_getDSRRsp:
			if (p->x.getDSRRsp == NULL) Dz1Thread_tprintf(tab, "getDSRRsp = NULL\n");
			else { Dz1Thread_tprintf(tab, "getDSRRsp = "); Dz1TcpSerialMsgPinResult_dump(p->x.getDSRRsp, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_received:
			if (p->x.received == NULL) Dz1Thread_tprintf(tab, "received = NULL\n");
			else { Dz1Thread_tprintf(tab, "received = "); Dz1TcpSerialMsgStream_dump(p->x.received, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_ringIndicated:
			if (p->x.ringIndicated == NULL) Dz1Thread_tprintf(tab, "ringIndicated = NULL\n");
			else { Dz1Thread_tprintf(tab, "ringIndicated = "); Dz1TcpSerialMsgPin_dump(p->x.ringIndicated, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_ctsChanged:
			if (p->x.ctsChanged == NULL) Dz1Thread_tprintf(tab, "ctsChanged = NULL\n");
			else { Dz1Thread_tprintf(tab, "ctsChanged = "); Dz1TcpSerialMsgPin_dump(p->x.ctsChanged, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1TcpSerialMsgPresent_dsrChanged:
			if (p->x.dsrChanged == NULL) Dz1Thread_tprintf(tab, "dsrChanged = NULL\n");
			else { Dz1Thread_tprintf(tab, "dsrChanged = "); Dz1TcpSerialMsgPin_dump(p->x.dsrChanged, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1Thread_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}

