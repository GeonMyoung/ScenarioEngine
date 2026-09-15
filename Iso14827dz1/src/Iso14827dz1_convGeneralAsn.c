#ifdef GITSN_GENERAL_ASN_TOOL

#include "Iso14827dz1_conv.h"

///////////////////////////////////////////////////////////////////////////////
// Converting Tool Function for GITSN_GENERAL_ASN_TOOL
///////////////////////////////////////////////////////////////////////////////
static Dz1Error OID_fromASN(Dz1Asn1OID **dst, OBJECT_IDENTIFIER_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		u32_t fixedArr[16], *arr = NULL;
		int cnt = OBJECT_IDENTIFIER_get_arcs(src, fixedArr, sizeof(u32_t), 16);
		if ((arr = (u32_t *)Dz1Malloc(sizeof(u32_t) * cnt, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1Asn1OID *p = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
			
			OBJECT_IDENTIFIER_get_arcs(src, arr, sizeof(u32_t), cnt);
			if ((p = (*dst) = Dz1Asn1OID_new((u8_t *)arr, sizeof(u32_t), cnt, &err)) == NULL) ERR_OUT(&err);
			
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		}
	}
	return err;
}

static Dz1Error OID_toASN(OBJECT_IDENTIFIER_t **dst, Dz1Asn1OID *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		OBJECT_IDENTIFIER_t *p = NULL;
		if ((p = (*dst) = (OBJECT_IDENTIFIER_t *)calloc(sizeof(OBJECT_IDENTIFIER_t), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			pthread_cleanup_push(OBJECT_IDENTIFIER_delAndSetNull, (void *)dst);

			if (OBJECT_IDENTIFIER_set_arcs(p, (void *)src->data, sizeof(src->data[0]), src->cnt) < 0) ERR_SET_OUT(&err, EFAULT);

			pthread_cleanup_pop(err.code); // (OBJECT_IDENTIFIER_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error ANY_fromASN(Dz1Asn1Any **dst, ANY_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Asn1Any *p = NULL;
		if ((p = (*dst) = Dz1Asn1Any_new(src->buf, src->size, &err)) == NULL) ERR_OUT(&err);
	}
	
	return err;
}

static Dz1Error _ANY_toASN(ANY_t *dst, Dz1Asn1Any *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	OCTET_STRING_t *temp = NULL;

	if (src == NULL) ERR_SET_OUT(&err, EINVAL);

	else if (ANY_fromBuf((OCTET_STRING_t *)dst, src->data, src->size) < 0) ERR_SET_OUT(&err, EFAULT);

	return err;
}

static Dz1Error ANY_toASN(ANY_t **dst, Dz1Asn1Any *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ANY_t *p = NULL;
		if ((p = (*dst) = (ANY_t *)calloc(sizeof(ANY_t), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			pthread_cleanup_push(ANY_delAndSetNull, (void *)dst);

			if ((err = _ANY_toASN(p, src)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // (ANY_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error UTF8Str_fromASN(Dz1Asn1UTF8Str **dst, UTF8String_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Asn1UTF8Str *p = NULL;
		if ((p = (*dst) = Dz1Asn1UTF8Str_new(src->buf, src->size, &err)) == NULL) ERR_OUT(&err);
	}
	
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Time Fraction
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TimeFrac_fromASN(Iso14827TimeFrac **dst, struct time_SecondFractions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TimeFracPresent present;
	s32_t val;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->present == time_SecondFractions_PR_deci_seconds)
	{
		present = Iso14827TimeFracPresent_deci;
		val = (s32_t)src->choice.deci_seconds;
	}
	else if (src->present == time_SecondFractions_PR_centi_seconds)
	{
		present = Iso14827TimeFracPresent_centi;
		val = (s32_t)src->choice.centi_seconds;
	}
	else if (src->present == time_SecondFractions_PR_milli_seconds)
	{
		present = Iso14827TimeFracPresent_milli;
		val = (s32_t)src->choice.milli_seconds;
	}
	else { ERR_SET_OUT(&err, EINVAL); }

	if (err.code == 0 && ((*dst) = Iso14827TimeFrac_new(present, (void *)&val, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error Iso14827TimeFrac_toASN(struct time_SecondFractions **dst, Iso14827TimeFrac *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	{
		struct time_SecondFractions *p = NULL;
		if ((p = (*dst) = (struct time_SecondFractions *)calloc(sizeof(struct time_SecondFractions), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else if (src->present == Iso14827TimeFracPresent_deci)
		{
			p->present = time_SecondFractions_PR_deci_seconds;
			p->choice.centi_seconds = (long)src->x.deci;
		}
		else if (src->present == Iso14827TimeFracPresent_centi)
		{
			p->present = time_SecondFractions_PR_centi_seconds;
			p->choice.centi_seconds = (long)src->x.centi;
		}
		else if (src->present == Iso14827TimeFracPresent_milli)
		{
			p->present = time_SecondFractions_PR_milli_seconds;
			p->choice.milli_seconds = (long)src->x.milli;
		}
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Time Zone
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TimeZone_fromASN(Iso14827TimeZone **dst, struct time_Timezone *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	{
		s32_t h = 0, m = 0;
		Iso14827TimeZone *p = NULL;

		if (src->timezone_Hour_qty) h = (s32_t)src->timezone_Hour_qty;
		if (src->time_Minute_qty) m = (s32_t)src->time_Minute_qty;

		if ((p = (*dst) = Iso14827TimeZone_new(h, m, &err)) == NULL) ERR_OUT(&err);
	}

	return err;
}

static Dz1Error Iso14827TimeZone_toASN(struct time_Timezone **dst, Iso14827TimeZone *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	{
		struct time_Timezone *p = NULL;
		if ((p = (*dst) = (struct time_Timezone *)calloc(sizeof(struct time_Timezone), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else if (src->modH != 0 && (p->timezone_Hour_qty = Asn1Long_new(src->modH, &err)) == NULL) ERR_OUT(&err);
		else if (src->modM != 0 && (p->time_Minute_qty = Asn1Long_new(src->modM, &err)) == NULL) ERR_OUT(&err);
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// IsoTime
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Time_fromASN(Iso14827Time **dst, IsoTime_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Time *p = NULL;
		if ((p = (*dst) = Iso14827Time_new(NULL, NULL, NULL, 0, 0, 0, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Time_delAndSetNull, (void *)dst);
			if (src->time_Year_qty && (p->year = Dz1s32_new((s32_t)*src->time_Year_qty, &err)) == NULL) ERR_OUT(&err);
			else if (src->time_Month_qty && (p->month = Dz1s32_new((s32_t)*src->time_Month_qty, &err)) == NULL) ERR_OUT(&err);
			else if (src->time_Day_qty && (p->day = Dz1s32_new((s32_t)*src->time_Day_qty, &err)) == NULL) ERR_OUT(&err);
			else
			{

				if (src->time_Hour_qty) p->h = (s32_t)*src->time_Hour_qty;
				if (src->time_Minute_qty) p->m = (s32_t)*src->time_Minute_qty;
				if (src->time_Second_qty) p->s = (s32_t)*src->time_Second_qty;

				if (src->time_SecondFractions && (err = Iso14827TimeFrac_fromASN(&p->frac, src->time_SecondFractions)).code) ERR_OUT(&err);
				else if (src->time_Timezone && (err = Iso14827TimeZone_fromASN(&p->zone, src->time_Timezone)).code) ERR_OUT(&err);

			}
			pthread_cleanup_pop(err.code); // (Iso14827Time_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error Iso14827Time_toASN(IsoTime_t **dst, Iso14827Time *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime_t *p = NULL;
		if ((p = (*dst) = (IsoTime_t *)calloc(sizeof(IsoTime_t), 1)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(IsoTime_delAndSetNull, (void *)dst);
			if (src->year && (p->time_Year_qty = Asn1Long_new((long)(*src->year), &err)) == NULL) ERR_OUT(&err);
			else if (src->month && (p->time_Month_qty = Asn1Long_new((long)(*src->month), &err)) == NULL) ERR_OUT(&err);
			else if (src->day && (p->time_Day_qty = Asn1Long_new((long)(*src->day), &err)) == NULL) ERR_OUT(&err);
			else if (src->h > 0 && (p->time_Hour_qty = Asn1Long_new((long)src->h, &err)) == NULL) ERR_OUT(&err);
			else if (src->m > 0 && (p->time_Minute_qty = Asn1Long_new((long)src->m, &err)) == NULL) ERR_OUT(&err);
			else if (src->s > 0 && (p->time_Second_qty = Asn1Long_new((long)src->s, &err)) == NULL) ERR_OUT(&err);
			else if (src->frac && (err = Iso14827TimeFrac_toASN(&p->time_SecondFractions, src->frac)).code) ERR_OUT(&err);
			else if (src->zone && (err = Iso14827TimeZone_toASN(&p->time_Timezone, src->zone)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (IsoTime_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Cost
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Cost_fromASN(Iso14827Cost **dst, Cost_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Cost *p = NULL;
		if ((p = (*dst) = Iso14827Cost_new(NULL, (s32_t)src->amount_Factor_quantity, (s32_t)src->amount_Quantity_quantity, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Cost_delAndSetNull, (void *)dst);
			
			if ((p->currency = Dz1Asn1OctetStr_new(src->amount_Currency_code.buf, src->amount_Currency_code.size, &err)) == NULL) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827Cost_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827Cost_toASN(Cost_t **dst, Iso14827Cost *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Cost_t *p = NULL;
		if ((p = (*dst) = (Cost_t *)calloc(sizeof(Cost_t), 1)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Cost_delAndSetNull, (void *)dst);
			if (OCTET_STRING_fromBuf(&p->amount_Currency_code, src->currency->data, src->currency->size) < 0) ERR_SET_OUT(&err, EFAULT);
			else
			{
				p->amount_Quantity_quantity = src->qty;
				p->amount_Factor_quantity = src->factor;
			}
			pthread_cleanup_pop(err.code); // (Cost_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Header Option
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827HdrOpt_fromASN(Iso14827HdrOpt **dst, HeaderOptions_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827HdrOpt *p = NULL;
		if ((p = (*dst) = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827HdrOpt_delAndSetNull, (void *)dst);
			// Origin
			if (src->datex_Origin_text && (p->origin = Dz1Asn1UTF8Str_new(src->datex_Origin_text->buf, src->datex_Origin_text->size, &err)) == NULL) ERR_OUT(&err);
			else if (src->datex_OriginAddress_location && (p->originAddr = Dz1Asn1OctetStr_new(src->datex_OriginAddress_location->buf, src->datex_OriginAddress_location->size, &err)) == NULL) ERR_OUT(&err);
			// Destination
			else if (src->datex_Destination_text && (p->dest = Dz1Asn1UTF8Str_new(src->datex_Destination_text->buf, src->datex_Destination_text->size, &err)) == NULL) ERR_OUT(&err);
			else if (src->datex_DestinationAddress_location && (p->destAddr = Dz1Asn1OctetStr_new(src->datex_DestinationAddress_location->buf, src->datex_DestinationAddress_location->size, &err)) == NULL) ERR_OUT(&err);
			// Sender
			else if (src->datex_Sender_text && (p->sender = Dz1Asn1UTF8Str_new(src->datex_Sender_text->buf, src->datex_Sender_text->size, &err)) == NULL) ERR_OUT(&err);
			else if (src->datex_SenderAddress_location && (p->senderAddr = Dz1Asn1OctetStr_new(src->datex_SenderAddress_location->buf, src->datex_SenderAddress_location->size, &err)) == NULL) ERR_OUT(&err);
			// Cost
			else if (src->datex_Cost && (err = Iso14827Cost_fromASN(&p->cost, src->datex_Cost)).code) ERR_OUT(&err);
			// Time
			else if (src->datex_DataPacket_time && (err = Iso14827Time_fromASN(&p->t, src->datex_DataPacket_time)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827HdrOpt_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827HdrOpt_toASN(HeaderOptions_t *dst, Iso14827HdrOpt *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->origin && (dst->datex_Origin_text = OCTET_STRING_new_fromBuf(&asn_DEF_UTF8String, src->origin->data, src->origin->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->originAddr && (dst->datex_OriginAddress_location = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, src->originAddr->data, src->originAddr->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->sender && (dst->datex_Sender_text = OCTET_STRING_new_fromBuf(&asn_DEF_UTF8String, src->sender->data, src->sender->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->senderAddr && (dst->datex_SenderAddress_location = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, src->senderAddr->data, src->senderAddr->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->dest && (dst->datex_Destination_text = OCTET_STRING_new_fromBuf(&asn_DEF_UTF8String, src->dest->data, src->dest->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->destAddr && (dst->datex_DestinationAddress_location = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, src->destAddr->data, src->destAddr->size)) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (src->cost && (err = Iso14827Cost_toASN(&dst->datex_Cost, src->cost)).code) ERR_OUT(&err);
	else if (src->t && (err = Iso14827Time_toASN(&dst->datex_DataPacket_time, src->t)).code) ERR_OUT(&err);
	
	return err;
}

static Dz1Error Iso14827Initiate_toASN(Initiate_t *dst, Iso14827Initiate *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (OCTET_STRING_fromBuf(&dst->datex_Sender_txt, (char *)src->sender->data, src->sender->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else if (OCTET_STRING_fromBuf(&dst->datex_Destination_txt, (char *)src->dest->data, src->dest->size) < 0) ERR_SET_OUT(&err, EFAULT);

	return err;
}

static Dz1Error _Iso14827LoginOIDList_toASN(void *ptr, Dz1Asn1OID *oid)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	struct datexLogin_EncodingRules_id *dst = (struct datexLogin_EncodingRules_id *)ptr;

	OBJECT_IDENTIFIER_t *asnOID = NULL;

	if (oid == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = OID_toASN(&asnOID, oid)).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)OBJECT_IDENTIFIER_del, (void *)asnOID);
		if (ASN_SEQUENCE_ADD(dst, asnOID) < 0) ERR_SET_OUT(&err, EFAULT);
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)OBJECT_IDENTIFIER_del, (void *)asnOID);
	}
	return err;
}

static Dz1Error Iso14827LoginOIDList_toASN(struct datexLogin_EncodingRules_id *dst, Dz1OIDList *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = src->travel(src, _Iso14827LoginOIDList_toASN, dst)).code) ERR_OUT(&err);

	return err;
}

static Dz1Error Iso14827LoginInitiator_toASN(datexLogin_Initiator_cd_e *dst, Iso14827LoginInitiator src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827LoginInitiator_serverInitiated:
			*dst = datexLogin_Initiator_cd_serverInitiated;
			break;
		case Iso14827LoginInitiator_clientInitiated:
			*dst = datexLogin_Initiator_cd_clientInitiated;
			break;
		case Iso14827LoginInitiator_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

static Dz1Error Iso14827Login_toASN(Login_t *dst, Iso14827Login *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (OCTET_STRING_fromBuf(&dst->datex_Sender_txt, src->sender->data, src->sender->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else if (OCTET_STRING_fromBuf(&dst->datex_Destination_txt, src->dest->data, src->sender->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else if (OCTET_STRING_fromBuf(&dst->datexLogin_UserName_txt, src->user->data, src->user->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else if (OCTET_STRING_fromBuf(&dst->datexLogin_Password_txt, src->pass->data, src->pass->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = Iso14827LoginOIDList_toASN(&dst->datexLogin_EncodingRules_id, src->encRules)).code) ERR_OUT(&err);
	else
	{
		dst->datexLogin_HeartbeatDurationMax_qty = (long)src->hbDur;
		dst->datexLogin_ResponseTimeOut_qty = (long)src->timeout;
		if ((err = Iso14827LoginInitiator_toASN(&dst->datexLogin_Initiator_cd, src->initiator)).code) ERR_OUT(&err);
		else
		{
			dst->datexLogin_DatagramSize_qty = src->datagramSize;
		}
	}
	return err;
}

static Dz1Error Iso14827Terminate_toASN(Terminate_e *dst, Iso14827Terminate src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827Terminate_other:
			*dst = Terminate_other;
			break;
		case Iso14827Terminate_serverRequested:
			*dst = Terminate_serverRequested;
			break;
		case Iso14827Terminate_clientRequested:
			*dst = Terminate_clientRequested;
			break;
		case Iso14827Terminate_serverShutdown:
			*dst = Terminate_serverShutdown;
			break;
		case Iso14827Terminate_clientShutdown:
			*dst = Terminate_clientShutdown;
			break;
		case Iso14827Terminate_serverCommProblems:
			*dst = Terminate_serverCommProblems;
			break;
		case Iso14827Terminate_clientCommProblems:
			*dst = Terminate_clientCommProblems;
			break;
		case Iso14827Terminate_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

static Dz1Error Iso14827Logout_toASN(Logout_e *dst, Iso14827Logout src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827Logout_other:
			*dst = Logout_other;
			break;
		case Iso14827Logout_serverRequested:
			*dst = Logout_serverRequested;
			break;
		case Iso14827Logout_clientRequested:
			*dst = Logout_clientRequested;
			break;
		case Iso14827Logout_serverShutdown:
			*dst = Logout_serverShutdown;
			break;
		case Iso14827Logout_clientShutdown:
			*dst = Logout_clientShutdown;
			break;
		case Iso14827Logout_serverCommProblems:
			*dst = Logout_serverCommProblems;
			break;
		case Iso14827Logout_clientCommProblems:
			*dst = Logout_clientCommProblems;
			break;
		case Iso14827Logout_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// EndApplication Message
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827EndAppMsg_fromASN(Iso14827EndAppMsg **dst, EndApplicationMessage_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827EndAppMsg *p = NULL;
		if ((p = (*dst) = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827EndAppMsg_delAndSetNull, (void *)dst);
			
			if ((err = OID_fromASN(&p->oid, &src->endApplication_Message_id)).code) ERR_OUT(&err);
			else if ((err = ANY_fromASN(&p->data, &src->endApplication_Message_msg)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827EndAppMsg_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827EndAppMsg_toASN(EndApplicationMessage_t *dst, Iso14827EndAppMsg *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (OBJECT_IDENTIFIER_set_arcs(&dst->endApplication_Message_id, (void *)src->oid->data, sizeof(src->oid->data[0]), src->oid->cnt) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = _ANY_toASN(&dst->endApplication_Message_msg, src->data)).code) ERR_OUT(&err);
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationTypePresent_fromASN(Iso14827PublicationTypePresent *dst, PublicationType_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case PublicationType_PR_datexPublication_Management_cd:
			*dst = Iso14827PublicationTypePresent_mgmt;
			break;
		case PublicationType_PR_datexPublish_Data:
			*dst = Iso14827PublicationTypePresent_msg;
			break;
		case PublicationType_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublicationTypePresent_toASN(PublicationType_PR *dst, Iso14827PublicationTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublicationTypePresent_mgmt:
		*dst = PublicationType_PR_datexPublication_Management_cd;
		break;
	case Iso14827PublicationTypePresent_msg:
		*dst = PublicationType_PR_datexPublish_Data;
		break;
	case Iso14827PublicationTypePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Management
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationMgmt_fromASN(Iso14827PublicationMgmt *dst, datexPublication_Management_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case datexPublication_Management_cd_temporarilySuspended:
			*dst = Iso14827PublicationMgmt_temporarilySuspended;
			break;
		case datexPublication_Management_cd_resume:
			*dst = Iso14827PublicationMgmt_resume;
			break;
		case datexPublication_Management_cd_terminate_other:
			*dst = Iso14827PublicationMgmt_terminateOther;
			break;
		case datexPublication_Management_cd_terminate_dataNoLongerAvailable:
			*dst = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
			break;
		case datexPublication_Management_cd_terminate_publicationsBeingRejected:
			*dst = Iso14827PublicationMgmt_terminatePublicationsBeingRejected;
			break;
		case datexPublication_Management_cd_terminate_PendingShutdown:
			*dst = Iso14827PublicationMgmt_terminatePendingShutdown;
			break;
		case datexPublication_Management_cd_terminate_processingMgmt:
			*dst = Iso14827PublicationMgmt_terminateProcessingMgmt;
			break;
		case datexPublication_Management_cd_terminate_bandwidthMgmt:
			*dst = Iso14827PublicationMgmt_terminateBandwidthMgmt;
			break;
		case datexPublication_Management_cd_terminate_accessDenied:
			*dst = Iso14827PublicationMgmt_terminateAccessDenied;
			break;
		case datexPublication_Management_cd_unknownRequest:
			*dst = Iso14827PublicationMgmt_unknownRequest;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublicationMgmt_toASN(datexPublication_Management_cd_e *dst, Iso14827PublicationMgmt src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublicationMgmt_temporarilySuspended:
		*dst = datexPublication_Management_cd_temporarilySuspended;
		break;
	case Iso14827PublicationMgmt_resume:
		*dst = datexPublication_Management_cd_resume;
		break;
	case Iso14827PublicationMgmt_terminateOther:
		*dst = datexPublication_Management_cd_terminate_other;
		break;
	case Iso14827PublicationMgmt_terminateDataNoLongerAvailable:
		*dst = datexPublication_Management_cd_terminate_dataNoLongerAvailable;
		break;
	case Iso14827PublicationMgmt_terminatePublicationsBeingRejected:
		*dst = datexPublication_Management_cd_terminate_publicationsBeingRejected;
		break;
	case Iso14827PublicationMgmt_terminatePendingShutdown:
		*dst = datexPublication_Management_cd_terminate_PendingShutdown;
		break;
	case Iso14827PublicationMgmt_terminateProcessingMgmt:
		*dst = datexPublication_Management_cd_terminate_processingMgmt;
		break;
	case Iso14827PublicationMgmt_terminateBandwidthMgmt:
		*dst = datexPublication_Management_cd_terminate_bandwidthMgmt;
		break;
	case Iso14827PublicationMgmt_terminateAccessDenied:
		*dst = datexPublication_Management_cd_terminate_accessDenied;
		break;
	case Iso14827PublicationMgmt_unknownRequest:
		*dst = datexPublication_Management_cd_unknownRequest;
		break;
	case Iso14827PublicationMgmt_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Type
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationType_fromASN(Iso14827PublicationType **dst, PublicationType_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827PublicationType *p = NULL;
		Iso14827PublicationTypePresent present;
		if ((err = Iso14827PublicationTypePresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827PublicationType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		{
			pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827PublicationTypePresent_mgmt:
				if ((err = Iso14827PublicationMgmt_fromASN(&p->x.mgmt, src->choice.datexPublication_Management_cd)).code) ERR_OUT(&err);
				break;
			case Iso14827PublicationTypePresent_msg:
				if ((err = Iso14827EndAppMsg_fromASN(&p->x.msg, &src->choice.datexPublish_Data)).code) ERR_OUT(&err);
			}
			pthread_cleanup_pop(err.code); // (Iso14827PublicationType_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827PublicationType_toASN(PublicationType_t *dst, Iso14827PublicationType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827PublicationTypePresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case PublicationType_PR_datexPublication_Management_cd:
			if ((err = Iso14827PublicationMgmt_toASN(&dst->choice.datexPublication_Management_cd, src->x.mgmt)).code) ERR_OUT(&err);
			break;
		case PublicationType_PR_datexPublish_Data:
			if ((err = Iso14827EndAppMsg_toASN(&dst->choice.datexPublish_Data, src->x.msg)).code) ERR_OUT(&err);
			break;
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationData_fromASN(Iso14827PublicationData **dst, PublicationData_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long subSerial, serial;
		Iso14827PublicationData *p = NULL;
		if (asn_INTEGER2long(&src->datexPublish_SubscribeSerial_nbr, &subSerial) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (asn_INTEGER2long(&src->datexPublish_Serial_nbr, &serial) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((p = (*dst) = Iso14827PublicationData_new((u32_t)subSerial, (u32_t)serial,
			src->datexPublish_LatePublicationFlag ? TRUE : FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827PublicationType_fromASN(&p->type, &src->datexPublish_Type)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827PublicationData_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827PublicationData_toASN(PublicationData_t **dst, Iso14827PublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		PublicationData_t *p = NULL;
		if ((p = (*dst) = (PublicationData_t *)calloc(sizeof(PublicationData_t), 1)) == NULL) ERR_SET_OUT(&err, EFAULT);
		else
		{
			pthread_cleanup_push(PublicationData_delAndSetNull, (void *)dst);
			if (asn_long2INTEGER(&p->datexPublish_SubscribeSerial_nbr, (long)src->subscriptionSerial) < 0) ERR_SET_OUT(&err, EFAULT);
			else if (asn_long2INTEGER(&p->datexPublish_Serial_nbr, (long)src->serial) < 0) ERR_SET_OUT(&err, EFAULT);
			else
			{
				p->datexPublish_LatePublicationFlag = src->isLated ? TRUE : FALSE;
				if ((err = Iso14827PublicationType_toASN(&p->datexPublish_Type, src->type)).code) ERR_OUT(&err);
			}
			pthread_cleanup_pop(err.code); // (PublicationData_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data List
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationDataList_fromASN(Iso14827PublicationDataList **dst, struct datexPublish_Data *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827PublicationDataList *p = NULL;
		if ((p = (*dst) = Iso14827PublicationDataList_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			int i;
			Iso14827PublicationData *e = NULL;
			pthread_cleanup_push(Iso14827PublicationDataList_delAndSetNull, (void *)dst);
			for (i = 0; err.code == 0 && i < src->list.count; i++)
			{
				if ((err = Iso14827PublicationData_fromASN(&e, src->list.array[i])).code) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&e);
					
					if ((err = p->add(p, e)).code) ERR_OUT(&err);
					else e = NULL;
					
					pthread_cleanup_pop(1); // (Iso14827PublicationData_delAndSetNull, (void *)&e);
				}
			}
			pthread_cleanup_pop(err.code); // (Iso14827PublicationDataList_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data List
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _Iso14827PublicationDataList_toASN(void *ptr, Iso14827PublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	struct datexPublish_Data *dst = (struct datexPublish_Data *)ptr;
	PublicationData_t *p = NULL;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827PublicationData_toASN(&p, src)).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)PublicationData_del, (void *)p);
		
		if (ASN_SEQUENCE_ADD(dst, p) < 0) ERR_SET_OUT(&err, EFAULT);
		
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)PublicationData_del, (void *)p);
	}
	
	return err;
}

static Dz1Error Iso14827PublicationDataList_toASN(struct datexPublish_Data *dst, Iso14827PublicationDataList *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = src->travel(src, _Iso14827PublicationDataList_toASN, dst)).code) ERR_OUT(&err);
	
	return err;
}

static Dz1Error Iso14827RejectTypePresent_toASN(RejectType_PR *dst, Iso14827RejectTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectTypePresent_login:
			*dst = RejectType_PR_datexReject_Login_cd;
			break;
		case Iso14827RejectTypePresent_subscription:
			*dst = RejectType_PR_datexReject_Subscription_cd;
			break;
		case Iso14827RejectTypePresent_publication:
			*dst = RejectType_PR_datexReject_Publication_cd;
			break;
		case Iso14827RejectTypePresent_pubData:
			*dst = RejectType_PR_rejectPublicationData;
			break;
		case Iso14827RejectTypePresent_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

static Dz1Error Iso14827Initiate_fromASN(Iso14827Initiate **dst, Initiate_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Initiate *p = NULL;
		if ((p = (*dst) = Iso14827Initiate_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Initiate_delAndSetNull, (void *)dst);
			if ((p->dest = Dz1Asn1UTF8Str_new(src->datex_Destination_txt.buf, src->datex_Destination_txt.size, &err)) == NULL) ERR_OUT(&err);
			else if ((p->sender = Dz1Asn1UTF8Str_new(src->datex_Sender_txt.buf, src->datex_Sender_txt.size, &err)) == NULL) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Initiate_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827LoginInitiator_fromASN(Iso14827LoginInitiator *dst, datexLogin_Initiator_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexLogin_Initiator_cd_serverInitiated:
				*dst = Iso14827LoginInitiator_serverInitiated;
				break;
			case datexLogin_Initiator_cd_clientInitiated:
				*dst = Iso14827LoginInitiator_clientInitiated;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

static Dz1Error Iso14827LoginOIDList_fromASN(Dz1OIDList *dst, struct datexLogin_EncodingRules_id *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	OBJECT_IDENTIFIER_t *asnOID = NULL;
	Dz1Asn1OID *oid = NULL;
	int i;
	for (i = 0; i < src->list.count; i++)
	{
		asnOID = src->list.array[i];
		if ((err = OID_fromASN(&oid, asnOID)).code) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Asn1OID_del, (void *)oid);

			if ((err = dst->add(dst, oid)).code) ERR_OUT(&err);
			else oid = NULL;

			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1Asn1OID_del, (void *)oid);
		}
	}
	return err;
}

static Dz1Error Iso14827Login_fromASN(Iso14827Login **dst, Login_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Login *p;
		Iso14827LoginInitiator initiator;
		if ((err = Iso14827LoginInitiator_fromASN(&initiator, src->datexLogin_Initiator_cd)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Login_new(NULL, NULL, NULL, NULL, src->datexLogin_HeartbeatDurationMax_qty, src->datexLogin_ResponseTimeOut_qty, initiator, src->datexLogin_DatagramSize_qty, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Login_delAndSetNull, (void *)dst);
			if ((p->sender = Dz1Asn1UTF8Str_new(src->datex_Sender_txt.buf, src->datex_Sender_txt.size, &err)) == NULL) ERR_OUT(&err);
			else if ((p->dest = Dz1Asn1UTF8Str_new(src->datex_Destination_txt.buf, src->datex_Destination_txt.size	, &err)) == NULL) ERR_OUT(&err);
			else if ((p->user = Dz1Asn1OctetStr_new(src->datexLogin_UserName_txt.buf, src->datexLogin_UserName_txt.size, &err)) == NULL) ERR_OUT(&err);
			else if ((p->pass = Dz1Asn1OctetStr_new(src->datexLogin_Password_txt.buf, src->datexLogin_Password_txt.size, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Iso14827LoginOIDList_fromASN(p->encRules, &src->datexLogin_EncodingRules_id)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Login_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Terminate_fromASN(Iso14827Terminate *dst, Terminate_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case Terminate_other:
				*dst = Iso14827Terminate_other;
				break;
			case Terminate_serverRequested:
				*dst = Iso14827Terminate_serverRequested;
				break;
			case Terminate_clientRequested:
				*dst = Iso14827Terminate_clientRequested;
				break;
			case Terminate_serverShutdown:
				*dst = Iso14827Terminate_serverShutdown;
				break;
			case Terminate_clientShutdown:
				*dst = Iso14827Terminate_clientShutdown;
				break;
			case Terminate_serverCommProblems:
				*dst = Iso14827Terminate_serverCommProblems;
				break;
			case Terminate_clientCommProblems:
				*dst = Iso14827Terminate_clientCommProblems;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

static Dz1Error Iso14827Logout_fromASN(Iso14827Logout *dst, Logout_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case Logout_other:
				*dst = Iso14827Logout_other;
				break;
			case Logout_serverRequested:
				*dst = Iso14827Logout_serverRequested;
				break;
			case Logout_clientRequested:
				*dst = Iso14827Logout_clientRequested;
				break;
			case Logout_serverShutdown:
				*dst = Iso14827Logout_serverShutdown;
				break;
			case Logout_clientShutdown:
				*dst = Iso14827Logout_clientShutdown;
				break;
			case Logout_serverCommProblems:
				*dst = Iso14827Logout_serverCommProblems;
				break;
			case Logout_clientCommProblems:
				*dst = Iso14827Logout_clientCommProblems;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionTypePresent_fromASN(Iso14827SubscriptionTypePresent *dst, SubscriptionType_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case SubscriptionType_PR_subscription:
			*dst = Iso14827SubscriptionTypePresent_data;
			break;
		case SubscriptionType_PR_datexSubscribe_CancelReason_cd:
			*dst = Iso14827SubscriptionTypePresent_reason;
			break;
		case SubscriptionType_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionTypePresent_toASN(SubscriptionType_PR *dst, Iso14827SubscriptionTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionTypePresent_data:
		*dst = SubscriptionType_PR_subscription;
		break;
	case Iso14827SubscriptionTypePresent_reason:
		*dst = SubscriptionType_PR_datexSubscribe_CancelReason_cd;
		break;
	case Iso14827SubscriptionTypePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Status
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataStatus_fromASN(Iso14827SubscriptionDataStatus *dst, datexSubscribe_Status_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case datexSubscribe_Status_cd_new:
			*dst = Iso14827SubscriptionDataStatus_NEW;
			break;
		case datexSubscribe_Status_cd_update:
			*dst = Iso14827SubscriptionDataStatus_UPDATED;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionDataStatus_toASN(datexSubscribe_Status_cd_e *dst, Iso14827SubscriptionDataStatus src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataStatus_NEW:
		*dst = datexSubscribe_Status_cd_new;
		break;
	case Iso14827SubscriptionDataStatus_UPDATED:
		*dst = datexSubscribe_Status_cd_update;
		break;
	case Iso14827SubscriptionDataStatus_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Format
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataFormat_fromASN(Iso14827SubscriptionDataFormat *dst, datexSubscribe_PublishFormat_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case datexSubscribe_PublishFormat_cd_other:
			*dst = Iso14827SubscriptionDataFormat_other;
			break;
		case datexSubscribe_PublishFormat_cd_ftp:
			*dst = Iso14827SubscriptionDataFormat_ftp;
			break;
		case datexSubscribe_PublishFormat_cd_tftp:
			*dst = Iso14827SubscriptionDataFormat_tftp;
			break;
		case datexSubscribe_PublishFormat_cd_dataPacket:
			*dst = Iso14827SubscriptionDataFormat_dataPacket;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionDataFormat_toASN(datexSubscribe_PublishFormat_cd_e *dst, Iso14827SubscriptionDataFormat src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataFormat_other:
		*dst = datexSubscribe_PublishFormat_cd_other;
		break;
	case Iso14827SubscriptionDataFormat_ftp:
		*dst = datexSubscribe_PublishFormat_cd_ftp;
		break;
	case Iso14827SubscriptionDataFormat_tftp:
		*dst = datexSubscribe_PublishFormat_cd_tftp;
		break;
	case Iso14827SubscriptionDataFormat_dataPacket:
		*dst = datexSubscribe_PublishFormat_cd_dataPacket;
		break;
	case Iso14827SubscriptionDataFormat_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Mode Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataModePresent_fromASN(Iso14827SubscriptionDataModePresent *dst, SubscriptionMode_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case SubscriptionMode_PR_single:
		*dst = Iso14827SubscriptionDataModePresent_single;
		break;
	case SubscriptionMode_PR_event_driven:
		*dst = Iso14827SubscriptionDataModePresent_eventDriven;
		break;
	case SubscriptionMode_PR_periodic:
		*dst = Iso14827SubscriptionDataModePresent_periodic;
		break;
	case SubscriptionMode_PR_NOTHING:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

static Dz1Error Iso14827SubscriptionDataModePresent_toASN(SubscriptionMode_PR *dst, Iso14827SubscriptionDataModePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataModePresent_single:
		*dst = SubscriptionMode_PR_single;
		break;
	case Iso14827SubscriptionDataModePresent_eventDriven:
		*dst = SubscriptionMode_PR_event_driven;
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		*dst = SubscriptionMode_PR_periodic;
		break;
	case Iso14827SubscriptionDataModePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
		
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredPresent_fromASN(Iso14827RegisteredPresent *dst, Registered_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Registered_PR_continuous:
		*dst = Iso14827RegisteredPresent_continuous;
		break;
	case Registered_PR_daily:
		*dst = Iso14827RegisteredPresent_daily;
		break;
	case Registered_PR_NOTHING:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredPresent_toASN(Registered_PR *dst, Iso14827RegisteredPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RegisteredPresent_continuous:
		*dst = Registered_PR_continuous;
		break;
	case Iso14827RegisteredPresent_daily:
		*dst = Registered_PR_daily;
		break;
	case Iso14827RegisteredPresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Continuous
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredContinuous_fromASN(Iso14827RegisteredContinuous **dst, struct continuous *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long updateDelay = 0;
		Iso14827RegisteredContinuous *p = NULL;
		if (src->datexRegistered_UpdateDelay_qty && asn_INTEGER2long(src->datexRegistered_UpdateDelay_qty, &updateDelay) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((p = (*dst) = Iso14827RegisteredContinuous_new((u32_t)updateDelay, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827RegisteredContinuous_delAndSetNull, (void *)dst);
			if (src->datexRegistered_StartTime && (err = Iso14827Time_fromASN(&p->start, src->datexRegistered_StartTime)).code) ERR_OUT(&err);
			else if (src->datexRegistered_EndTime && (err = Iso14827Time_fromASN(&p->end, src->datexRegistered_EndTime)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827RegisteredContinuous_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredContinuous_toASN(struct continuous *dst, Iso14827RegisteredContinuous *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->updateDelay > 0 && (dst->datexRegistered_UpdateDelay_qty = INTEGER_new((long)src->updateDelay, &err)) == NULL) ERR_OUT(&err);
	else if (src->start && (err = Iso14827Time_toASN(&dst->datexRegistered_StartTime, src->start)).code) ERR_OUT(&err);
	else if (src->end && (err = Iso14827Time_toASN(&dst->datexRegistered_EndTime, src->end)).code) ERR_OUT(&err);
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Daily
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredDaily_fromASN(Iso14827RegisteredDaily **dst, struct daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		u8_t dow = src->datexRegistered_DaysOfWeek_cd.buf[0];
		long updateDelay = 0;
		Iso14827RegisteredDaily *p = NULL;
		if (src->datexRegistered_UpdateDelay_qty && asn_INTEGER2long(src->datexRegistered_UpdateDelay_qty, &updateDelay) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((p = (*dst) = Iso14827RegisteredDaily_new(updateDelay, dow, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827RegisteredDaily_delAndSetNull, (void *)dst);
			
			if (src->datexRegistered_StartDate && (err = Iso14827Time_fromASN(&p->startDate, src->datexRegistered_StartDate)).code) ERR_OUT(&err);
			else if (src->datexRegistered_EndDate && (err = Iso14827Time_fromASN(&p->endDate, src->datexRegistered_EndDate)).code) ERR_OUT(&err);
			else if (src->datexRegistered_StartTime && (err = Iso14827Time_fromASN(&p->startTime, src->datexRegistered_StartTime)).code) ERR_OUT(&err);
			else if (src->datexRegistered_Duration_qty && (p->duration = Dz1u16_new((u16_t)(*src->datexRegistered_Duration_qty), &err)) == NULL) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827RegisteredDaily_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredDaily_toASN(struct daily *dst, Iso14827RegisteredDaily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->updateDelay > 0 && (dst->datexRegistered_UpdateDelay_qty = INTEGER_new((long)src->updateDelay, &err)) == NULL) ERR_OUT(&err);
	else if (src->startDate &&  (err = Iso14827Time_toASN(&dst->datexRegistered_StartDate, src->startDate)).code) ERR_OUT(&err);
	else if (src->endDate && (err = Iso14827Time_toASN(&dst->datexRegistered_EndDate, src->endDate)).code) ERR_OUT(&err);
	else if (src->startTime && (err = Iso14827Time_toASN(&dst->datexRegistered_StartTime, src->startTime)).code) ERR_OUT(&err);
	else if (src->duration && (dst->datexRegistered_Duration_qty = Asn1Long_new((long)*src->duration, &err)) == NULL) ERR_OUT(&err);
	else if ((dst->datexRegistered_DaysOfWeek_cd.buf = (u8_t *)calloc(sizeof(u8_t), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else { *dst->datexRegistered_DaysOfWeek_cd.buf = src->daysOfWeek; dst->datexRegistered_DaysOfWeek_cd.size = 1; }
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Registered_fromASN(Iso14827Registered **dst, Registered_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Registered *p = NULL;
		Iso14827RegisteredPresent present;
		if ((err = Iso14827RegisteredPresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Registered_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Registered_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827RegisteredPresent_continuous:
				if ((err = Iso14827RegisteredContinuous_fromASN(&p->x.continuous, &src->choice.continuous)).code) ERR_OUT(&err);
				break;
			case Iso14827RegisteredPresent_daily:
				if ((err = Iso14827RegisteredDaily_fromASN(&p->x.daily, &src->choice.daily)).code) ERR_OUT(&err);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827Registered_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Registered_toASN(Registered_t *dst, Iso14827Registered *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827RegisteredPresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
			case Registered_PR_continuous:
				if ((err = Iso14827RegisteredContinuous_toASN(&dst->choice.continuous, src->x.continuous)).code) ERR_OUT(&err);
				break;
			case Registered_PR_daily:
				if ((err = Iso14827RegisteredDaily_toASN(&dst->choice.daily, src->x.daily)).code) ERR_OUT(&err);
				break;
		}
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Mode
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataMode_fromASN(Iso14827SubscriptionDataMode **dst, SubscriptionMode_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827SubscriptionDataMode *p = NULL;
		Iso14827SubscriptionDataModePresent present;
		if ((err = Iso14827SubscriptionDataModePresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionDataMode_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		{
			pthread_cleanup_push(Iso14827SubscriptionDataMode_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827SubscriptionDataModePresent_single:
				break;
			case Iso14827SubscriptionDataModePresent_eventDriven:
				if ((err = Iso14827Registered_fromASN(&p->x.eventDriven, &src->choice.event_driven)).code) ERR_OUT(&err);
				break;
			case Iso14827SubscriptionDataModePresent_periodic:
				if ((err = Iso14827Registered_fromASN(&p->x.periodic, &src->choice.periodic)).code) ERR_OUT(&err);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionDataMode_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827SubscriptionDataMode_toASN(SubscriptionMode_t *dst, Iso14827SubscriptionDataMode *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827SubscriptionDataModePresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case SubscriptionMode_PR_single:
			break;
		case SubscriptionMode_PR_event_driven:
			if ((err = Iso14827Registered_toASN(&dst->choice.event_driven, src->x.eventDriven)).code) ERR_OUT(&err);
			break;
		case SubscriptionMode_PR_periodic:
			if ((err = Iso14827Registered_toASN(&dst->choice.periodic, src->x.periodic)).code) ERR_OUT(&err);
			break;
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionData_fromASN(Iso14827SubscriptionData **dst, SubscriptionData_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827SubscriptionData *p = NULL;
		Iso14827SubscriptionDataStatus status;
		Iso14827SubscriptionDataFormat fmt;
		if ((err = Iso14827SubscriptionDataStatus_fromASN(&status, src->datexSubscribe_Status_cd)).code) ERR_OUT(&err);
		else if ((err = Iso14827SubscriptionDataFormat_fromASN(&fmt, src->datexSubscribe_PublishFormat_cd)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionData_new(src->datexSubscribe_Guarantee_bool ? TRUE : FALSE,
			status, NULL, fmt, (s32_t)src->datexSubscription_Priority_nbr,
			src->datexSubscribe_Guarantee_bool ? TRUE : FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827SubscriptionData_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827SubscriptionDataMode_fromASN(&p->mode, &src->datexSubscribe_Mode)).code) ERR_OUT(&err);
			else if ((err = Iso14827EndAppMsg_fromASN(&p->msg, &src->datexSubscribe_Pdu)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionData_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionData_toASN(SubscriptionData_t *dst, Iso14827SubscriptionData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else 
	{
		dst->datexSubscribe_Persistent_bool = src->persistent ? TRUE : FALSE;
		if ((err = Iso14827SubscriptionDataStatus_toASN(&dst->datexSubscribe_Status_cd, src->status)).code) ERR_OUT(&err);
		else if ((err = Iso14827SubscriptionDataMode_toASN(&dst->datexSubscribe_Mode, src->mode)).code) ERR_OUT(&err);
		else if ((err = Iso14827SubscriptionDataFormat_toASN(&dst->datexSubscribe_PublishFormat_cd, src->fmt)).code) ERR_OUT(&err);
		else
		{
			dst->datexSubscription_Priority_nbr = (long)src->priority;
			dst->datexSubscribe_Guarantee_bool = src->guarantee ? TRUE : FALSE;
			if ((err = Iso14827EndAppMsg_toASN(&dst->datexSubscribe_Pdu, src->msg)).code) ERR_OUT(&err);
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Cancel
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionCancel_fromASN(Iso14827SubscriptionCancel *dst, datexSubscribe_CancelReason_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexSubscribe_CancelReason_cd_other:
				*dst = Iso14827SubscriptionCancel_other;
				break;
			case datexSubscribe_CancelReason_cd_dataNotNeeded:
				*dst = Iso14827SubscriptionCancel_dataNotNeeded;
				break;
			case datexSubscribe_CancelReason_cd_errorsInPublication:
				*dst = Iso14827SubscriptionCancel_errorsInPublication;
				break;
			case datexSubscribe_CancelReason_cd_pendingLogout:
				*dst = Iso14827SubscriptionCancel_pendingLogout;
				break;
			case datexSubscribe_CancelReason_cd_processingMgmt:
				*dst = Iso14827SubscriptionCancel_processingMgmt;
				break;
			case datexSubscribe_CancelReason_cd_bandwidthMgmt:
				*dst = Iso14827SubscriptionCancel_bandwidthMgmt;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionCancel_toASN(datexSubscribe_CancelReason_cd_e *dst, Iso14827SubscriptionCancel src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionCancel_other:
		*dst = datexSubscribe_CancelReason_cd_other;
		break;
	case Iso14827SubscriptionCancel_dataNotNeeded:
		*dst = datexSubscribe_CancelReason_cd_dataNotNeeded;
		break;
	case Iso14827SubscriptionCancel_errorsInPublication:
		*dst = datexSubscribe_CancelReason_cd_errorsInPublication;
		break;
	case Iso14827SubscriptionCancel_pendingLogout:
		*dst = datexSubscribe_CancelReason_cd_pendingLogout;
		break;
	case Iso14827SubscriptionCancel_processingMgmt:
		*dst = datexSubscribe_CancelReason_cd_processingMgmt;
		break;
	case Iso14827SubscriptionCancel_bandwidthMgmt:
		*dst = datexSubscribe_CancelReason_cd_bandwidthMgmt;
		break;
	case Iso14827SubscriptionCancel_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Type
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionType_fromASN(Iso14827SubscriptionType **dst, SubscriptionType_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827SubscriptionType *p = NULL;
		Iso14827SubscriptionTypePresent present;
		if ((err = Iso14827SubscriptionTypePresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827SubscriptionType_delAndSetNull, (void *)dst);
			switch(p->present)
			{
				case Iso14827SubscriptionTypePresent_data:
					if ((err = Iso14827SubscriptionData_fromASN(&p->x.data, &src->choice.subscription)).code) ERR_OUT(&err);
					break;
				case Iso14827SubscriptionTypePresent_reason:
					if ((err = Iso14827SubscriptionCancel_fromASN(&p->x.reason, src->choice.datexSubscribe_CancelReason_cd)).code) ERR_OUT(&err);
					break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionType_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error _Iso14827SubscriptionType_toASN(SubscriptionType_t *dst, Iso14827SubscriptionType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827SubscriptionTypePresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case SubscriptionType_PR_subscription:
			if ((err = Iso14827SubscriptionData_toASN(&dst->choice.subscription, src->x.data)).code) ERR_OUT(&err);
			break;
		case SubscriptionType_PR_datexSubscribe_CancelReason_cd:
			if ((err = Iso14827SubscriptionCancel_toASN(&dst->choice.datexSubscribe_CancelReason_cd, src->x.reason)).code) ERR_OUT(&err);
			break;
		}
	}
	
	return err;
}

static Dz1Error Iso14827SubscriptionType_toASN(SubscriptionType_t **dst, Iso14827SubscriptionType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		SubscriptionType_t *p = NULL;
		if ((p = (*dst) = (SubscriptionType_t *)calloc(sizeof(SubscriptionType_t), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			pthread_cleanup_push(SubscriptionType_delAndSetNull, (void *)dst);
			if ((err = _Iso14827SubscriptionType_toASN(p, src)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (SubscriptionType_delAdnSetNull, (void *)dst);
		}
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Subscription_fromASN(Iso14827Subscription **dst, Subscription_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long serial;
		Iso14827Subscription *p = NULL;
		if (asn_INTEGER2long(&src->datexSubscribe_Serial_nbr, &serial) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((p = (*dst) = Iso14827Subscription_new((u32_t)serial, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Subscription_delAndSetNull, (void *)dst);

			if ((err = Iso14827SubscriptionType_fromASN(&p->type, &src->datexSubscribe_Type)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // (Iso14827Subscription_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Subscription_toASN(Subscription_t *dst, Iso14827Subscription *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (asn_long2INTEGER(&dst->datexSubscribe_Serial_nbr, (long)src->serial) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = _Iso14827SubscriptionType_toASN(&dst->datexSubscribe_Type, src->type)).code) ERR_OUT(&err);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Format Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublishFormatPresent_fromASN(Iso14827PublishFormatPresent *dst, Publish_Format_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case Publish_Format_PR_datexPublish_Data:
				*dst = Iso14827PublishFormatPresent_dataList;
				break;
			case Publish_Format_PR_datexPublish_FileName_txt:
				*dst = Iso14827PublishFormatPresent_filename;
				break;
			case Publish_Format_PR_NOTHING:
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublishFormatPresent_toASN(Publish_Format_PR *dst, Iso14827PublishFormatPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublishFormatPresent_dataList:
		*dst = Publish_Format_PR_datexPublish_Data;
		break;
	case Iso14827PublishFormatPresent_filename:
		*dst = Publish_Format_PR_datexPublish_FileName_txt;
		break;
	case Iso14827PublishFormatPresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublishFormat_fromASN(Iso14827PublishFormat **dst, Publish_Format_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827PublishFormat *p = NULL;
		Iso14827PublishFormatPresent present;
		if ((err = Iso14827PublishFormatPresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827PublishFormat_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827PublishFormat_delAndSetNull, (void *)dst);

			switch(p->present)
			{
				case Iso14827PublishFormatPresent_dataList:
					if ((err = Iso14827PublicationDataList_fromASN(&p->x.dataList, &src->choice.datexPublish_Data)).code) ERR_OUT(&err);
					break;
				case Iso14827PublishFormatPresent_filename:
					if ((err = UTF8Str_fromASN(&p->x.filename, &src->choice.datexPublish_FileName_txt)).code) ERR_OUT(&err);
					break;
			}

			pthread_cleanup_pop(err.code); //(Iso14827PublishFormat_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error Iso14827PublishFormat_toASN(Publish_Format_t *dst, Iso14827PublishFormat *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827PublishFormatPresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case Publish_Format_PR_datexPublish_Data:
			if ((err = Iso14827PublicationDataList_toASN(&dst->choice.datexPublish_Data, src->x.dataList)).code) ERR_OUT(&err);
			break;
		case Publish_Format_PR_datexPublish_FileName_txt:
			if (OCTET_STRING_fromBuf(&dst->choice.datexPublish_FileName_txt, (char *)src->x.filename->data, src->x.filename->size) < 0) ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Publication
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Publication_fromASN(Iso14827Publication **dst, Publication_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Publication *p = NULL;
		if ((p = (*dst) = Iso14827Publication_new(src->datexPublish_Guaranteed_bool ? TRUE : FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Publication_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827PublishFormat_fromASN(&p->fmt, &src->datexPublish_Format)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827Publication_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Publication_toASN(Publication_t *dst, Iso14827Publication *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else 
	{
		dst->datexPublish_Guaranteed_bool = src->guaranteed ? TRUE : FALSE;
		if ((err = Iso14827PublishFormat_toASN(&dst->datexPublish_Format, src->fmt)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Transfer Done
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TransferDone_fromASN(Iso14827TransferDone **dst, TransferDone_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827TransferDone *p = NULL;
		if ((p = (*dst) = Iso14827TransferDone_new(NULL, src->datexTransferDone_Success_bool ? TRUE : FALSE, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827TransferDone_delAndSetNull, (void *)dst);
			if ((p->filename = Dz1Asn1UTF8Str_new(src->datexTransferDone_FileName_txt.buf, src->datexTransferDone_FileName_txt.size, &err)) == NULL) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827TransferDone_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827TransferDone_toASN(TransferDone_t *dst, Iso14827TransferDone *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (OCTET_STRING_fromBuf(&dst->datexTransferDone_FileName_txt, (char *)src->filename->data, src->filename->size) < 0) ERR_SET_OUT(&err, EFAULT);
	else
	{
		dst->datexTransferDone_Success_bool = src->isSuccess ? TRUE : FALSE;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827AcceptTypePresent_fromASN(Iso14827AcceptTypePresent *dst, datexAccept_Type_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexAccept_Type_PR_login:
				*dst = Iso14827AcceptTypePresent_login;
				break;
			case datexAccept_Type_PR_single_subscription:
				*dst = Iso14827AcceptTypePresent_singleSubscription;
				break;
			case datexAccept_Type_PR_registered_subscription:
				*dst = Iso14827AcceptTypePresent_registeredSubscription;
				break;
			case datexAccept_Type_PR_publication:
				*dst = Iso14827AcceptTypePresent_publication;
				break;
			case datexAccept_Type_PR_NOTHING:
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}

	return err;
}

static Dz1Error Iso14827AcceptTypePresent_toASN(datexAccept_Type_PR *dst, Iso14827AcceptTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827AcceptTypePresent_login:
		*dst = datexAccept_Type_PR_login;
		break;
	case Iso14827AcceptTypePresent_singleSubscription:
		*dst = datexAccept_Type_PR_single_subscription;
		break;
	case Iso14827AcceptTypePresent_registeredSubscription:
		*dst = datexAccept_Type_PR_registered_subscription;
		break;
	case Iso14827AcceptTypePresent_publication:
		*dst = datexAccept_Type_PR_publication;
		break;
	case Iso14827AcceptTypePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept Type
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827AcceptType_fromASN(Iso14827AcceptType **dst, struct datexAccept_Type *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827AcceptType *p = NULL;
		Iso14827AcceptTypePresent present;
		if ((err = Iso14827AcceptTypePresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827AcceptType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			long val;
			pthread_cleanup_push(Iso14827AcceptType_delAndSetNull, (void *)dst);

			switch(p->present)
			{
				case Iso14827AcceptTypePresent_login:
					if ((err = OID_fromASN(&p->x.login, &src->choice.login)).code) ERR_OUT(&err);
					break;
				case Iso14827AcceptTypePresent_registeredSubscription:
					if (asn_INTEGER2long(&src->choice.registered_subscription, &val) < 0) ERR_OUT(&err);
					else p->x.registeredSubscription = (u32_t)val;
				default:
					break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827AcceptType_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error Iso14827AcceptType_toASN(struct datexAccept_Type *dst, Iso14827AcceptType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827AcceptTypePresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case datexAccept_Type_PR_login:
			if (OBJECT_IDENTIFIER_set_arcs(&dst->choice.login, src->x.login->data, sizeof(src->x.login->data[0]), src->x.login->cnt) < 0) ERR_SET_OUT(&err, EFAULT);
			break;
		case datexAccept_Type_PR_single_subscription:
			break;
		case datexAccept_Type_PR_registered_subscription:
			if (asn_long2INTEGER(&dst->choice.registered_subscription, (long)src->x.registeredSubscription) < 0) ERR_SET_OUT(&err, EFAULT);
			break;
		case datexAccept_Type_PR_publication:
			break;
		case datexAccept_Type_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Accept_fromASN(Iso14827Accept **dst, Accept_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long pktNbr;
		Iso14827Accept *p = NULL;
		if (asn_INTEGER2long(&src->datexAccept_Packet_nbr, &pktNbr) < 0) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Accept_new((u32_t)pktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Accept_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827AcceptType_fromASN(&p->acceptType, &src->datexAccept_Type)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827Accept_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Accept_toASN(Accept_t *dst, Iso14827Accept *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (asn_long2INTEGER(&dst->datexAccept_Packet_nbr, (long)src->pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = Iso14827AcceptType_toASN(&dst->datexAccept_Type, src->acceptType)).code) ERR_OUT(&err);
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Login
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectLogin_fromASN(Iso14827RejectLogin *dst, datexReject_Login_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexReject_Login_cd_other:
				*dst = Iso14827RejectLogin_other;
				break;
			case datexReject_Login_cd_unknownDomainName:
				*dst = Iso14827RejectLogin_unknownDomainName;
				break;
			case datexReject_Login_cd_accessDenied:
				*dst = Iso14827RejectLogin_accessDenied;
				break;
			case datexReject_Login_cd_invalidNamePassword:
				*dst = Iso14827RejectLogin_invalidPassword;
				break;
			case datexReject_Login_cd_timeoutTooSmall:
				*dst = Iso14827RejectLogin_timeoutTooSmall;
				break;
			case datexReject_Login_cd_timeoutTooLarge:
				*dst = Iso14827RejectLogin_timeoutTooLarge;
				break;
			case datexReject_Login_cd_heartbeatTooSmall:
				*dst = Iso14827RejectLogin_heartbeatTooSmall;
				break;
			case datexReject_Login_cd_heartbeatTooLarge:
				*dst = Iso14827RejectLogin_heartbeatTooLarge;
				break;
			case datexReject_Login_cd_sessionExists:
				*dst = Iso14827RejectLogin_sessionExist;
				break;
			case datexReject_Login_cd_maxSessionsReached:
				*dst = Iso14827RejectLogin_maxSessionReached;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
		}
	}

	return err;
}

static Dz1Error Iso14827RejectLogin_toASN(datexReject_Login_cd_e *dst, Iso14827RejectLogin src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RejectLogin_other:
		*dst = datexReject_Login_cd_other;
		break;
	case Iso14827RejectLogin_unknownDomainName:
		*dst = datexReject_Login_cd_unknownDomainName;
		break;
	case Iso14827RejectLogin_accessDenied:
		*dst = datexReject_Login_cd_accessDenied;
		break;
	case Iso14827RejectLogin_invalidPassword:
		*dst = datexReject_Login_cd_invalidNamePassword;
		break;
	case Iso14827RejectLogin_timeoutTooSmall:
		*dst = datexReject_Login_cd_timeoutTooSmall;
		break;
	case Iso14827RejectLogin_timeoutTooLarge:
		*dst = datexReject_Login_cd_timeoutTooLarge;
		break;
	case Iso14827RejectLogin_heartbeatTooSmall:
		*dst = datexReject_Login_cd_heartbeatTooSmall;
		break;
	case Iso14827RejectLogin_heartbeatTooLarge:
		*dst = datexReject_Login_cd_heartbeatTooLarge;
		break;
	case Iso14827RejectLogin_sessionExist:
		*dst = datexReject_Login_cd_sessionExists;
		break;
	case Iso14827RejectLogin_maxSessionReached:
		*dst = datexReject_Login_cd_maxSessionsReached;
		break;
	case Iso14827RejectLogin_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Subscription
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectSubscription_fromASN(Iso14827RejectSubscription *dst, datexReject_Subscription_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexReject_Subscription_cd_other:
				*dst = Iso14827RejectSubscription_other;
				break;
			case datexReject_Subscription_cd_unknownSubscriptionNbr:
				*dst = Iso14827RejectSubscription_unknownSubscriptionNbr;
				break;
			case datexReject_Subscription_cd_invalidTimes:
				*dst = Iso14827RejectSubscription_invalidTimes;
				break;
			case datexReject_Subscription_cd_frequencyTooSmall:
				*dst = Iso14827RejectSubscription_frequencyTooSmall;
				break;
			case datexReject_Subscription_cd_frequencyTooLarge:
				*dst = Iso14827RejectSubscription_frequencyTooLarge;
				break;
			case datexReject_Subscription_cd_invalid_mode:
				*dst = Iso14827RejectSubscription_invalidMode;
				break;
			case datexReject_Subscription_cd_publishFormatNotSupported:
				*dst = Iso14827RejectSubscription_publishFormatNotSupported;
				break;
			case datexReject_Subscription_cd_unknowSubscriptionMsgId:
				*dst = Iso14827RejectSubscription_unknownSubscriptionMsgId;
				break;
			case datexReject_Subscription_cd_invalidSubscriptionMsgId:
				*dst = Iso14827RejectSubscription_invalidSubscriptionMsgId;
				break;
			case datexReject_Subscription_cd_invalidSubscriptionContent:
				*dst = Iso14827RejectSubscription_invalidSubscriptionContent;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectSubscription_toASN(datexReject_Subscription_cd_e *dst, Iso14827RejectSubscription src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RejectSubscription_other:
		*dst = datexReject_Subscription_cd_other;
		break;
	case Iso14827RejectSubscription_unknownSubscriptionNbr:
		*dst = datexReject_Subscription_cd_unknownSubscriptionNbr;
		break;
	case Iso14827RejectSubscription_invalidTimes:
		*dst = datexReject_Subscription_cd_invalidTimes;
		break;
	case Iso14827RejectSubscription_frequencyTooSmall:
		*dst = datexReject_Subscription_cd_frequencyTooSmall;
		break;
	case Iso14827RejectSubscription_frequencyTooLarge:
		*dst = datexReject_Subscription_cd_frequencyTooLarge;
		break;
	case Iso14827RejectSubscription_invalidMode:
		*dst = datexReject_Subscription_cd_invalid_mode;
		break;
	case Iso14827RejectSubscription_publishFormatNotSupported:
		*dst = datexReject_Subscription_cd_publishFormatNotSupported;
		break;
	case Iso14827RejectSubscription_unknownSubscriptionMsgId:
		*dst = datexReject_Subscription_cd_unknowSubscriptionMsgId;
		break;
	case Iso14827RejectSubscription_invalidSubscriptionMsgId:
		*dst = datexReject_Subscription_cd_invalidSubscriptionMsgId;
		break;
	case Iso14827RejectSubscription_invalidSubscriptionContent:
		*dst = datexReject_Subscription_cd_invalidSubscriptionContent;
		break;
	case Iso14827RejectSubscription_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Publication
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectPublication_fromASN(Iso14827RejectPublication *dst, datexReject_Publication_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
			case datexReject_Publication_cd_other:
				*dst = Iso14827RejectPublication_other;
				break;
			case datexReject_Publication_cd_invalidPublishFormat:
				*dst = Iso14827RejectPublication_invalidPublishFormat;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectPublication_toASN(datexReject_Publication_cd_e *dst, Iso14827RejectPublication src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RejectPublication_other:
		*dst = datexReject_Publication_cd_other;
		break;
	case Iso14827RejectPublication_invalidPublishFormat:
		*dst = datexReject_Publication_cd_invalidPublishFormat;
		break;
	case Iso14827RejectPublication_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Publication Data Reason
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectPubDataReason_fromASN(Iso14827RejectPubDataReason *dst, datexReject_PublicationData_cd_e src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case datexReject_PublicationData_cd_other:
			*dst = Iso14827RejectPubDataReason_other;
			break;
		case datexReject_PublicationData_cd_unknownSubscription:
			*dst = Iso14827RejectPubDataReason_unknownSubscription;
			break;
		case datexReject_PublicationData_cd_unknownPublicationNbr:
			*dst = Iso14827RejectPubDataReason_unknownPublicationNbr;
			break;
		case datexReject_PublicationData_cd_unknownPublicationMsgId:
			*dst = Iso14827RejectPubDataReason_unknownPublicationMsgId;
			break;
		case datexReject_PublicationData_cd_invalidPublicationMsgId:
			*dst = Iso14827RejectPubDataReason_invalidPublicationMsgId;
			break;
		case datexReject_PublicationData_cd_invalidPublicationMsgContent:
			*dst = Iso14827RejectPubDataReason_invalidPublicationMsgContent;
			break;
		case datexReject_PublicationData_cd_repeatedPublicationNbr:
			*dst = Iso14827RejectPubDataReason_repeatedPublicationNbr;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectPubDataReason_toASN(datexReject_PublicationData_cd_e *dst, Iso14827RejectPubDataReason src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RejectPubDataReason_other:
		*dst = datexReject_PublicationData_cd_other;
		break;
	case Iso14827RejectPubDataReason_unknownSubscription:
		*dst = datexReject_PublicationData_cd_unknownSubscription;
		break;
	case Iso14827RejectPubDataReason_unknownPublicationNbr:
		*dst = datexReject_PublicationData_cd_unknownPublicationNbr;
		break;
	case Iso14827RejectPubDataReason_unknownPublicationMsgId:
		*dst = datexReject_PublicationData_cd_unknownPublicationMsgId;
		break;
	case Iso14827RejectPubDataReason_invalidPublicationMsgId:
		*dst = datexReject_PublicationData_cd_invalidPublicationMsgId;
		break;
	case Iso14827RejectPubDataReason_invalidPublicationMsgContent:
		*dst = datexReject_PublicationData_cd_invalidPublicationMsgContent;
		break;
	case Iso14827RejectPubDataReason_repeatedPublicationNbr:
		*dst = datexReject_PublicationData_cd_repeatedPublicationNbr;
		break;
	case Iso14827RejectPubDataReason_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Publication Data
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectPubData_fromASN(Iso14827RejectPubData **dst, struct rejectPublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long subSerial, pubSerial;
		Iso14827RejectPubDataReason reason;
		Iso14827RejectPubData *p = NULL;
		if (asn_INTEGER2long(&src->datexReject_SubscriptionSerial_nbr, &subSerial) < 0) ERR_OUT(&err);
		else if (asn_INTEGER2long(&src->datexReject_PublicationSerial_nbr, &pubSerial) < 0) ERR_OUT(&err);
		else if ((err = Iso14827RejectPubDataReason_fromASN(&reason, src->datexReject_PublicationData_cd)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827RejectPubData_new((u32_t)subSerial, (u32_t)pubSerial, reason, &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error Iso14827RejectPubData_toASN(struct rejectPublicationData *dst, Iso14827RejectPubData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (asn_long2INTEGER(&dst->datexReject_SubscriptionSerial_nbr, (long)src->subSerial) < 0) ERR_SET_OUT(&err, EFAULT);
	else if (asn_long2INTEGER(&dst->datexReject_PublicationSerial_nbr, (long)src->pubSerial) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = Iso14827RejectPubDataReason_toASN(&dst->datexReject_PublicationData_cd, src->reason)).code) ERR_OUT(&err);
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectTypePresent_fronASN(Iso14827RejectTypePresent *dst, RejectType_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src)
		{
		case RejectType_PR_datexReject_Login_cd:
			*dst = Iso14827RejectTypePresent_login;
			break;
		case RejectType_PR_datexReject_Subscription_cd:
			*dst = Iso14827RejectTypePresent_subscription;
			break;
		case RejectType_PR_datexReject_Publication_cd:
			*dst = Iso14827RejectTypePresent_publication;
			break;
		case RejectType_PR_rejectPublicationData:
			*dst = Iso14827RejectTypePresent_pubData;
			break;
		case RejectType_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Type
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectType_fromASN(Iso14827RejectType **dst, RejectType_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827RejectType *p = NULL;
		Iso14827RejectTypePresent present;
		if ((err = Iso14827RejectTypePresent_fronASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827RejectType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827RejectType_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827RejectTypePresent_login:
				if ((err = Iso14827RejectLogin_fromASN(&p->x.login, src->choice.datexReject_Login_cd)).code) ERR_OUT(&err);
				break;
			case Iso14827RejectTypePresent_subscription:
				if ((err = Iso14827RejectSubscription_fromASN(&p->x.subscription, src->choice.datexReject_Subscription_cd)).code) ERR_OUT(&err);
				break;
			case Iso14827RejectTypePresent_publication:
				if ((err = Iso14827RejectPublication_fromASN(&p->x.publication, src->choice.datexReject_Publication_cd)).code) ERR_OUT(&err);
				break;
			case Iso14827RejectTypePresent_pubData:
				if ((err = Iso14827RejectPubData_fromASN(&p->x.pubData, &src->choice.rejectPublicationData)).code) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827RejectType_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectType_toASN(RejectType_t *dst, Iso14827RejectType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827RejectTypePresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case RejectType_PR_datexReject_Login_cd:
			if ((err = Iso14827RejectLogin_toASN(&dst->choice.datexReject_Login_cd, src->x.login)).code) ERR_OUT(&err);
			break;
		case RejectType_PR_datexReject_Subscription_cd:
			if ((err = Iso14827RejectSubscription_toASN(&dst->choice.datexReject_Subscription_cd, src->x.subscription)).code) ERR_OUT(&err);
			break;
		case RejectType_PR_datexReject_Publication_cd:
			if ((err = Iso14827RejectPublication_toASN(&dst->choice.datexReject_Publication_cd, src->x.publication)).code) ERR_OUT(&err);
			break;
		case RejectType_PR_rejectPublicationData:
			if ((err = Iso14827RejectPubData_toASN(&dst->choice.rejectPublicationData, src->x.pubData)).code) ERR_OUT(&err);
			break;
		case RejectType_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
			
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Reject_fromASN(Iso14827Reject **dst, Reject_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long pktNbr;
		Iso14827Reject *p = NULL;
		if (asn_INTEGER2long(&src->datexReject_Packet_nbr, &pktNbr) < 0) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Reject_new((u32_t)pktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Reject_delAndSetNull, (void *)dst);
			if ((err = Iso14827RejectType_fromASN(&p->type, &src->datexReject_Type)).code) ERR_OUT(&err);
			else if (src->datexReject_AlternateRequest && (err = Iso14827SubscriptionType_fromASN(&p->altReq, src->datexReject_AlternateRequest)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Reject_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Reject_toASN(Reject_t *dst, Iso14827Reject *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (asn_long2INTEGER(&dst->datexReject_Packet_nbr, (long)src->pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
	else if ((err = Iso14827RejectType_toASN(&dst->datexReject_Type, src->type)).code) ERR_OUT(&err);
	else if (src->altReq && (err = Iso14827SubscriptionType_toASN(&dst->datexReject_AlternateRequest, src->altReq)).code) ERR_OUT(&err);
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// PDUs Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PDUsPresent_fromASN(Iso14827PDUsPresent *dst, PDUs_PR src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch (src)
	{
		case PDUs_PR_datex_Initiate_null:
			*dst = Iso14827PDUsPresent_initiate;
			break;
		case PDUs_PR_login:
			*dst = Iso14827PDUsPresent_login;
			break;
		case PDUs_PR_fred:
			*dst = Iso14827PDUsPresent_fred;
			break;
		case PDUs_PR_terminate:
			*dst = Iso14827PDUsPresent_term;
			break;
		case PDUs_PR_logout:
			*dst = Iso14827PDUsPresent_logout;
			break;
		case PDUs_PR_subscription:
			*dst = Iso14827PDUsPresent_subscription;
			break;
		case PDUs_PR_publication:
			*dst = Iso14827PDUsPresent_publication;
			break;
		case PDUs_PR_transfer_done:
			*dst = Iso14827PDUsPresent_transferDone;
			break;
		case PDUs_PR_accept:
			*dst = Iso14827PDUsPresent_ack;
			break;
		case PDUs_PR_reject:
			*dst = Iso14827PDUsPresent_nak;
			break;
		case PDUs_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}

	return err;
}

static Dz1Error Iso14827PDUsPresent_toASN(PDUs_PR *dst, Iso14827PDUsPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(src)
	{
	case Iso14827PDUsPresent_initiate:
		*dst = PDUs_PR_datex_Initiate_null;
		break;
	case Iso14827PDUsPresent_login:
		*dst = PDUs_PR_login;
		break;
	case Iso14827PDUsPresent_fred:
		*dst = PDUs_PR_fred;
		break;
	case Iso14827PDUsPresent_term:
		*dst = PDUs_PR_terminate;
		break;
	case Iso14827PDUsPresent_logout:
		*dst = PDUs_PR_logout;
		break;
	case Iso14827PDUsPresent_subscription:
		*dst = PDUs_PR_subscription;
		break;
	case Iso14827PDUsPresent_publication:
		*dst = PDUs_PR_publication;
		break;
	case Iso14827PDUsPresent_transferDone:
		*dst = PDUs_PR_transfer_done;
		break;
	case Iso14827PDUsPresent_ack:
		*dst = PDUs_PR_accept;
		break;
	case Iso14827PDUsPresent_nak:
		*dst = PDUs_PR_reject;
		break;
	case Iso14827PDUsPresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// PDUs
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PDUs_fromASN(Iso14827PDUs **dst, PDUs_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827PDUsPresent present;
		Iso14827PDUs *p = NULL;
		if ((err = Iso14827PDUsPresent_fromASN(&present, src->present)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827PDUs_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			long fred;
			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)dst);
			switch(p->present)
			{
				case Iso14827PDUsPresent_initiate:
					if ((err = Iso14827Initiate_fromASN(&p->x.initiate, &src->choice.datex_Initiate_null)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_login:
					if ((err = Iso14827Login_fromASN(&p->x.login, &src->choice.login)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_fred:
					if (asn_INTEGER2long(&src->choice.fred, &fred) < 0) ERR_SET_OUT(&err, EFAULT);
					else { p->x.fred = (u32_t)fred; }
					break;
				case Iso14827PDUsPresent_term:
					if ((err = Iso14827Terminate_fromASN(&p->x.term, src->choice.terminate)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_logout:
					if ((err = Iso14827Logout_fromASN(&p->x.logout, src->choice.logout)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_subscription:
					if ((err = Iso14827Subscription_fromASN(&p->x.subscription, &src->choice.subscription)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_publication:
					if ((err = Iso14827Publication_fromASN(&p->x.publication, &src->choice.publication)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_transferDone:
					if ((err = Iso14827TransferDone_fromASN(&p->x.transferDone, &src->choice.transfer_done)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_ack:
					if ((err = Iso14827Accept_fromASN(&p->x.ack, &src->choice.accept)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_nak:
					if ((err = Iso14827Reject_fromASN(&p->x.nak, &src->choice.reject)).code) ERR_OUT(&err);
					break;
				default:
					break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827PDUs_delAndSetNull, (void *)dst);
		}
	}

	return err;
}

static Dz1Error Iso14827PDUs_toASN(PDUs_t *dst, Iso14827PDUs *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827PDUsPresent_toASN(&dst->present, src->present)).code) ERR_OUT(&err);
	else
	{
		switch(dst->present)
		{
		case PDUs_PR_datex_Initiate_null:
			if ((err = Iso14827Initiate_toASN(&dst->choice.datex_Initiate_null, src->x.initiate)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_login:
			if ((err = Iso14827Login_toASN(&dst->choice.login, src->x.login)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_fred:
			if (asn_long2INTEGER(&dst->choice.fred, (long)src->x.fred) < 0) ERR_SET_OUT(&err, EFAULT);
			break;
		case PDUs_PR_terminate:
			if ((err = Iso14827Terminate_toASN(&dst->choice.terminate, src->x.term)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_logout:
			if ((err = Iso14827Logout_toASN(&dst->choice.logout, src->x.logout)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_subscription:
			if ((err = Iso14827Subscription_toASN(&dst->choice.subscription, src->x.subscription)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_publication:
			if ((err = Iso14827Publication_toASN(&dst->choice.publication, src->x.publication)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_transfer_done:
			if ((err = Iso14827TransferDone_toASN(&dst->choice.transfer_done, src->x.transferDone)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_accept:
			if ((err = Iso14827Accept_toASN(&dst->choice.accept, src->x.ack)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_reject:
			if ((err = Iso14827Reject_toASN(&dst->choice.reject, src->x.nak)).code) ERR_OUT(&err);
			break;
		case PDUs_PR_NOTHING:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// C2C Authenticated Message
///////////////////////////////////////////////////////////////////////////////
Dz1Error Iso14827C2CAuthMsg_fromASN(Iso14827C2CAuthMsg **dst, C2CAuthenticatedMessage_t *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		long pktNbr;
		Iso14827C2CAuthMsg *msg = NULL;
		if (asn_INTEGER2long(&src->datex_DataPacket_number, &pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
		else
		{
			pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)dst);
			
			if ((msg = (*dst) = Iso14827C2CAuthMsg_new(NULL, (u32_t)pktNbr, (s32_t)src->datex_DataPacketPriority_number, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->authInfo = Dz1Asn1OctetStr_new(src->datex_AuthenticationInfo_text.buf, src->datex_AuthenticationInfo_text.size, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Iso14827HdrOpt_fromASN(&msg->hdrOpt, &src->options)).code) ERR_OUT(&err);
			else if ((err = Iso14827PDUs_fromASN(&msg->pdu, &src->pdu)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

Dz1Error Iso14827C2CAuthMsg_toASN(C2CAuthenticatedMessage_t **dst, Iso14827C2CAuthMsg *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (*dst != NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		C2CAuthenticatedMessage_t *p = NULL;
		if ((p = (*dst) = (C2CAuthenticatedMessage_t *)calloc(sizeof(C2CAuthenticatedMessage_t), 1)) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			pthread_cleanup_push(C2CAuthenticatedMessage_delAndSetNull, (void *)dst);
			if ((OCTET_STRING_fromBuf(&p->datex_AuthenticationInfo_text,
				src->authInfo->size ? (char *)src->authInfo->data : "", src->authInfo->size))) ERR_SET_OUT(&err, EFAULT);
			else if (asn_long2INTEGER(&p->datex_DataPacket_number, (long)src->pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
			else if ((err = Iso14827HdrOpt_toASN(&p->options, src->hdrOpt)).code) ERR_OUT(&err);
			else if ((err= Iso14827PDUs_toASN(&p->pdu, src->pdu)).code) ERR_OUT(&err);
			else
			{
				p->datex_DataPacketPriority_number = (long)src->priority;
			}
			pthread_cleanup_pop(err.code); // (C2CAuthenticatedMessage_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

#endif