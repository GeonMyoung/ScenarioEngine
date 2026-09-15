////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////


#include <dz1_gasn_support.h>
#include "TechnicalRegulation2EamDz1.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1CommTxPDU
Dz1CommTxPDU* Dz1CommTxPDU_new(u32_t index,
	u32_t psid,
	u8_t priority,
	u8_t channel,
	u16_t txInterval,
	Dz1TimeVal* deliveryStart,
	Dz1TimeVal* deliveryStop,
	Dz1Asn1OctetStr* payload, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommTxPDU* __internal_ret = (Dz1CommTxPDU*)Dz1Calloc(sizeof(Dz1CommTxPDU), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CommTxPDU_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->index = index;
		__internal_ret->psid = psid;
		__internal_ret->priority = priority;
		__internal_ret->channel = channel;
		__internal_ret->txInterval = txInterval;
		__internal_ret->deliveryStart = deliveryStart;
		__internal_ret->deliveryStop = deliveryStop;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommTxPDU_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1CommTxPDU* Dz1CommTxPDU_clone(Dz1CommTxPDU* src, Dz1Error* err)
{
	Dz1CommTxPDU* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1CommTxPDU*)Dz1Calloc(sizeof(Dz1CommTxPDU), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1CommTxPDU_delAndSetNull, (void*)&ret);

		if (src->ipAddressServicePort && (ret->ipAddressServicePort = Dz1NetworkInfo_clone(src->ipAddressServicePort, errp)) == NULL) ERR_OUT(errp);
		else if (src->deliveryStart && (ret->deliveryStart = Dz1TimeVal_clone(src->deliveryStart, errp)) == NULL) ERR_OUT(errp);
		else if (src->deliveryStop && (ret->deliveryStop = Dz1TimeVal_clone(src->deliveryStop, errp)) == NULL) ERR_OUT(errp);
		else if (src->signature && (ret->signature = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payloadType && (ret->payloadType = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payload && (ret->payload = Dz1Asn1OctetStr_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
		else if (src->txPower && (ret->txPower = (s8_t*)Dz1Calloc(sizeof(s8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->txDataRate && (ret->txDataRate = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->channelNumberHdrExt && (ret->channelNumberHdrExt = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->dataRateHdrExt && (ret->dataRateHdrExt = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->txPowerHdrExt && (ret->txPowerHdrExt = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->index = src->index;
			ret->psid = src->psid;
			ret->priority = src->priority;
			ret->channel = src->channel;
			ret->txInterval = src->txInterval;
			if (src->signature != NULL && ret->signature != NULL) *ret->signature = *src->signature;
			if (src->payloadType != NULL && ret->payloadType != NULL) *ret->payloadType = *src->payloadType;
			if (src->txPower != NULL && ret->txPower != NULL) *ret->txPower = *src->txPower;
			if (src->txDataRate != NULL && ret->txDataRate != NULL) *ret->txDataRate = *src->txDataRate;
			if (src->channelNumberHdrExt != NULL && ret->channelNumberHdrExt != NULL) *ret->channelNumberHdrExt = *src->channelNumberHdrExt;
			if (src->dataRateHdrExt != NULL && ret->dataRateHdrExt != NULL) *ret->dataRateHdrExt = *src->dataRateHdrExt;
			if (src->txPowerHdrExt != NULL && ret->txPowerHdrExt != NULL) *ret->txPowerHdrExt = *src->txPowerHdrExt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommTxPDU_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CommTxPDU_del(Dz1CommTxPDU* p)
{
	if (p == NULL) return;
	if (p->ipAddressServicePort) Dz1NetworkInfo_del(p->ipAddressServicePort);
	if (p->deliveryStart) Dz1TimeVal_del(p->deliveryStart);
	if (p->deliveryStop) Dz1TimeVal_del(p->deliveryStop);
	if (p->signature) Dz1Free(p->signature);
	if (p->payloadType) Dz1Free(p->payloadType);
	if (p->payload) Dz1Asn1OctetStr_del(p->payload);
	if (p->txPower) Dz1Free(p->txPower);
	if (p->txDataRate) Dz1Free(p->txDataRate);
	if (p->channelNumberHdrExt) Dz1Free(p->channelNumberHdrExt);
	if (p->dataRateHdrExt) Dz1Free(p->dataRateHdrExt);
	if (p->txPowerHdrExt) Dz1Free(p->txPowerHdrExt);
	Dz1Free(p);
}

void Dz1CommTxPDU_dump(Dz1CommTxPDU* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("index = ")); Dz1u32_dump(&p->index, tab);

	Dz1Thread_tprintf(tab, Dz1T("psid = ")); Dz1u32_dump(&p->psid, tab);

	Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1u8_dump(&p->priority, tab);

	Dz1Thread_tprintf(tab, Dz1T("channel = ")); Dz1u8_dump(&p->channel, tab);

	Dz1Thread_tprintf(tab, Dz1T("txInterval = ")); Dz1u16_dump(&p->txInterval, tab);

	if (p->ipAddressServicePort == NULL) Dz1Thread_tprintf(tab, Dz1T("ipAddressServicePort = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("ipAddressServicePort = ")); Dz1NetworkInfo_dump(p->ipAddressServicePort, tab); /* using dump func */ }

	if (p->deliveryStart == NULL) Dz1Thread_tprintf(tab, Dz1T("deliveryStart = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("deliveryStart = ")); Dz1TimeVal_dump(p->deliveryStart, tab); /* using dump func */ }

	if (p->deliveryStop == NULL) Dz1Thread_tprintf(tab, Dz1T("deliveryStop = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("deliveryStop = ")); Dz1TimeVal_dump(p->deliveryStop, tab); /* using dump func */ }

	if (p->signature == NULL) Dz1Thread_tprintf(tab, Dz1T("signature = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("signature = ")); Dz1Bool_dump(p->signature, tab); }

	if (p->payloadType == NULL) Dz1Thread_tprintf(tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payloadType = ")); Dz1s64_dump(p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_tprintf(tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Asn1OctetStr_dump(p->payload, tab); /* using dump func */ }

	if (p->txPower == NULL) Dz1Thread_tprintf(tab, Dz1T("txPower = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("txPower = ")); Dz1s8_dump(p->txPower, tab); }

	if (p->txDataRate == NULL) Dz1Thread_tprintf(tab, Dz1T("txDataRate = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("txDataRate = ")); Dz1u8_dump(p->txDataRate, tab); }

	if (p->channelNumberHdrExt == NULL) Dz1Thread_tprintf(tab, Dz1T("channelNumberHdrExt = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("channelNumberHdrExt = ")); Dz1Bool_dump(p->channelNumberHdrExt, tab); }

	if (p->dataRateHdrExt == NULL) Dz1Thread_tprintf(tab, Dz1T("dataRateHdrExt = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("dataRateHdrExt = ")); Dz1Bool_dump(p->dataRateHdrExt, tab); }

	if (p->txPowerHdrExt == NULL) Dz1Thread_tprintf(tab, Dz1T("txPowerHdrExt = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("txPowerHdrExt = ")); Dz1Bool_dump(p->txPowerHdrExt, tab); }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1CommTxPDU_fdump(FILE* fp, Dz1CommTxPDU* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	Dz1Thread_ftprintf(fp, tab, Dz1T("index = ")); Dz1u32_fdump(fp, &p->index, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("psid = ")); Dz1u32_fdump(fp, &p->psid, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("priority = ")); Dz1u8_fdump(fp, &p->priority, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("channel = ")); Dz1u8_fdump(fp, &p->channel, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("txInterval = ")); Dz1u16_fdump(fp, &p->txInterval, tab);

	if (p->ipAddressServicePort == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("ipAddressServicePort = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("ipAddressServicePort = ")); Dz1NetworkInfo_fdump(fp, p->ipAddressServicePort, tab); }

	if (p->deliveryStart == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStart = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStart = %p\n"), p->deliveryStart); }

	if (p->deliveryStop == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStop = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStop = %p\n"), p->deliveryStop); }

	if (p->signature == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("signature = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("signature = ")); Dz1Bool_fdump(fp, p->signature, tab); }

	if (p->payloadType == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = ")); Dz1s64_fdump(fp, p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payload = ")); Dz1Asn1OctetStr_fdump(fp, p->payload, tab); }

	if (p->txPower == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("txPower = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("txPower = ")); Dz1s8_fdump(fp, p->txPower, tab); }

	if (p->txDataRate == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("txDataRate = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("txDataRate = ")); Dz1u8_fdump(fp, p->txDataRate, tab); }

	if (p->channelNumberHdrExt == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("channelNumberHdrExt = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("channelNumberHdrExt = ")); Dz1Bool_fdump(fp, p->channelNumberHdrExt, tab); }

	if (p->dataRateHdrExt == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("dataRateHdrExt = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("dataRateHdrExt = ")); Dz1Bool_fdump(fp, p->dataRateHdrExt, tab); }

	if (p->txPowerHdrExt == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("txPowerHdrExt = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("txPowerHdrExt = ")); Dz1Bool_fdump(fp, p->txPowerHdrExt, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1CommTxPDU_fromASN(Dz1CommTxPDU* dst, CommTxPDU* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_fromASN(&dst->index, &src->index)).code) { Dz1Thread_printf("index : "); ERR_OUT(&err); }
		else if ((err = u32_t_fromASN(&dst->psid, &src->psid)).code) { Dz1Thread_printf("psid : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->priority, &src->priority)).code) { Dz1Thread_printf("priority : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->channel, &src->channel)).code) { Dz1Thread_printf("channel : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->txInterval, &src->txInterval)).code) { Dz1Thread_printf("txInterval : "); ERR_OUT(&err); }
		else if (src->DEF_CommTxPDU_ipAddressServicePort && (dst->ipAddressServicePort = Dz1NetworkInfo_newFromASN(src->ipAddressServicePort, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->deliveryStart = Dz1TimeVal_newFromGeneralizedTime(&src->deliveryStart, &err)) == NULL) { Dz1Thread_printf("deliveryStart : "); ERR_OUT(&err); }
		else if ((dst->deliveryStop = Dz1TimeVal_newFromGeneralizedTime(&src->deliveryStop, &err)) == NULL) { Dz1Thread_printf("deliveryStop : "); ERR_OUT(&err); }
		else if (src->DEF_CommTxPDU_signature && (dst->signature = bool_t_newFromASN(&src->signature, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommTxPDU_payloadType && (dst->payloadType = s64_t_newFromASN(&src->payloadType, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->payload = Dz1Asn1OctetStr_newFromASN(&src->payload, &err)) == NULL) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else if (src->DEF_CommTxPDU_txPower && (dst->txPower = s8_t_newFromASN(&src->txPower, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommTxPDU_txDataRate && (dst->txDataRate = u8_t_newFromASN(&src->txDataRate, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommTxPDU_channelNumberHdrExt && (dst->channelNumberHdrExt = bool_t_newFromASN(&src->channelNumberHdrExt, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommTxPDU_dataRateHdrExt && (dst->dataRateHdrExt = bool_t_newFromASN(&src->dataRateHdrExt, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommTxPDU_txPowerHdrExt && (dst->txPowerHdrExt = bool_t_newFromASN(&src->txPowerHdrExt, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1CommTxPDU, CommTxPDU)

Dz1Error Dz1CommTxPDU_toASN(CommTxPDU* dst, Dz1CommTxPDU* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_toASN(&dst->index, &src->index, ws)).code) { Dz1Thread_printf("index : "); ERR_OUT(&err); }
		else if ((err = u32_t_toASN(&dst->psid, &src->psid, ws)).code) { Dz1Thread_printf("psid : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->priority, &src->priority, ws)).code) { Dz1Thread_printf("priority : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->channel, &src->channel, ws)).code) { Dz1Thread_printf("channel : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->txInterval, &src->txInterval, ws)).code) { Dz1Thread_printf("txInterval : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_ipAddressServicePort = src->ipAddressServicePort ? 1 : 0) == 1 && (dst->ipAddressServicePort = Dz1NetworkInfo_toNewASN(src->ipAddressServicePort, ws, &err)) == NULL) { Dz1Thread_printf("ipAddressServicePort : "); ERR_OUT(&err); }
		else if ((err = Dz1TimeVal_toGeneralizedTime(&dst->deliveryStart, src->deliveryStart, ws)).code) { Dz1Thread_printf("deliveryStart : "); ERR_OUT(&err); }
		else if ((err = Dz1TimeVal_toGeneralizedTime(&dst->deliveryStop, src->deliveryStop, ws)).code) { Dz1Thread_printf("deliveryStop : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_signature = src->signature ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->signature, src->signature, ws)).code) { Dz1Thread_printf("signature : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_payloadType = src->payloadType ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->payloadType, src->payloadType, ws)).code) { Dz1Thread_printf("payloadType : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1OctetStr_toASN(&dst->payload, src->payload, ws)).code) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_txPower = src->txPower ? 1 : 0) == 1 && (err = s8_t_toASN(&dst->txPower, src->txPower, ws)).code) { Dz1Thread_printf("txPower : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_txDataRate = src->txDataRate ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->txDataRate, src->txDataRate, ws)).code) { Dz1Thread_printf("txDataRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_channelNumberHdrExt = src->channelNumberHdrExt ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->channelNumberHdrExt, src->channelNumberHdrExt, ws)).code) { Dz1Thread_printf("channelNumberHdrExt : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_dataRateHdrExt = src->dataRateHdrExt ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->dataRateHdrExt, src->dataRateHdrExt, ws)).code) { Dz1Thread_printf("dataRateHdrExt : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommTxPDU_txPowerHdrExt = src->txPowerHdrExt ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->txPowerHdrExt, src->txPowerHdrExt, ws)).code) { Dz1Thread_printf("txPowerHdrExt : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1CommTxPDU, CommTxPDU)
// Dz1CommTxPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommTxPDUResponse
static Dz1Error Dz1CommTxPDUResponse_add(Dz1CommTxPDUResponse* p, Dz1CommTxPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1CommTxPDUResponseMkArrArg
{
	Dz1CommTxPDU** arr;
	unsigned int idx;
} Dz1CommTxPDUResponseMkArrArg;

static Dz1Error _Dz1CommTxPDUResponse_get_array(void* ptr, Dz1CommTxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommTxPDUResponseMkArrArg* arg = (Dz1CommTxPDUResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1CommTxPDU** Dz1CommTxPDUResponse_get_array(Dz1CommTxPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1CommTxPDU** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CommTxPDU**)Dz1Calloc(sizeof(Dz1CommTxPDU*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CommTxPDUResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1CommTxPDUResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1CommTxPDUResponse_travelForward(Dz1CommTxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommTxPDU* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1CommTxPDUResponse_travelBackward(Dz1CommTxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommTxPDU* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1CommTxPDUResponse_count(Dz1CommTxPDUResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommTxPDUResponse* ret = (Dz1CommTxPDUResponse*)Dz1Calloc(sizeof(Dz1CommTxPDUResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommTxPDUResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1CommTxPDU_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1CommTxPDUResponse_add;
			ret->get_array = Dz1CommTxPDUResponse_get_array;
			ret->travel = Dz1CommTxPDUResponse_travelForward;
			ret->travelForward = Dz1CommTxPDUResponse_travelForward;
			ret->travelBackward = Dz1CommTxPDUResponse_travelBackward;
			ret->count = Dz1CommTxPDUResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommTxPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1CommTxPDUResponse_clone(void* ptr, Dz1CommTxPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommTxPDUResponse* p = (Dz1CommTxPDUResponse*)ptr;
	Dz1CommTxPDU* cloned = Dz1CommTxPDU_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_clone(Dz1CommTxPDUResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommTxPDUResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1CommTxPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommTxPDUResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1CommTxPDUResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommTxPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CommTxPDUResponse_del(Dz1CommTxPDUResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1CommTxPDUResponse_dump(void* ptr, Dz1CommTxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1CommTxPDU_dump(p, tab);
	return err;
}

void Dz1CommTxPDUResponse_dump(Dz1CommTxPDUResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CommTxPDUResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1CommTxPDUResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1CommTxPDUResponseFDumpArg;

static Dz1Error _Dz1CommTxPDUResponse_fdump(void* ptr, Dz1CommTxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommTxPDUResponseFDumpArg* arg = (Dz1CommTxPDUResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1CommTxPDU_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1CommTxPDUResponse_fdump(FILE* fp, Dz1CommTxPDUResponse* p, int tab)
{
	Dz1CommTxPDUResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CommTxPDUResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1CommTxPDUResponse, Dz1CommTxPDU, CommTxPDU)
DZ1_NEW_LIST_FROM_ASN(Dz1CommTxPDUResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1CommTxPDUResponse, Dz1CommTxPDU, CommTxPDU)
PSEUDO_LIST_TO_ASN(Dz1CommTxPDUResponse)
DZ1_TO_NEW_ASN_LIST(Dz1CommTxPDUResponse, ASN1List)

// Dz1CommTxPDUResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NetworkInfo
Dz1NetworkInfo* Dz1NetworkInfo_new(Dz1Asn1OctetStr* ipAddress,
	u16_t servicePort,
	Dz1Asn1OctetStr* providerServiceContext, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1NetworkInfo* __internal_ret = (Dz1NetworkInfo*)Dz1Calloc(sizeof(Dz1NetworkInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1NetworkInfo_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->ipAddress = ipAddress;
		__internal_ret->servicePort = servicePort;
		__internal_ret->providerServiceContext = providerServiceContext;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NetworkInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1NetworkInfo* Dz1NetworkInfo_clone(Dz1NetworkInfo* src, Dz1Error* err)
{
	Dz1NetworkInfo* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1NetworkInfo*)Dz1Calloc(sizeof(Dz1NetworkInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1NetworkInfo_delAndSetNull, (void*)&ret);

		if (src->ipAddress && (ret->ipAddress = Dz1Asn1OctetStr_clone(src->ipAddress, errp)) == NULL) ERR_OUT(errp);
		else if (src->providerServiceContext && (ret->providerServiceContext = Dz1Asn1OctetStr_clone(src->providerServiceContext, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->servicePort = src->servicePort;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NetworkInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1NetworkInfo_del(Dz1NetworkInfo* p)
{
	if (p == NULL) return;
	if (p->ipAddress) Dz1Asn1OctetStr_del(p->ipAddress);
	if (p->providerServiceContext) Dz1Asn1OctetStr_del(p->providerServiceContext);
	Dz1Free(p);
}

void Dz1NetworkInfo_dump(Dz1NetworkInfo* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->ipAddress == NULL) Dz1Thread_tprintf(tab, Dz1T("ipAddress = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("ipAddress = ")); Dz1Asn1OctetStr_dump(p->ipAddress, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("servicePort = ")); Dz1u16_dump(&p->servicePort, tab);

	if (p->providerServiceContext == NULL) Dz1Thread_tprintf(tab, Dz1T("providerServiceContext = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("providerServiceContext = ")); Dz1Asn1OctetStr_dump(p->providerServiceContext, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1NetworkInfo_fdump(FILE* fp, Dz1NetworkInfo* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->ipAddress == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("ipAddress = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("ipAddress = ")); Dz1Asn1OctetStr_fdump(fp, p->ipAddress, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("servicePort = ")); Dz1u16_fdump(fp, &p->servicePort, tab);

	if (p->providerServiceContext == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("providerServiceContext = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("providerServiceContext = ")); Dz1Asn1OctetStr_fdump(fp, p->providerServiceContext, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1NetworkInfo_fromASN(Dz1NetworkInfo* dst, NetworkInfo* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->ipAddress = Dz1Asn1OctetStr_newFromASN(&src->ipAddress, &err)) == NULL) { Dz1Thread_printf("ipAddress : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->servicePort, &src->servicePort)).code) { Dz1Thread_printf("servicePort : "); ERR_OUT(&err); }
		else if ((dst->providerServiceContext = Dz1Asn1OctetStr_newFromASN(&src->providerServiceContext, &err)) == NULL) { Dz1Thread_printf("providerServiceContext : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1NetworkInfo, NetworkInfo)

Dz1Error Dz1NetworkInfo_toASN(NetworkInfo* dst, Dz1NetworkInfo* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1OctetStr_toASN(&dst->ipAddress, src->ipAddress, ws)).code) { Dz1Thread_printf("ipAddress : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->servicePort, &src->servicePort, ws)).code) { Dz1Thread_printf("servicePort : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1OctetStr_toASN(&dst->providerServiceContext, src->providerServiceContext, ws)).code) { Dz1Thread_printf("providerServiceContext : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1NetworkInfo, NetworkInfo)
// Dz1NetworkInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommRxPDU
Dz1CommRxPDU* Dz1CommRxPDU_new(u32_t psid,
	u8_t channel,
	u8_t rcpi,
	Dz1Asn1OctetStr* payload, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommRxPDU* __internal_ret = (Dz1CommRxPDU*)Dz1Calloc(sizeof(Dz1CommRxPDU), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CommRxPDU_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->psid = psid;
		__internal_ret->channel = channel;
		__internal_ret->rcpi = rcpi;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommRxPDU_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1CommRxPDU* Dz1CommRxPDU_clone(Dz1CommRxPDU* src, Dz1Error* err)
{
	Dz1CommRxPDU* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1CommRxPDU*)Dz1Calloc(sizeof(Dz1CommRxPDU), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1CommRxPDU_delAndSetNull, (void*)&ret);

		if (src->peerAddress && (ret->peerAddress = Dz1Asn1OctetStr_clone(src->peerAddress, errp)) == NULL) ERR_OUT(errp);
		else if (src->sign && (ret->sign = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payloadType && (ret->payloadType = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payload && (ret->payload = Dz1Asn1OctetStr_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->psid = src->psid;
			ret->channel = src->channel;
			ret->rcpi = src->rcpi;
			if (src->sign != NULL && ret->sign != NULL) *ret->sign = *src->sign;
			if (src->payloadType != NULL && ret->payloadType != NULL) *ret->payloadType = *src->payloadType;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommRxPDU_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CommRxPDU_del(Dz1CommRxPDU* p)
{
	if (p == NULL) return;
	if (p->peerAddress) Dz1Asn1OctetStr_del(p->peerAddress);
	if (p->sign) Dz1Free(p->sign);
	if (p->payloadType) Dz1Free(p->payloadType);
	if (p->payload) Dz1Asn1OctetStr_del(p->payload);
	Dz1Free(p);
}

void Dz1CommRxPDU_dump(Dz1CommRxPDU* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("psid = ")); Dz1u32_dump(&p->psid, tab);

	Dz1Thread_tprintf(tab, Dz1T("channel = ")); Dz1u8_dump(&p->channel, tab);

	Dz1Thread_tprintf(tab, Dz1T("rcpi = ")); Dz1u8_dump(&p->rcpi, tab);

	if (p->peerAddress == NULL) Dz1Thread_tprintf(tab, Dz1T("peerAddress = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peerAddress = ")); Dz1Asn1OctetStr_dump(p->peerAddress, tab); /* using dump func */ }

	if (p->sign == NULL) Dz1Thread_tprintf(tab, Dz1T("sign = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("sign = ")); Dz1Bool_dump(p->sign, tab); }

	if (p->payloadType == NULL) Dz1Thread_tprintf(tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payloadType = ")); Dz1s64_dump(p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_tprintf(tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Asn1OctetStr_dump(p->payload, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1CommRxPDU_fdump(FILE* fp, Dz1CommRxPDU* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	Dz1Thread_ftprintf(fp, tab, Dz1T("psid = ")); Dz1u32_fdump(fp, &p->psid, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("channel = ")); Dz1u8_fdump(fp, &p->channel, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("rcpi = ")); Dz1u8_fdump(fp, &p->rcpi, tab);

	if (p->peerAddress == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("peerAddress = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("peerAddress = ")); Dz1Asn1OctetStr_fdump(fp, p->peerAddress, tab); }

	if (p->sign == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("sign = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("sign = ")); Dz1Bool_fdump(fp, p->sign, tab); }

	if (p->payloadType == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = ")); Dz1s64_fdump(fp, p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payload = ")); Dz1Asn1OctetStr_fdump(fp, p->payload, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1CommRxPDU_fromASN(Dz1CommRxPDU* dst, CommRxPDU* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_fromASN(&dst->psid, &src->psid)).code) { Dz1Thread_printf("psid : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->channel, &src->channel)).code) { Dz1Thread_printf("channel : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->rcpi, &src->rcpi)).code) { Dz1Thread_printf("rcpi : "); ERR_OUT(&err); }
		else if (src->DEF_CommRxPDU_peerAddress && (dst->peerAddress = Dz1Asn1OctetStr_newFromASN(&src->peerAddress, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommRxPDU_signed && (dst->sign = bool_t_newFromASN(&src->sign, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CommRxPDU_payloadType && (dst->payloadType = s64_t_newFromASN(&src->payloadType, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->payload = Dz1Asn1OctetStr_newFromASN(&src->payload, &err)) == NULL) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1CommRxPDU, CommRxPDU)

Dz1Error Dz1CommRxPDU_toASN(CommRxPDU* dst, Dz1CommRxPDU* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_toASN(&dst->psid, &src->psid, ws)).code) { Dz1Thread_printf("psid : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->channel, &src->channel, ws)).code) { Dz1Thread_printf("channel : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->rcpi, &src->rcpi, ws)).code) { Dz1Thread_printf("rcpi : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommRxPDU_peerAddress = src->peerAddress ? 1 : 0) == 1 && (err = Dz1Asn1OctetStr_toASN(&dst->peerAddress, src->peerAddress, ws)).code) { Dz1Thread_printf("peerAddress : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommRxPDU_signed = src->sign ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->sign, src->sign, ws)).code) { Dz1Thread_printf("sign : "); ERR_OUT(&err); }
		else if ((dst->DEF_CommRxPDU_payloadType = src->payloadType ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->payloadType, src->payloadType, ws)).code) { Dz1Thread_printf("payloadType : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1OctetStr_toASN(&dst->payload, src->payload, ws)).code) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1CommRxPDU, CommRxPDU)
// Dz1CommRxPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommRxPDUResponse
static Dz1Error Dz1CommRxPDUResponse_add(Dz1CommRxPDUResponse* p, Dz1CommRxPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1CommRxPDUResponseMkArrArg
{
	Dz1CommRxPDU** arr;
	unsigned int idx;
} Dz1CommRxPDUResponseMkArrArg;

static Dz1Error _Dz1CommRxPDUResponse_get_array(void* ptr, Dz1CommRxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommRxPDUResponseMkArrArg* arg = (Dz1CommRxPDUResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1CommRxPDU** Dz1CommRxPDUResponse_get_array(Dz1CommRxPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1CommRxPDU** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CommRxPDU**)Dz1Calloc(sizeof(Dz1CommRxPDU*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CommRxPDUResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1CommRxPDUResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1CommRxPDUResponse_travelForward(Dz1CommRxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommRxPDU* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1CommRxPDUResponse_travelBackward(Dz1CommRxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommRxPDU* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1CommRxPDUResponse_count(Dz1CommRxPDUResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommRxPDUResponse* ret = (Dz1CommRxPDUResponse*)Dz1Calloc(sizeof(Dz1CommRxPDUResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommRxPDUResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1CommRxPDU_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1CommRxPDUResponse_add;
			ret->get_array = Dz1CommRxPDUResponse_get_array;
			ret->travel = Dz1CommRxPDUResponse_travelForward;
			ret->travelForward = Dz1CommRxPDUResponse_travelForward;
			ret->travelBackward = Dz1CommRxPDUResponse_travelBackward;
			ret->count = Dz1CommRxPDUResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommRxPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1CommRxPDUResponse_clone(void* ptr, Dz1CommRxPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommRxPDUResponse* p = (Dz1CommRxPDUResponse*)ptr;
	Dz1CommRxPDU* cloned = Dz1CommRxPDU_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_clone(Dz1CommRxPDUResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CommRxPDUResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1CommRxPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommRxPDUResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1CommRxPDUResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CommRxPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CommRxPDUResponse_del(Dz1CommRxPDUResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1CommRxPDUResponse_dump(void* ptr, Dz1CommRxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1CommRxPDU_dump(p, tab);
	return err;
}

void Dz1CommRxPDUResponse_dump(Dz1CommRxPDUResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CommRxPDUResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1CommRxPDUResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1CommRxPDUResponseFDumpArg;

static Dz1Error _Dz1CommRxPDUResponse_fdump(void* ptr, Dz1CommRxPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CommRxPDUResponseFDumpArg* arg = (Dz1CommRxPDUResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1CommRxPDU_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1CommRxPDUResponse_fdump(FILE* fp, Dz1CommRxPDUResponse* p, int tab)
{
	Dz1CommRxPDUResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CommRxPDUResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1CommRxPDUResponse, Dz1CommRxPDU, CommRxPDU)
DZ1_NEW_LIST_FROM_ASN(Dz1CommRxPDUResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1CommRxPDUResponse, Dz1CommRxPDU, CommRxPDU)
PSEUDO_LIST_TO_ASN(Dz1CommRxPDUResponse)
DZ1_TO_NEW_ASN_LIST(Dz1CommRxPDUResponse, ASN1List)

// Dz1CommRxPDUResponse
////////////////////////////////////////////////////////////////////////////////

