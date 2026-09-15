#include <dz1_malloc.h>

#include "Iso3309CRC.h"
#include "Iso14827dz1_assistGeneralAsn.h"

#ifdef GITSN_GENERAL_ASN_TOOL

C2CAuthenticatedMessage_t *C2CAuthenticatedMessage_new(OCTET_STRING_t *authInfo, long packetNbr, long priority,
														UTF8String_t *dstDomain, UTF8String_t *srcDomain, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	C2CAuthenticatedMessage_t *ret = (C2CAuthenticatedMessage_t *)calloc(sizeof(C2CAuthenticatedMessage_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(C2CAuthenticatedMessage_delAndSetNull, (void *)&ret);
		
		if (OCTET_STRING_fromBuf(&ret->datex_AuthenticationInfo_text, (char *)authInfo->buf, authInfo->size) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (asn_long2INTEGER(&ret->datex_DataPacket_number, packetNbr) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->options.datex_Destination_text =
					OCTET_STRING_new_fromBuf(&asn_DEF_UTF8String, (char *)dstDomain->buf, dstDomain->size)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->options.datex_Origin_text =
					OCTET_STRING_new_fromBuf(&asn_DEF_UTF8String, (char *)srcDomain->buf, srcDomain->size)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->datex_DataPacketPriority_number = priority;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (C2CAuthenticatedMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

int C2CAuthenticatedMessage_cmp(C2CAuthenticatedMessage_t *a, C2CAuthenticatedMessage_t *b)
{
	long pktA, pktB;
	asn_INTEGER2long(&a->datex_DataPacket_number, &pktA);
	asn_INTEGER2long(&b->datex_DataPacket_number, &pktB);
	return (int)(pktA - pktB);
}

// Make Signle Mode Subscription
Subscription_t *Subscription_new(long serial, BOOLEAN_t persistent, datexSubscribe_Status_cd_e status,
								 datexSubscribe_PublishFormat_cd_e format, long priority, BOOLEAN_t guarantee,
								str_t oid, struct asn_TYPE_descriptor_s *endAppMsgType, void *endAppMsg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Subscription_t *ret = (Subscription_t *)calloc(sizeof(Subscription_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(Subscription_delAndSetNull, (void *)&ret);

		if (asn_long2INTEGER(&ret->datexSubscribe_Serial_nbr, serial) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			SubscriptionType_t *st = &ret->datexSubscribe_Type;
			SubscriptionData_t *sd = &ret->datexSubscribe_Type.choice.subscription;
			EndApplicationMessage_t *em = &sd->datexSubscribe_Pdu;
			st->present = SubscriptionType_PR_subscription;
			sd->datexSubscribe_Persistent_bool = persistent;
			sd->datexSubscribe_Status_cd = status;
			sd->datexSubscribe_Mode.present = SubscriptionMode_PR_single;
			sd->datexSubscribe_PublishFormat_cd = format;
			sd->datexSubscription_Priority_nbr = priority;
			sd->datexSubscribe_Guarantee_bool = guarantee;
			if ((*errp = OBJECT_IDENTIFIER_set(&em->endApplication_Message_id, oid)).code) ERR_OUT(errp);
			else if (ANY_fromType(&em->endApplication_Message_msg, endAppMsgType, endAppMsg) != 0) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (freeAndSetNull, (void *)&ret);
	}
	return ret;
}

Subscription_t *Subscription_cancelNew(long serial, datexSubscribe_CancelReason_cd_e reason, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Subscription_t *ret = (Subscription_t *)calloc(sizeof(Subscription_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(Subscription_delAndSetNull, (void *)&ret);

		if (asn_long2INTEGER(&ret->datexSubscribe_Serial_nbr, serial) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			SubscriptionType_t *st = &ret->datexSubscribe_Type;
			st->present = SubscriptionType_PR_datexSubscribe_CancelReason_cd;
			st->choice.datexSubscribe_CancelReason_cd = reason;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (freeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Subscription_setModeEventContinuous(Subscription_t *p, long *updateDelaySec, time_t *startTime, time_t *endTime)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		SubscriptionType_t *st = &p->datexSubscribe_Type;
		if (st->present != SubscriptionType_PR_subscription) ERR_SET_OUT(&err, EINVAL);
		else
		{
			SubscriptionData_t *sd = &st->choice.subscription;
			SubscriptionMode_t *sm = &sd->datexSubscribe_Mode;
			Registered_t *edr = &sm->choice.event_driven;
			struct continuous *cont = &edr->choice.continuous;

			sm->present = SubscriptionMode_PR_event_driven;
			edr->present = Registered_PR_continuous;

			if (updateDelaySec && (cont->datexRegistered_UpdateDelay_qty = INTEGER_new(*updateDelaySec, &err)) == NULL) ERR_OUT(&err);
			else if (startTime && (cont->datexRegistered_StartTime = IsoTime_new(*startTime, TimeConv_full, &err)) == NULL) ERR_OUT(&err);
			else if (endTime && (cont->datexRegistered_EndTime = IsoTime_new(*endTime, TimeConv_full, &err)) == NULL) ERR_OUT(&err);
		}
	}
	return err;
}

Dz1Error Subscription_setModeEventDaily(Subscription_t *p, long *updateDelaySec, u8_t dailyBit,
										time_t *startDate, time_t *endDate, time_t *startTime, long *durationSec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		SubscriptionType_t *st = &p->datexSubscribe_Type;
		if (st->present != SubscriptionType_PR_subscription) ERR_SET_OUT(&err, EINVAL);
		else
		{
			SubscriptionData_t *sd = &st->choice.subscription;
			SubscriptionMode_t *sm = &sd->datexSubscribe_Mode;
			Registered_t *edr = &sm->choice.event_driven;
			struct daily *daily = &edr->choice.daily;

			sm->present = SubscriptionMode_PR_event_driven;
			edr->present = Registered_PR_daily;

			if (updateDelaySec && (daily->datexRegistered_UpdateDelay_qty = INTEGER_new(*updateDelaySec, &err)) == NULL) ERR_OUT(&err);
			else if ((err = DailyBit_set(&daily->datexRegistered_DaysOfWeek_cd, dailyBit)).code) ERR_OUT(&err);
			else if (startDate && (daily->datexRegistered_StartDate = IsoTime_new(*startDate, TimeConv_date, &err)) == NULL) ERR_OUT(&err);
			else if (endDate && (daily->datexRegistered_EndDate = IsoTime_new(*endDate, TimeConv_date, &err)) == NULL) ERR_OUT(&err);
			else if (startTime && (daily->datexRegistered_StartTime = IsoTime_new(*startTime, TimeConv_clock, &err)) == NULL) ERR_OUT(&err);
			else if (durationSec && (daily->datexRegistered_Duration_qty = Asn1Long_new(*durationSec, &err)) == NULL) ERR_OUT(&err);
		}
	}
	return err;
}

Dz1Error Subscription_setModePeriodicContinuous(Subscription_t *p, long periodSec, time_t *startTime, time_t *endTime)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		SubscriptionType_t *st = &p->datexSubscribe_Type;
		if (st->present != SubscriptionType_PR_subscription) ERR_SET_OUT(&err, EINVAL);
		else
		{
			SubscriptionData_t *sd = &st->choice.subscription;
			SubscriptionMode_t *sm = &sd->datexSubscribe_Mode;
			Registered_t *edr = &sm->choice.event_driven;
			struct continuous *cont = &edr->choice.continuous;

			sm->present = SubscriptionMode_PR_periodic;
			edr->present = Registered_PR_continuous;

			if ((cont->datexRegistered_UpdateDelay_qty = INTEGER_new(periodSec, &err)) == NULL) ERR_OUT(&err);
			else if (startTime && (cont->datexRegistered_StartTime = IsoTime_new(*startTime, TimeConv_full, &err)) == NULL) ERR_OUT(&err);
			else if (endTime && (cont->datexRegistered_EndTime = IsoTime_new(*endTime, TimeConv_full, &err)) == NULL) ERR_OUT(&err);
		}
	}
	return err;
}

Dz1Error Subscription_setModePeriodicDaily(Subscription_t *p, long periodSec, u8_t dailyBit,
										time_t *startDate, time_t *endDate, time_t *startTime, long *durationSec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		SubscriptionType_t *st = &p->datexSubscribe_Type;
		if (st->present != SubscriptionType_PR_subscription) ERR_SET_OUT(&err, EINVAL);
		else
		{
			SubscriptionData_t *sd = &st->choice.subscription;
			SubscriptionMode_t *sm = &sd->datexSubscribe_Mode;
			Registered_t *edr = &sm->choice.event_driven;
			struct daily *daily = &edr->choice.daily;

			sm->present = SubscriptionMode_PR_event_driven;
			edr->present = Registered_PR_daily;

			if ((daily->datexRegistered_UpdateDelay_qty = INTEGER_new(periodSec, &err)) == NULL) ERR_OUT(&err);
			else if ((err = DailyBit_set(&daily->datexRegistered_DaysOfWeek_cd, dailyBit)).code) ERR_OUT(&err);
			else if (startDate && (daily->datexRegistered_StartDate = IsoTime_new(*startDate, TimeConv_date, &err)) == NULL) ERR_OUT(&err);
			else if (endDate && (daily->datexRegistered_EndDate = IsoTime_new(*endDate, TimeConv_date, &err)) == NULL) ERR_OUT(&err);
			else if (startTime && (daily->datexRegistered_StartTime = IsoTime_new(*startTime, TimeConv_clock, &err)) == NULL) ERR_OUT(&err);
			else if (durationSec && (daily->datexRegistered_Duration_qty = Asn1Long_new(*durationSec, &err)) == NULL) ERR_OUT(&err);
		}
	}
	return err;
}

Subscription_t *Subscription_copy(Subscription_t **dst, Subscription_t *src, Dz1Error *err)
{
	Subscription_t *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((ret = asn1msg_copy(&asn_DEF_Subscription, (void **)dst, (void *)src, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

Accept_t *Accept_copy(Accept_t **dst, Accept_t *src, Dz1Error *err) { return asn1msg_copy(&asn_DEF_Accept, (void **)dst, (void *)src, err); }
Reject_t *Reject_copy(Reject_t **dst, Reject_t *src, Dz1Error *err) { return asn1msg_copy(&asn_DEF_Reject, (void **)dst, (void *)src, err); }

static Dz1Error IsoTime_setClock(IsoTime_t *dst, struct tm t)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((dst->time_Hour_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else if ((dst->time_Minute_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else if ((dst->time_Second_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		*dst->time_Hour_qty = t.tm_hour;
		*dst->time_Minute_qty = t.tm_min;
		*dst->time_Second_qty = t.tm_sec;
	}
	return err;
}

static Dz1Error IsoTime_setDate(IsoTime_t *dst, struct tm t)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((dst->time_Year_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else if ((dst->time_Month_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else if ((dst->time_Day_qty = (long *)calloc(sizeof(long), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		*dst->time_Year_qty = t.tm_year + 1900;
		*dst->time_Month_qty = t.tm_mon + 1;
		*dst->time_Day_qty = t.tm_mday;
	}
	return err;
}

IsoTime_t *IsoTime_new(time_t val, TimeConv conv, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	IsoTime_t *ret = (IsoTime_t *)calloc(sizeof(IsoTime_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		struct tm *tm_p, tm;
		pthread_cleanup_push(IsoTime_delAndSetNull, (void *)&ret);

		tm_p = localtime(&val); tm = *tm_p;

		switch(conv)
		{
			case TimeConv_full:
				if ((*errp = IsoTime_setClock(ret, tm)).code) ERR_OUT(errp);
			case TimeConv_date:
				if ((*errp = IsoTime_setDate(ret, tm)).code) ERR_OUT(errp);
				break;
			case TimeConv_clock:
				if ((*errp = IsoTime_setClock(ret, tm)).code) ERR_OUT(errp);
				break;
		}
		pthread_cleanup_pop(errp->code); // (IsoTime_delAndSetNull, (void *)&ret);
	}
	return ret;
}

time_t IsoTime2time(IsoTime_t *src, Dz1Error *err)
{
	time_t ret = time(NULL);
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm *tm_p = localtime(&ret), tm = *tm_p;
		if (src->time_Year_qty) tm.tm_year = (int)(*src->time_Year_qty - 1900);
		if (src->time_Month_qty) tm.tm_mon = (int)(*src->time_Month_qty - 1);
		if (src->time_Day_qty) tm.tm_mday = (int)(*src->time_Day_qty);
		if (src->time_Hour_qty) tm.tm_hour = (int)(*src->time_Hour_qty);
		if (src->time_Minute_qty) tm.tm_min =  (int)(*src->time_Minute_qty);
		if (src->time_Second_qty) tm.tm_sec = (int)(*src->time_Second_qty);

		ret = mktime(&tm);
	}
	return ret;
}

Dz1Error DailyBit_set(BIT_STRING_t *dst, u8_t dailyBit)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (dst->buf) free(dst->buf);

		if ((dst->buf = (uint8_t *)malloc(1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			*dst->buf = dailyBit;
			dst->size = 1;
			dst->bits_unused = 0;
		}
	}
	return err;
}

Publication_t *Publication_newFile(BOOLEAN_t guarantee, UTF8String_t *file, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Publication_t *ret = (Publication_t *)calloc(sizeof(Publication_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		Publish_Format_t *format = &ret->datexPublish_Format;
		pthread_cleanup_push(Publication_delAndSetNull, (void *)&ret);

		ret->datexPublish_Guaranteed_bool = guarantee;
		format->present = Publish_Format_PR_datexPublish_FileName_txt;

		if (OCTET_STRING_fromBuf(&format->choice.datexPublish_FileName_txt, (char *)file->buf, file->size) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Publication_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Publication_t *Publication_newPacket(BOOLEAN_t guarantee, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Publication_t *ret = (Publication_t *)calloc(sizeof(Publication_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		Publish_Format_t *format = &ret->datexPublish_Format;
		ret->datexPublish_Guaranteed_bool = guarantee;
		format->present = Publish_Format_PR_datexPublish_Data;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Publication_t *Publication_copy(Publication_t **dst, Publication_t *src, Dz1Error *err)
{
	Publication_t *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((ret = asn1msg_copy(&asn_DEF_Publication, (void **)dst, (void *)src, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

static PublicationData_t *PublicationData_newMgmt(long subscriptionSerial, long publicationSerial, BOOLEAN_t late, datexPublication_Management_cd_e mgmt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublicationData_t *ret = (PublicationData_t *)calloc(sizeof(PublicationData_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(PublicationData_delAndSetNull, (void *)&ret);

		if (asn_long2INTEGER(&ret->datexPublish_SubscribeSerial_nbr, subscriptionSerial) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (asn_long2INTEGER(&ret->datexPublish_Serial_nbr, publicationSerial) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			PublicationType_t *pt = &ret->datexPublish_Type;
			ret->datexPublish_LatePublicationFlag = late;
			pt->present = PublicationType_PR_datexPublication_Management_cd;
			pt->choice.datexPublication_Management_cd = mgmt;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (PublicationData_delAndSetNull, (void *)&ret);
	}
	return ret;
}


Dz1Error Publication_addMgmt(Publication_t *p, long subscriptionSerial, long publicationSerial, BOOLEAN_t late, datexPublication_Management_cd_e mgmt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Publish_Format_t *format = &p->datexPublish_Format;
		if (format->present != Publish_Format_PR_datexPublish_Data) ERR_SET_OUT(&err, EINVAL);
		else
		{
			struct datexPublish_Data *pdseq = &format->choice.datexPublish_Data;

			PublicationData_t *pd = PublicationData_newMgmt(subscriptionSerial, publicationSerial, late, mgmt, &err);
			if (pd == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)PublicationData_del, (void *)pd);
				if (ASN_SEQUENCE_ADD(pdseq, pd) < 0) ERR_SET_OUT(&err, EFAULT);
				pthread_cleanup_pop(err.code); // ((Dz1DelFunc)PublicationData_del, (void *)pd);
			}
		}
	}
	return err;
}

static PublicationData_t *PublicationData_newData(long subscriptionSerial, long publicationSerial, BOOLEAN_t late, str_t oid, u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublicationData_t *ret = (PublicationData_t *)calloc(sizeof(PublicationData_t), 1);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(PublicationData_delAndSetNull, (void *)&ret);

		if (asn_long2INTEGER(&ret->datexPublish_SubscribeSerial_nbr, subscriptionSerial) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (asn_long2INTEGER(&ret->datexPublish_Serial_nbr, publicationSerial) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			PublicationType_t *pt = &ret->datexPublish_Type;
			EndApplicationMessage_t *em = &pt->choice.datexPublish_Data;

			ret->datexPublish_LatePublicationFlag = late;
			pt->present = PublicationType_PR_datexPublish_Data;

			if ((*errp = OBJECT_IDENTIFIER_set(&em->endApplication_Message_id, oid)).code) ERR_OUT(errp);
			else if (ANY_fromBuf((OCTET_STRING_t *)&em->endApplication_Message_msg, (char *)data, size) < 0) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (PublicationData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Publication_addData(Publication_t *p, long subscriptionSerial, long publicationSerial, BOOLEAN_t late,
								str_t oid, u8_t *encoddedUserData, size_t encoddedUserDataSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Publish_Format_t *format = &p->datexPublish_Format;
		if (format->present != Publish_Format_PR_datexPublish_Data) ERR_SET_OUT(&err, EINVAL);
		else
		{
			struct datexPublish_Data *pdseq = &format->choice.datexPublish_Data;

			PublicationData_t *pd = PublicationData_newData(subscriptionSerial, publicationSerial, late, oid, encoddedUserData, encoddedUserDataSize, &err);
			if (pd == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)PublicationData_del, (void *)pd);
				if (ASN_SEQUENCE_ADD(pdseq, pd) < 0) ERR_SET_OUT(&err, EFAULT);
				pthread_cleanup_pop(err.code); // ((Dz1DelFunc)PublicationData_del, (void *)pd);
			}
		}
	}
	return err;
}
#else
str_t __AssisterGeneralASN__;
#endif // GITSN_GENERAL_ASN_TOOL