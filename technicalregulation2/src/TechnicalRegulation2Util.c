#include <TechnicalRegulation2MsgStructAPI.h>


static CommTxPDUEntry* CommTxPDUEntry_fromDimz(Dz1CommTxPDU* src, Dz1Error* errp)
{
	CommTxPDUEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CommTxPDUEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&ret);
		ret->idx = src->index;
		ret->psid = src->psid;
		ret->priority = src->priority;
		ret->channel = src->channel;
		ret->txInterval = src->txInterval;
		ret->deliveryStart = src->deliveryStart->tv_sec;
		ret->deliveryStop = src->deliveryStop->tv_sec;
		if ((ret->payload = Dz1Binary_new(src->payload->data, src->payload->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			if (src->ipAddressServicePort != NULL)
			{
				if ((ret->ipAddress = Dz1Str_ndup(src->ipAddressServicePort->ipAddress->data, src->ipAddressServicePort->ipAddress->size, errp)) == NULL) ERR_OUT(errp);
				else if ((ret->provideServiceContext = Dz1Str_ndup(src->ipAddressServicePort->providerServiceContext->data, src->ipAddressServicePort->providerServiceContext->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->servicePort = src->ipAddressServicePort->servicePort;
					Dz1Error_set(errp, 0);
				}
			}
			if (src->payloadType != NULL) ret->payloadType = *src->payloadType;
			if (src->signature != NULL) ret->signature = *src->signature;
			if (src->txPower != NULL) ret->txPower = *src->txPower;
			if (src->txDataRate != NULL) ret->txDataRate = *src->txDataRate;
			if (src->channelNumberHdrExt != NULL) ret->channelNumberHdrExt = *src->channelNumberHdrExt;
			if (src->dataRateHdrExt != NULL) ret->dataRateHdrExt = *src->dataRateHdrExt;
			if (src->txPowerHdrExt != NULL) ret->txPowerHdrExt = *src->txPowerHdrExt;
		}
		pthread_cleanup_pop(errp->code); // (CommTxPDUEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

CommTxPDUList* CommTxPDUList_fromDimz(Dz1CommTxPDUResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommTxPDUList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CommTxPDUList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CommTxPDU** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(CommTxPDUList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1CommTxPDU* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				CommTxPDUEntry* entry = NULL;
				if ((entry = CommTxPDUEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (CommTxPDUList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static CommRxPDUEntry* CommRxPDUEntry_fromDimz(Dz1CommRxPDU* src, Dz1Error* errp)
{
	CommRxPDUEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CommRxPDUEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&ret);
		ret->psid = src->psid;
		ret->channel = src->channel;
		ret->rcpi = src->rcpi;
		if ((ret->payload = Dz1Binary_new(src->payload->data, src->payload->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			if (src->peerAddress != NULL)
			{
				if ((ret->peerAddress = Dz1Str_ndup(src->peerAddress->data, src->peerAddress->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->sign != NULL) ret->sign = *src->sign;
			if (src->payloadType != NULL) ret->payloadType = *src->payloadType;
		}
		pthread_cleanup_pop(errp->code); // (CommRxPDUEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

CommRxPDUList* CommRxPDUList_fromDimz(Dz1CommRxPDUResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommRxPDUList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CommRxPDUList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CommRxPDU** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(CommRxPDUList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1CommRxPDU* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				CommRxPDUEntry* entry = NULL;
				if ((entry = CommRxPDUEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommRxPDUEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (CommRxPDUList_delAndSetNull, (void*)&ret);
	}

	return ret;
}