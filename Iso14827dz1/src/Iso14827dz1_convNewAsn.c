#include <dz1_int.h>
#include <dz1_thread_stdio.h>

#include <Iso14827dz1_assist.h>
#include <ISO14827_2.h>
//#include <ISO14827_1.h>

#include "Iso14827dz1_conv.h"
///////////////////////////////////////////////////////////////////////////////
// End Application Message
///////////////////////////////////////////////////////////////////////////////
static Dz1Error ANY_fromASN(Dz1Asn1Any **dst, OpenType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (( (*dst) = Dz1Asn1Any_new(src->data, src->numocts, &err)) == NULL) ERR_OUT(&err);

 	return err;
}

static Dz1Error Iso14827EndAppMsg_fromASN(Iso14827EndAppMsg **dst, EndApplicationMessage *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827EndAppMsg *p = NULL;
		if ((p = (*dst) = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827EndAppMsg_delAndSetNull, (void *)dst);
			
			if ((p->oid = Dz1Asn1OID_newFromASN(&src->endApplication_Message_id, &err)) == NULL) ERR_OUT(&err);
			else if ((err = ANY_fromASN(&p->data, &src->endApplication_Message_msg)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827EndAppMsg_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error Iso14827EndAppMsg_toASN(EndApplicationMessage **dst, Iso14827EndAppMsg *src, ASN1WorkSpace *ws)
{
	EndApplicationMessage *p = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (EndApplicationMessage *)mpool_malloc(ws->Pmemory, sizeof(EndApplicationMessage))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(EndApplicationMessage));
		if (ASN1_SET_EndApplicationMessage_endApplication_Message_id(ws, p, src->oid->data, src->oid->cnt) < 0) {ERR_OUT(&err);}
		else if (src->data && ASN1_SET_EndApplicationMessage_endApplication_Message_msg(ws, p, src->data->data, src->data->size) < 0) {ERR_OUT(&err);}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// IsoTime Fraction
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TimeFrac_fromASN(Iso14827TimeFrac **dst, IsoTime_time_SecondFractions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TimeFracPresent present;
	s32_t val;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else if (src->M == DEF_IsoTime_time_SecondFractions_deci_seconds)
	{
		present = Iso14827TimeFracPresent_deci;
		val = (s32_t)src->elements.deci_seconds;
	}
	else if (src->M == DEF_IsoTime_time_SecondFractions_centi_seconds)
	{
		present = Iso14827TimeFracPresent_centi;
		val = (s32_t)src->elements.centi_seconds;
	}
	else if (src->M == DEF_IsoTime_time_SecondFractions_milli_seconds)
	{
		present = Iso14827TimeFracPresent_milli;
		val = (s32_t)src->elements.milli_seconds;
	}
	else { ERR_SET_OUT(&err, EINVAL); }
	
	if (err.code == 0 && ((*dst) = Iso14827TimeFrac_new(present, (void *)&val, &err)) == NULL) ERR_OUT(&err);
	
	return err;
}

static Dz1Error Iso14827TimeFrac_toASN(IsoTime_time_SecondFractions *dst, Iso14827TimeFrac *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0,sizeof(IsoTime_time_SecondFractions));
		if (src->present == Iso14827TimeFracPresent_deci)
		{
			if (ASN1_SET_IsoTime_time_SecondFractions_deci_seconds(ws, dst, (INTEGER)src->x.deci) < 0) ERR_SET_OUT(&err, EFAULT);
		}
		else if (src->present == Iso14827TimeFracPresent_centi)
		{
			if (ASN1_SET_IsoTime_time_SecondFractions_centi_seconds(ws, dst, (INTEGER)src->x.centi) < 0) ERR_SET_OUT(&err, EFAULT);
		}
		else if (src->present == Iso14827TimeFracPresent_milli)
		{
			if (ASN1_SET_IsoTime_time_SecondFractions_milli_seconds(ws, dst, (INTEGER)src->x.milli) < 0) ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// IsoTime Zone
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TimeZone_fromASN(Iso14827TimeZone **dst, IsoTime_time_Timezone *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Iso14827TimeZone *p = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else 
	{
		INTEGER H, M;
		if (ASN1_GET_IsoTime_time_Timezone_timezone_Hour_qty(&ws, src, &H) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_GET_IsoTime_time_Timezone_time_Minute_qty(&ws, src, &M) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (((*dst) = Iso14827TimeZone_new((s32_t)H, (s32_t)M, &err)) == NULL) ERR_OUT(&err);
	}
	
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827TimeZone_toASN(IsoTime_time_Timezone *dst, Iso14827TimeZone *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//IsoTime_time_Timezone *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0,sizeof(IsoTime_time_Timezone));
		if ((ASN1_SET_IsoTime_time_Timezone_time_Minute_qty(ws, dst, src->modM)) <0) ERR_OUT(&err);
		else if ((ASN1_SET_IsoTime_time_Timezone_timezone_Hour_qty(ws, dst, src->modH)) <0) ERR_OUT(&err);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// IsoTime
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Time_yearFromASN(u32_t **dst, IsoTime *src, ASN1WorkSpace *ws)
{
	INTEGER val;
	int getStatus;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((getStatus = ASN1_GET_IsoTime_time_Year_qty(ws, src, &val)) == -1) ERR_SET_OUT(&err, EFAULT);
	else if (getStatus == -2) { }
	else if ((*dst = Dz1u32_new((u32_t)val, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error Iso14827Time_monthFromASN(u32_t **dst, IsoTime *src, ASN1WorkSpace *ws)
{
	INTEGER val;
	int getStatus;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if ((getStatus = ASN1_GET_IsoTime_time_Month_qty(ws, src, &val)) == -1) ERR_SET_OUT(&err, EFAULT);
	else if (getStatus == -2) { }
	else if ((*dst = Dz1u32_new((u32_t)val, &err)) == NULL) ERR_OUT(&err);
	
	return err;
}

static Dz1Error Iso14827Time_dayFromASN(u32_t **dst, IsoTime *src, ASN1WorkSpace *ws)
{
	INTEGER val;
	int getStatus;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if ((getStatus = ASN1_GET_IsoTime_time_Day_qty(ws, src, &val)) == -1) ERR_SET_OUT(&err, EFAULT);
	else if (getStatus == -2) { }
	else if ((*dst = Dz1u32_new((u32_t)val, &err)) == NULL) ERR_OUT(&err);
	
	return err;
}


static Dz1Error Iso14827Time_fracFromASN(Iso14827TimeFrac **dst, IsoTime *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime_time_SecondFractions *frac = NULL;
		if ((status = ASN1_GET_IsoTime_time_SecondFractions(ws, src, &frac)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -3) { }
		else if ((err = Iso14827TimeFrac_fromASN(dst, frac)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error Iso14827Time_zoneFromASN(Iso14827TimeZone **dst, IsoTime *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime_time_Timezone *zone = NULL;
		if ((status = ASN1_GET_IsoTime_time_Timezone(ws, src, &zone)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827TimeZone_fromASN(dst, zone)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error Iso14827Time_fromASN(Iso14827Time **dst, IsoTime *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	 
	else
	{
		int status;
		Iso14827Time *p = NULL;
		INTEGER H = 0, M = 0, S = 0;
		if ((status = ASN1_GET_IsoTime_time_Hour_qty(&ws, src, &H)) < 0 && status != -3) ERR_SET_OUT(&err, EFAULT);
		else if ((status = ASN1_GET_IsoTime_time_Minute_qty(&ws, src, &M)) < 0 && status != -3) ERR_SET_OUT(&err, EFAULT);
		else if ((status = ASN1_GET_IsoTime_time_Second_qty(&ws, src, &S)) < 0 && status != -3) ERR_SET_OUT(&err, EFAULT);
		else if ((p = (*dst) = Iso14827Time_new(NULL, NULL, NULL, (s32_t)H, (s32_t)M, (s32_t)S, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Time_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827Time_yearFromASN((u32_t **)&p->year, src, &ws)).code) ERR_OUT(&err);
			else if ((err = Iso14827Time_monthFromASN((u32_t **)&p->month, src, &ws)).code) ERR_OUT(&err);
			else if ((err = Iso14827Time_dayFromASN((u32_t **)&p->day, src, &ws)).code) ERR_OUT(&err);
			else if ((err = Iso14827Time_fracFromASN(&p->frac, src, &ws)).code) ERR_OUT(&err);
			else if ((err = Iso14827Time_zoneFromASN(&p->zone, src, &ws)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Time_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827Time_fracToASN(IsoTime *dst, Iso14827TimeFrac *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!dst) ERR_SET_OUT(&err, EINVAL);
	else if (src == NULL)
	{
		/*
		IsoTime_time_SecondFractions frac;
		memset(&frac, 0, sizeof(IsoTime_time_SecondFractions));
		if (ASN1_SET_IsoTime_time_SecondFractions_centi_seconds(ws, &frac, 0) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_IsoTime_time_SecondFractions(ws, dst, &frac) < 0) ERR_SET_OUT(&err, EFAULT);
		*/
	}
	else
	{
		IsoTime_time_SecondFractions frac;
		if ((err = Iso14827TimeFrac_toASN(&frac, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_IsoTime_time_SecondFractions(ws, dst, &frac) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

static Dz1Error Iso14827Time_zoneToASN(IsoTime *dst, Iso14827TimeZone *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime_time_Timezone zone;
		if ((err = Iso14827TimeZone_toASN(&zone, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_IsoTime_time_Timezone(ws, dst, &zone) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

static Dz1Error Iso14827Time_toASN(IsoTime *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0,sizeof(IsoTime));
		if (src->year && ASN1_SET_IsoTime_time_Year_qty(ws, dst, *src->year) < 0) ERR_OUT(&err);
		else if (src->month && ASN1_SET_IsoTime_time_Month_qty(ws, dst, *src->month) < 0) ERR_OUT(&err);
		else if (src->day && ASN1_SET_IsoTime_time_Day_qty(ws, dst, *src->day) < 0) ERR_OUT(&err);
		else if (src->h != 0 && ASN1_SET_IsoTime_time_Hour_qty(ws, dst, src->h) < 0) ERR_OUT(&err);
		else if (src->m != 0 && ASN1_SET_IsoTime_time_Minute_qty(ws, dst, src->m) < 0) ERR_OUT(&err);
		else if (src->s != 0 && ASN1_SET_IsoTime_time_Second_qty(ws, dst, src->s) < 0) ERR_OUT(&err);
		else if (src->frac && (err = Iso14827Time_fracToASN(dst, src->frac, ws)).code) ERR_OUT(&err);
		else if (src->zone && (err = Iso14827Time_zoneToASN(dst, src->zone, ws)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Header Option Cost
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Cost_fromASN(Iso14827Cost **dst, Cost *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER factor, qty;
		Iso14827Cost *p = NULL;
		
		if (ASN1_GET_Cost_amount_Factor_quantity(&ws, src, &factor) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_GET_Cost_amount_Quantity_quantity(&ws, src, &qty) < 0) ERR_SET_OUT(&err, EFAULT);
		if ((p = (*dst) = Iso14827Cost_new(NULL, (s32_t)factor, (s32_t)qty, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Cost_delAndSetNull, (void *)dst);
			// Verified : Jake Lim			
			if ((p->currency = Dz1Asn1OctetStr_new(src->amount_Currency_code.data, src->amount_Currency_code.numbits, &err)) == NULL) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827Cost_delAndSetNull, (void *)dst);
		}
	}
	
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827Cost_toASN(Cost *dst, Iso14827Cost *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0, sizeof(Cost));
		if (ASN1_SET_Cost_amount_Currency_code(ws, dst, src->currency->data, src->currency->size) <0) {ERR_OUT(&err);}
		else if (ASN1_SET_Cost_amount_Quantity_quantity(ws, dst, (INTEGER)src->factor)  <0) {ERR_OUT(&err);}
		else if (ASN1_SET_Cost_amount_Factor_quantity(ws, dst, (INTEGER)src->qty)  <0) {ERR_OUT(&err);}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Header Option
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827HdrOpt_originFromASN(Dz1Asn1UTF8Str **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_Origin_text(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1UTF8Str_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827HdrOpt_originAddressFromASN(Dz1Asn1OctetStr **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_OriginAddress_location(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1OctetStr_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827HdrOpt_senderFromASN(Dz1Asn1UTF8Str **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_Sender_text(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1UTF8Str_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827HdrOpt_senderAddressFromASN(Dz1Asn1OctetStr **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_SenderAddress_location(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1OctetStr_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827HdrOpt_destFromASN(Dz1Asn1UTF8Str **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_Destination_text(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1UTF8Str_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827HdrOpt_destAddressFromASN(Dz1Asn1OctetStr **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		ASNUINT8 *buf = NULL;
		ASNUINT32 size = 0;
		if ((status = ASN1_GET_HeaderOptions_datex_DestinationAddress_location(&ws, src, &buf, &size)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1Asn1OctetStr_new(buf, size, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827HdrOpt_costFromASN(Iso14827Cost **dst, HeaderOptions *src)
{
	int status;
	Cost *cost = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else if ((status = ASN1_GET_HeaderOptions_datex_Cost(&ws, src, &cost)) == -1) ERR_SET_OUT(&err, EFAULT);
	else if (status == -2) { }
	else if ((err = Iso14827Cost_fromASN(dst, cost)).code) ERR_OUT(&err);

	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827HdrOpt_timeFromASN(Iso14827Time **dst, HeaderOptions *src)
{
	int status;
	IsoTime *_src = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else if ((status = ASN1_GET_HeaderOptions_datex_DataPacket_time(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
	else if (status == -2) { }
	else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827HdrOpt_fromASN(Iso14827HdrOpt **dst, HeaderOptions *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827HdrOpt *p = NULL;
		if ((p = (*dst) = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827HdrOpt_delAndSetNull, (void *)dst);
			// Origin
			if ((err = Iso14827HdrOpt_originFromASN(&p->origin, src)).code) ERR_OUT(&err);
			else if ((err = Iso14827HdrOpt_originAddressFromASN(&p->originAddr, src)).code) ERR_OUT(&err);
			// Sender
			else if ((err = Iso14827HdrOpt_senderFromASN(&p->sender, src)).code) ERR_OUT(&err);
			else if ((err = Iso14827HdrOpt_senderAddressFromASN(&p->senderAddr, src)).code) ERR_OUT(&err);
			// Destination
			else if ((err = Iso14827HdrOpt_destFromASN(&p->dest, src)).code) ERR_OUT(&err);
			else if ((err = Iso14827HdrOpt_destAddressFromASN(&p->destAddr, src)).code) ERR_OUT(&err);
			// Cost
			else if ((err = Iso14827HdrOpt_costFromASN(&p->cost, src)).code) ERR_OUT(&err);
			// PacketTime
			else if ((err = Iso14827HdrOpt_timeFromASN(&p->t, src)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827HdrOpt_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827HdrOpt_costToASN(HeaderOptions *dst, Iso14827Cost *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Cost cost;
		memset(&cost, 0, sizeof(Cost));
		if ((err = Iso14827Cost_toASN(&cost, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_HeaderOptions_datex_Cost(ws, dst, &cost) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

static Dz1Error Iso14827HdrOpt_tToAsn(HeaderOptions *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		memset(&t, 0, sizeof(IsoTime));
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_HeaderOptions_datex_DataPacket_time(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

static Dz1Error Iso14827HdrOpt_toASN(HeaderOptions **dst, Iso14827HdrOpt *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	HeaderOptions *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (HeaderOptions *)mpool_malloc(ws->Pmemory, sizeof(HeaderOptions))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0, sizeof(HeaderOptions));
		if (src->origin && ASN1_SET_HeaderOptions_datex_Origin_text(ws, p, src->origin->data,  src->origin->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->sender && ASN1_SET_HeaderOptions_datex_Sender_text(ws, p, src->sender->data,  src->sender->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->dest && ASN1_SET_HeaderOptions_datex_Destination_text(ws, p, src->dest->data,  src->dest->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->originAddr && ASN1_SET_HeaderOptions_datex_OriginAddress_location(ws, p, src->originAddr->data,  src->originAddr->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->senderAddr && ASN1_SET_HeaderOptions_datex_SenderAddress_location(ws, p, src->senderAddr->data,  src->senderAddr->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->destAddr && ASN1_SET_HeaderOptions_datex_DestinationAddress_location(ws, p, src->destAddr->data,  src->destAddr->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->cost && (err = Iso14827HdrOpt_costToASN(p, src->cost, ws)).code) ERR_OUT(&err);
		else if (src->t && (err = Iso14827HdrOpt_tToAsn(p, src->t, ws)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Initiate : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Initiate_fromASN(Iso14827Initiate **dst, Initiate *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827Initiate *p = NULL;
		if ((p = (*dst) = Iso14827Initiate_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Initiate_delAndSetNull, (void *)dst);
			if ((p->dest = Dz1Asn1UTF8Str_new(src->datex_Destination_txt.asnstring, src->datex_Destination_txt.nchar, &err)) == NULL) ERR_OUT(&err);
			else if ((p->sender = Dz1Asn1UTF8Str_new(src->datex_Sender_txt.asnstring, src->datex_Sender_txt.nchar, &err)) == NULL) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Initiate_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Initiate_toASN(Initiate **dst, Iso14827Initiate *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Initiate *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	 
	else if ((p = (*dst) = (Initiate *)mpool_malloc(ws->Pmemory, sizeof(Initiate))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Initiate));
		if (src->dest && ASN1_SET_Initiate_datex_Destination_txt(ws, p, src->dest->data, src->dest->size)<0) ERR_SET_OUT(&err, EFAULT);
		else if (src->sender &&ASN1_SET_Initiate_datex_Sender_txt(ws, p, src->sender->data, src->sender->size)<0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Login OID List
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827LoginOIDList_fromASN(Dz1OIDList *dst, Login_datexLogin_EncodingRules_id *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	Dz1Asn1OID *oid = NULL;
	OBJECTIDENTIFIER *asnOID = NULL;
	
	ASN1ListNode *node = NULL;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	for (node = src->head->next; err.code == 0 && node; node = node->next)
	{
		asnOID = (OBJECTIDENTIFIER *)node->data;;
		if ((oid = Dz1Asn1OID_newFromASN(asnOID, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Asn1OID_del, (void *)oid);
			
			if ((err = dst->add(dst, oid)).code) ERR_OUT(&err);
			else oid = NULL;
			
			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1Asn1OID_del, (void *)oid);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

typedef struct Iso14827LoginOIDListToASNArg
{
	Login_datexLogin_EncodingRules_id *dst;
	ASN1WorkSpace *ws;
} Iso14827LoginOIDListToASNArg;

static Dz1Error _Iso14827LoginOIDList_toASN(void *ptr, Dz1Asn1OID *oid)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827LoginOIDListToASNArg *arg = (Iso14827LoginOIDListToASNArg *)ptr;
	Login_datexLogin_EncodingRules_id *dst = arg->dst;
	ASN1WorkSpace *ws = arg->ws;
	
	OBJECTIDENTIFIER *asnOID = NULL;

	if ((asnOID = Dz1Asn1OID_toNewASN(oid, ws, &err)) == NULL) ERR_OUT(&err);
	else if (ASN1_Insert_Node(ws, dst, asnOID) < 0) ERR_SET_OUT(&err, EFAULT);
	
	return err;
}

static Dz1Error Iso14827LoginOIDList_toASN(Login_datexLogin_EncodingRules_id *dst, Dz1OIDList *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827LoginOIDListToASNArg arg;
	arg.dst = dst;
	arg.ws = ws;

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASN1_Creat_Init_List(ws, dst);
		if ((err = src->travel(src, _Iso14827LoginOIDList_toASN, (void *)&arg)).code) ERR_OUT(&err);
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Login Initiator
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827LoginInitiator_fromASN(Iso14827LoginInitiator *dst, Login src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src.datexLogin_Initiator_cd)
		{
		case Login_datexLogin_Initiator_cd_serverInitiated:
			*dst = Iso14827LoginInitiator_serverInitiated;
			break;
		case Login_datexLogin_Initiator_cd_clientInitiated:
			*dst = Iso14827LoginInitiator_clientInitiated;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827LoginInitiator_toASN(int *dst, Iso14827LoginInitiator src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827LoginInitiator_serverInitiated:
			*dst = Login_datexLogin_Initiator_cd_serverInitiated;
			break;
		case Iso14827LoginInitiator_clientInitiated:
			*dst = Login_datexLogin_Initiator_cd_clientInitiated;
			break;
		case Iso14827LoginInitiator_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Login : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Login_fromASN(Iso14827Login **dst, Login *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827Login *p;
		Iso14827LoginInitiator initiator;
		if ((err = Iso14827LoginInitiator_fromASN(&initiator, *src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Login_new(NULL, NULL, NULL, NULL, (s32_t)src->datexLogin_HeartbeatDurationMax_qty,
			(s32_t)src->datexLogin_ResponseTimeOut_qty, initiator, (s32_t)src->datexLogin_DatagramSize_qty, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Login_delAndSetNull, (void *)dst);
			if ((p->sender = Dz1Asn1UTF8Str_new(src->datex_Sender_txt.asnstring, src->datex_Sender_txt.nchar, &err)) == NULL) ERR_OUT(&err);
			else if ((p->dest = Dz1Asn1UTF8Str_new(src->datex_Destination_txt.asnstring, src->datex_Destination_txt.nchar	, &err)) == NULL) ERR_OUT(&err);
			else if ((p->user = Dz1Asn1OctetStr_new(src->datexLogin_UserName_txt.data, src->datexLogin_UserName_txt.numbits, &err)) == NULL) ERR_OUT(&err);
			else if ((p->pass = Dz1Asn1OctetStr_new(src->datexLogin_Password_txt.data, src->datexLogin_Password_txt.numbits, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Iso14827LoginOIDList_fromASN(p->encRules, &src->datexLogin_EncodingRules_id)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (Iso14827Login_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827Login_toASN(Login **dst, Iso14827Login *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Login *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	 
	else if ((p = (*dst) = (Login *)mpool_malloc(ws->Pmemory, sizeof(Login))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Login));
		if (src->sender && ASN1_SET_Login_datex_Sender_txt(ws, p, src->sender->data, src->sender->size)<0) ERR_SET_OUT(&err, EFAULT);
		else if (src->dest && ASN1_SET_Login_datex_Destination_txt(ws, p, src->dest->data, src->dest->size)<0) ERR_SET_OUT(&err, EFAULT);
		else if (src->user && ASN1_SET_Login_datexLogin_UserName_txt(ws, p, src->user->data, src->user->size)<0) ERR_SET_OUT(&err, EFAULT);
		else if (src->pass && ASN1_SET_Login_datexLogin_Password_txt(ws, p, src->pass->data, src->pass->size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->encRules && (err = Iso14827LoginOIDList_toASN(&p->datexLogin_EncodingRules_id, src->encRules, ws)).code) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_Login_datexLogin_HeartbeatDurationMax_qty(ws, p, src->hbDur) <0)ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_Login_datexLogin_ResponseTimeOut_qty(ws, p, src->timeout) <0)ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827LoginInitiator_toASN((int *)&p->datexLogin_Initiator_cd, src->initiator, ws)).code)ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_Login_datexLogin_DatagramSize_qty(ws, p, src->datagramSize)<0)ERR_SET_OUT(&err, EFAULT);
	}
		
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Terminate
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Terminate_fromASN(Iso14827Terminate *dst, Terminate src)
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

static Dz1Error Iso14827Terminate_toASN(Terminate *dst, Iso14827Terminate src)
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

///////////////////////////////////////////////////////////////////////////////
// Logout
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Logout_fromASN(Iso14827Logout *dst, Logout src)
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

static Dz1Error Iso14827Logout_toASN(Logout *dst, Iso14827Logout src)
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
// Registered Continuous : Optional Members = StartTime, EndTime
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredContinuous_startFromASN(Iso14827Time **dst, Registered_continuous *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime *_src = NULL;
		if ((status = ASN1_GET_Registered_continuous_datexRegistered_StartTime(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredContinuous_endFromASN(Iso14827Time **dst, Registered_continuous *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime *_src = NULL;
		if ((status = ASN1_GET_Registered_continuous_datexRegistered_EndTime(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredContinuous_fromASN(Iso14827RegisteredContinuous **dst, Registered_continuous *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		INTEGER updateDelay = 0;
		Iso14827RegisteredContinuous *p = NULL;
		//IsoTime *IsoTimer1 = NULL, *IsoTimer2 = NULL;
		if ((status = ASN1_GET_Registered_continuous_datexRegistered_UpdateDelay_qty(&ws, src, &updateDelay)) < 0 && status != -3) {ERR_OUT(&err);}
		else if ((p = (*dst) = Iso14827RegisteredContinuous_new((u32_t)updateDelay, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827RegisteredContinuous_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827RegisteredContinuous_startFromASN(&p->start, src)).code) ERR_OUT(&err);
			else if ((err = Iso14827RegisteredContinuous_endFromASN(&p->end, src)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827RegisteredContinuous_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827RegisteredContinuous_startToASN(Registered_continuous *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_Registered_continuous_datexRegistered_StartTime(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}

	return err;
}

static Dz1Error Iso14827RegisteredContinuous_endToASN(Registered_continuous *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_Registered_continuous_datexRegistered_EndTime(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredContinuous_toASN(Registered_continuous *dst, Iso14827RegisteredContinuous *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Registered_continuous *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0, sizeof(Registered_continuous));
		if ((ASN1_SET_Registered_continuous_datexRegistered_UpdateDelay_qty(ws, dst, src->updateDelay)) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (src->start && (err = Iso14827RegisteredContinuous_startToASN(dst, src->start, ws)).code) ERR_OUT(&err);
		else if (src->end && (err = Iso14827RegisteredContinuous_endToASN(dst, src->end, ws)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Daily : Optional Members = StartDate, EndDate, StartTime, Duration
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredDaily_startDateFromASN(Iso14827Time **dst, Registered_daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime *_src = NULL;

		if ((status = ASN1_GET_Registered_daily_datexRegistered_StartDate(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredDaily_endDateFromASN(Iso14827Time **dst, Registered_daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime *_src = NULL;
		
		if ((status = ASN1_GET_Registered_daily_datexRegistered_EndDate(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredDaily_startTimeFromASN(Iso14827Time **dst, Registered_daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		IsoTime *_src = NULL;
		
		if ((status = ASN1_GET_Registered_daily_datexRegistered_StartTime(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827Time_fromASN(dst, _src)).code) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredDaily_durationFromASN(u16_t **dst, Registered_daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		INTEGER _src;
		if ((status = ASN1_GET_Registered_daily_datexRegistered_Duration_qty(&ws, src, &_src)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if (((*dst) = Dz1u16_new((u16_t)_src, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RegisteredDaily_fromASN(Iso14827RegisteredDaily **dst, Registered_daily *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT8 *v = NULL;
		ASNUINT32L vSize = 0;
		if (ASN1_GET_Registered_daily_datexRegistered_DaysOfWeek_cd(&ws, src, &v, &vSize) < 0) ERR_SET_OUT(&err, EFAULT);
		else
		{
			int status;
			u8_t dow = *v;
			INTEGER updateDelay = 0;
			Iso14827RegisteredDaily *p = NULL;

			if ((status = ASN1_GET_Registered_daily_datexRegistered_UpdateDelay_qty(&ws, src, &updateDelay)) <0 && status != -3)  {ERR_OUT(&err);}
			else if ((p = (*dst) = Iso14827RegisteredDaily_new((u32_t)updateDelay, dow, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Iso14827RegisteredDaily_delAndSetNull, (void *)dst);

				if ((err = Iso14827RegisteredDaily_startDateFromASN(&p->startDate, src)).code) ERR_OUT(&err);
				else if ((err = Iso14827RegisteredDaily_endDateFromASN(&p->endDate, src)).code) ERR_OUT(&err);
				else if ((err = Iso14827RegisteredDaily_startTimeFromASN(&p->startTime, src)).code) ERR_OUT(&err);
				else if ((err = Iso14827RegisteredDaily_durationFromASN(&p->duration, src)).code) ERR_OUT(&err);

				pthread_cleanup_pop(err.code); // (Iso14827RegisteredDaily_delAndSetNull, (void *)dst);
			}
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}

static Dz1Error Iso14827RegisteredDaily_startDateToASN(Registered_daily *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_Registered_daily_datexRegistered_StartDate(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}

	return err;
}

static Dz1Error Iso14827RegisteredDaily_endDateToASN(Registered_daily *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_Registered_daily_datexRegistered_EndDate(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredDaily_startTimeToASN(Registered_daily *dst, Iso14827Time *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		IsoTime t;
		if ((err = Iso14827Time_toASN(&t, src, ws)).code) ERR_OUT(&err);
		else if (ASN1_SET_Registered_daily_datexRegistered_StartTime(ws, dst, &t) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

static Dz1Error Iso14827RegisteredDaily_toASN(Registered_daily *dst, Iso14827RegisteredDaily *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0, sizeof(Registered_daily));
		if (ASN1_SET_Registered_daily_datexRegistered_UpdateDelay_qty(ws, dst, src->updateDelay) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_Registered_daily_datexRegistered_DaysOfWeek_cd(ws, dst, &src->daysOfWeek, 8) < 0)ERR_SET_OUT(&err, EFAULT);
		else if (src->startDate && (err = Iso14827RegisteredDaily_startDateToASN(dst, src->startDate, ws)).code) ERR_OUT(&err);
		else if (src->endDate && (err = Iso14827RegisteredDaily_endDateToASN(dst, src->endDate, ws)).code) ERR_OUT(&err);
		else if (src->startTime && (err = Iso14827RegisteredDaily_startTimeToASN(dst, src->startTime, ws)).code) ERR_OUT(&err);
		else if (src->duration && ASN1_SET_Registered_daily_datexRegistered_Duration_qty(ws, dst, (INTEGER)(*src->duration)) < 0) ERR_SET_OUT(&err, EFAULT);	
	}	
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Registered Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RegisteredPresent_fromASN(Iso14827RegisteredPresent *dst, Registered *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src->M)
	{
	case DEF_Registered_continuous:
		*dst = Iso14827RegisteredPresent_continuous;
		break;
	case DEF_Registered_daily:
		*dst = Iso14827RegisteredPresent_daily;
		break;
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

/*
static Dz1Error Iso14827RegisteredPresent_toASN(Registered *dst, Iso14827RegisteredPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827RegisteredPresent_continuous:
		dst->M = DEF_Registered_continuous;
		break;
	case Iso14827RegisteredPresent_daily:
		dst->M = DEF_Registered_daily;
		break;
	case Iso14827RegisteredPresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}
*/

///////////////////////////////////////////////////////////////////////////////
// Registered
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Registered_fromASN(Iso14827Registered **dst, Registered *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Registered *p = NULL;
		Iso14827RegisteredPresent present;
		
		if ((err = Iso14827RegisteredPresent_fromASN(&present, src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827Registered_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Registered_continuous *c = NULL;
			Registered_daily *d = NULL;
			
			pthread_cleanup_push(Iso14827Registered_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827RegisteredPresent_continuous:
				if (ASN1_GET_Registered_continuous(&ws, src, &c) < 0) ERR_SET_OUT(&err, EFAULT);
				else if ((err = Iso14827RegisteredContinuous_fromASN(&p->x.continuous, c)).code) ERR_OUT(&err);
				break;
			case Iso14827RegisteredPresent_daily:
				if (( ASN1_GET_Registered_daily(&ws, src, &d)) < 0) { p->x.daily = NULL;}
				else if ((err = Iso14827RegisteredDaily_fromASN(&p->x.daily, d)).code) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827Registered_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827Registered_toASN(Registered *dst, Iso14827Registered *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Registered_daily d;
		Registered_continuous c;

		memset(dst, 0, sizeof(Registered));

		switch(src->present)
		{
		case Iso14827RegisteredPresent_continuous:
			if ((err = Iso14827RegisteredContinuous_toASN(&c, src->x.continuous, ws)).code) ERR_OUT(&err);
			else if (ASN1_SET_Registered_continuous(ws, dst, &c) < 0) ERR_SET_OUT(&err, EFAULT);
			break;
		case DEF_Registered_daily:
			if ((err = Iso14827RegisteredDaily_toASN(&d, src->x.daily, ws)).code) ERR_OUT(&err);
			else if (ASN1_SET_Registered_daily(ws, dst, &d) < 0) ERR_SET_OUT(&err, EINVAL);
			break;
		default :
			ERR_OUT(&err);
			break;
		}
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Mode Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataModePresent_fromASN(Iso14827SubscriptionDataModePresent *dst, SubscriptionMode *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src->M)
	{
	case DEF_SubscriptionMode_single:
		*dst = Iso14827SubscriptionDataModePresent_single;
		break;
	case DEF_SubscriptionMode_event_driven:
		*dst = Iso14827SubscriptionDataModePresent_eventDriven;
		break;
	case DEF_SubscriptionMode_periodic:
		*dst = Iso14827SubscriptionDataModePresent_periodic;
		break;
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

static Dz1Error Iso14827SubscriptionDataModePresent_toASN(SubscriptionMode *dst, Iso14827SubscriptionDataModePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataModePresent_single:
		dst->M = DEF_SubscriptionMode_single;
		break;
	case Iso14827SubscriptionDataModePresent_eventDriven:
		dst->M = DEF_SubscriptionMode_event_driven;
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		dst->M = DEF_SubscriptionMode_periodic;
		break;
	case Iso14827SubscriptionDataModePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
		
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Mode
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataMode_fromASN(Iso14827SubscriptionDataMode **dst, SubscriptionMode *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827SubscriptionDataMode *p = NULL;
		Iso14827SubscriptionDataModePresent present;
		Registered *drv = NULL;
		Registered *perio = NULL;
		if ((err = Iso14827SubscriptionDataModePresent_fromASN(&present, src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionDataMode_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		{
			pthread_cleanup_push(Iso14827SubscriptionDataMode_delAndSetNull, (void *)dst);
			
			switch(p->present)
			{
			case Iso14827SubscriptionDataModePresent_single:
				break;
			case Iso14827SubscriptionDataModePresent_eventDriven:
				if (( ASN1_GET_SubscriptionMode_event_driven(&ws, src, &drv)) <0) { p->x.eventDriven = NULL; }
				else if ((err = Iso14827Registered_fromASN(&p->x.eventDriven, src->elements.event_driven)).code) ERR_OUT(&err);
				break;
			case Iso14827SubscriptionDataModePresent_periodic:
				if (( ASN1_GET_SubscriptionMode_periodic(&ws, src, &perio)) <0) { p->x.periodic = NULL; }
				else if ((err = Iso14827Registered_fromASN(&p->x.periodic, src->elements.periodic)).code) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionDataMode_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827SubscriptionDataMode_toASN(SubscriptionMode **dst, Iso14827SubscriptionDataMode *src, ASN1WorkSpace *ws)
{
	SubscriptionMode *p = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (SubscriptionMode *)mpool_malloc(ws->Pmemory, sizeof(SubscriptionMode))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(SubscriptionMode));
		if ((err = Iso14827SubscriptionDataModePresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			Registered event, periodic;
			switch(p->M)
			{
			case DEF_SubscriptionMode_single:
				break;
			case DEF_SubscriptionMode_event_driven:
				if ((err = Iso14827Registered_toASN(&event, src->x.eventDriven, ws)).code) ERR_OUT(&err);
				else if (ASN1_SET_SubscriptionMode_event_driven(ws, p, &event) < 0) ERR_SET_OUT(&err, EFAULT);
				break;
			case DEF_SubscriptionMode_periodic:
				if ((err = Iso14827Registered_toASN(&periodic, src->x.periodic, ws)).code) ERR_OUT(&err);
				else if (ASN1_SET_SubscriptionMode_periodic(ws, p, &periodic) < 0) ERR_SET_OUT(&err, EFAULT);
				break;
			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data Status
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataStatus_fromASN(Iso14827SubscriptionDataStatus *dst, SubscriptionData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->datexSubscribe_Status_cd)
		{
		case SubscriptionData_datexSubscribe_Status_cd_new:
			*dst = Iso14827SubscriptionDataStatus_NEW;
			break;
		case SubscriptionData_datexSubscribe_Status_cd_update:
			*dst = Iso14827SubscriptionDataStatus_UPDATED;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

/*
static Dz1Error Iso14827SubscriptionDataStatus_toASN(SubscriptionData *dst, Iso14827SubscriptionDataStatus src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataStatus_NEW:
		dst->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_new;
		break;
	case Iso14827SubscriptionDataStatus_UPDATED:
		dst->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_update;
		break;
	case Iso14827SubscriptionDataStatus_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}
*/
///////////////////////////////////////////////////////////////////////////////
// Subscription Data Format
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionDataFormat_fromASN(Iso14827SubscriptionDataFormat *dst, SubscriptionData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->datexSubscribe_PublishFormat_cd)
		{
		case SubscriptionData_datexSubscribe_PublishFormat_cd_other:
			*dst = Iso14827SubscriptionDataFormat_other;
			break;
		case SubscriptionData_datexSubscribe_PublishFormat_cd_ftp:
			*dst = Iso14827SubscriptionDataFormat_ftp;
			break;
		case SubscriptionData_datexSubscribe_PublishFormat_cd_tftp:
			*dst = Iso14827SubscriptionDataFormat_tftp;
			break;
		case SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket:
			*dst = Iso14827SubscriptionDataFormat_dataPacket;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionDataFormat_toASN(SubscriptionData *dst, Iso14827SubscriptionDataFormat src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionDataFormat_other:
		dst->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_other;
		break;
	case Iso14827SubscriptionDataFormat_ftp:
		dst->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_ftp;
		break;
	case Iso14827SubscriptionDataFormat_tftp:
		dst->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_tftp;
		break;
	case Iso14827SubscriptionDataFormat_dataPacket:
		dst->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket;
		break;
	case Iso14827SubscriptionDataFormat_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Data : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionData_fromASN(Iso14827SubscriptionData **dst, SubscriptionData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827SubscriptionData *p = NULL;
		Iso14827SubscriptionDataStatus status;
		Iso14827SubscriptionDataFormat fmt;
		if ((err = Iso14827SubscriptionDataStatus_fromASN(&status, src)).code) ERR_OUT(&err);
		else if ((err = Iso14827SubscriptionDataFormat_fromASN(&fmt, src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionData_new(src->datexSubscribe_Guarantee_bool ? TRUE : FALSE,
															status, NULL, fmt, (s32_t)src->datexSubscription_Priority_nbr,
															src->datexSubscribe_Guarantee_bool ? TRUE : FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827SubscriptionData_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827SubscriptionDataMode_fromASN(&p->mode, src->datexSubscribe_Mode)).code) ERR_OUT(&err);
			else if ((err = Iso14827EndAppMsg_fromASN(&p->msg, src->datexSubscribe_Pdu)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionData_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionData_toASN(SubscriptionData **dst, Iso14827SubscriptionData *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SubscriptionData *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else if ((p = (*dst) = (SubscriptionData *)mpool_malloc(ws->Pmemory, sizeof(SubscriptionData))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(SubscriptionData));
		if ( ASN1_SET_SubscriptionData_datexSubscribe_Persistent_bool(ws, p, (BOOLEAN)src->persistent) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ( ASN1_SET_SubscriptionData_datexSubscribe_Status_cd(ws, p, src->status) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827SubscriptionDataMode_toASN(&p->datexSubscribe_Mode, src->mode, ws)).code) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827SubscriptionDataFormat_toASN(p, src->fmt)).code) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_SubscriptionData_datexSubscription_Priority_nbr(ws, p, src->priority) <0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_SubscriptionData_datexSubscribe_Guarantee_bool(ws, p, (BOOLEAN)src->guarantee)< 0) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827EndAppMsg_toASN(&p->datexSubscribe_Pdu, src->msg, ws)).code) ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Cancel
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionCancel_fromASN(Iso14827SubscriptionCancel *dst, SubscriptionType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
		case SubscriptionType_datexSubscribe_CancelReason_cd_other:
			*dst = Iso14827SubscriptionCancel_other;
			break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded:
			*dst = Iso14827SubscriptionCancel_dataNotNeeded;
			break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication:
			*dst = Iso14827SubscriptionCancel_errorsInPublication;
			break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout:
			*dst = Iso14827SubscriptionCancel_pendingLogout;
			break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt:
			*dst = Iso14827SubscriptionCancel_processingMgmt;
			break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt:
			*dst = Iso14827SubscriptionCancel_bandwidthMgmt;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionCancel_toASN(SubscriptionType *dst, Iso14827SubscriptionCancel src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
		
	case Iso14827SubscriptionCancel_other:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_other;
		break;
	case Iso14827SubscriptionCancel_dataNotNeeded:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded;
		break;
	case Iso14827SubscriptionCancel_errorsInPublication:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication;
		break;
	case Iso14827SubscriptionCancel_pendingLogout:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout;
		break;
	case Iso14827SubscriptionCancel_processingMgmt:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt;
		break;
	case Iso14827SubscriptionCancel_bandwidthMgmt:
		dst->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt;
		break;
	case Iso14827SubscriptionCancel_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionTypePresent_fromASN(Iso14827SubscriptionTypePresent *dst, SubscriptionType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
		case DEF_SubscriptionType_subscription:
			*dst = Iso14827SubscriptionTypePresent_data;
			break;
		case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
			*dst = Iso14827SubscriptionTypePresent_reason;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827SubscriptionTypePresent_toASN(SubscriptionType *dst, Iso14827SubscriptionTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827SubscriptionTypePresent_data:
		dst->M = DEF_SubscriptionType_subscription;
		break;
	case Iso14827SubscriptionTypePresent_reason:
		dst->M = DEF_SubscriptionType_datexSubscribe_CancelReason_cd;
		break;
	case Iso14827SubscriptionTypePresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription Type : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827SubscriptionType_fromASN(Iso14827SubscriptionType **dst, SubscriptionType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827SubscriptionType *p = NULL;
		Iso14827SubscriptionTypePresent present;
		if ((err = Iso14827SubscriptionTypePresent_fromASN(&present, src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827SubscriptionType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827SubscriptionType_delAndSetNull, (void *)dst);
			switch(p->present)
			{
			case Iso14827SubscriptionTypePresent_data:
				if ((err = Iso14827SubscriptionData_fromASN(&p->x.data, src->elements.subscription)).code) ERR_OUT(&err);
				break;
			case Iso14827SubscriptionTypePresent_reason:
				if ((err = Iso14827SubscriptionCancel_fromASN(&p->x.reason, src)).code) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827SubscriptionType_delAndSetNull, (void *)dst);
		}
	}
	
	return err;
}

static Dz1Error _Iso14827SubscriptionType_toASN(SubscriptionType *dst, Iso14827SubscriptionType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//SubscriptionType *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		memset(dst, 0,sizeof(SubscriptionType));
		if ((err = Iso14827SubscriptionTypePresent_toASN(dst, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(dst->M)
			{
			case DEF_SubscriptionType_subscription:
				if ((err = Iso14827SubscriptionData_toASN(&dst->elements.subscription, src->x.data, ws)).code) ERR_OUT(&err);
				break;
			case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
				if ((err = Iso14827SubscriptionCancel_toASN(dst, src->x.reason)).code) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
			}
		}
	}
	
	return err;
}

static Dz1Error Iso14827SubscriptionType_toASN(SubscriptionType **dst, Iso14827SubscriptionType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SubscriptionType *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else if ((p = (*dst) = (SubscriptionType *)mpool_malloc(ws->Pmemory, sizeof(SubscriptionType))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(SubscriptionType));
		if ((err = _Iso14827SubscriptionType_toASN(p, src, ws)).code) ERR_OUT(&err);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Subscription_fromASN(Iso14827Subscription **dst, Subscription *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	
	else
	{
		INTEGER serial;
		Iso14827Subscription *p = NULL;
		
		//if (asn_INTEGER2long(&src->datexSubscribe_Serial_nbr, &serial) < 0) ERR_SET_OUT(&err, EFAULT);
		
		if((ASN1_GET_Subscription_datexSubscribe_Serial_nbr(&ws, src, &serial)) < 0) {ERR_OUT(&err);}
		
		else if ((p = (*dst) = Iso14827Subscription_new((u32_t)serial, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Subscription_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827SubscriptionType_fromASN(&p->type, src->datexSubscribe_Type)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827Subscription_delAndSetNull, (void *)dst);
		}
	}
	
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827Subscription_toASN(Subscription **dst, Iso14827Subscription *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Subscription *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (Subscription *)mpool_malloc(ws->Pmemory, sizeof(Subscription))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Subscription));
		if (ASN1_SET_Subscription_datexSubscribe_Serial_nbr(ws, p, src->serial) < 0) ERR_OUT(&err);
		else if ((err = Iso14827SubscriptionType_toASN(&p->datexSubscribe_Type, src->type, ws)).code)ERR_SET_OUT(&err, EFAULT);
	}
	
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Type Management
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationMgmt_fromASN(Iso14827PublicationMgmt *dst, PublicationType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->elements.datexPublication_Management_cd)
		{
		case PublicationType_datexPublication_Management_cd_temporarilySuspended:
			*dst = Iso14827PublicationMgmt_temporarilySuspended;
			break;
		case PublicationType_datexPublication_Management_cd_resume:
			*dst = Iso14827PublicationMgmt_resume;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_other:
			*dst = Iso14827PublicationMgmt_terminateOther;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable:
			*dst = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected:
			*dst = Iso14827PublicationMgmt_terminatePublicationsBeingRejected;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_PendingShutdown:
			*dst = Iso14827PublicationMgmt_terminatePendingShutdown;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_processingMgmt:
			*dst = Iso14827PublicationMgmt_terminateProcessingMgmt;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt:
			*dst = Iso14827PublicationMgmt_terminateBandwidthMgmt;
			break;
		case PublicationType_datexPublication_Management_cd_terminate_accessDenied:
			*dst = Iso14827PublicationMgmt_terminateAccessDenied;
			break;
		case PublicationType_datexPublication_Management_cd_unknownRequest:
			*dst = Iso14827PublicationMgmt_unknownRequest;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublicationMgmt_toASN(PublicationType *dst, Iso14827PublicationMgmt src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublicationMgmt_temporarilySuspended:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_temporarilySuspended;
		break;
	case Iso14827PublicationMgmt_resume:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_resume;
		break;
	case Iso14827PublicationMgmt_terminateOther:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_other;
		break;
	case Iso14827PublicationMgmt_terminateDataNoLongerAvailable:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable;
		break;
	case Iso14827PublicationMgmt_terminatePublicationsBeingRejected:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected;
		break;
	case Iso14827PublicationMgmt_terminatePendingShutdown:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_PendingShutdown;
		break;
	case Iso14827PublicationMgmt_terminateProcessingMgmt:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_processingMgmt;
		break;
	case Iso14827PublicationMgmt_terminateBandwidthMgmt:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt;
		break;
	case Iso14827PublicationMgmt_terminateAccessDenied:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_accessDenied;
		break;
	case Iso14827PublicationMgmt_unknownRequest:
		dst->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_unknownRequest;
		break;
	case Iso14827PublicationMgmt_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationTypePresent_fromASN(Iso14827PublicationTypePresent *dst, PublicationType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
		case DEF_PublicationType_datexPublication_Management_cd:
			*dst = Iso14827PublicationTypePresent_mgmt;
			break;
		case DEF_PublicationType_datexPublish_Data:
			*dst = Iso14827PublicationTypePresent_msg;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublicationTypePresent_toASN(PublicationType *dst, Iso14827PublicationTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublicationTypePresent_mgmt:
		dst->M = DEF_PublicationType_datexPublication_Management_cd;
		break;
	case Iso14827PublicationTypePresent_msg:
		dst->M = DEF_PublicationType_datexPublish_Data;
		break;
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Type : No Optional Members
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationType_fromASN(Iso14827PublicationType **dst, PublicationType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublicationType *p = NULL;
	Iso14827PublicationTypePresent present;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827PublicationTypePresent_fromASN(&present, src)).code) ERR_OUT(&err);
	else if ((p = (*dst) = Iso14827PublicationType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{

		pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)dst);
		switch(p->present)
		{
		case Iso14827PublicationTypePresent_mgmt:
			if ((err = Iso14827PublicationMgmt_fromASN(&p->x.mgmt, src)).code) ERR_OUT(&err);
			break;
		case Iso14827PublicationTypePresent_msg:
			if ((err = Iso14827EndAppMsg_fromASN(&p->x.msg, src->elements.datexPublish_Data)).code) ERR_OUT(&err);
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}

		pthread_cleanup_pop(err.code); // (Iso14827PublicationType_delAndSetNull, (void *)dst);
	}
	
	return err;
}

static Dz1Error Iso14827PublicationType_toASN(PublicationType **dst, Iso14827PublicationType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublicationType *p = NULL;
	
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (dst == NULL || src == NULL)ERR_SET_OUT(&err, EINVAL);
	else if (( p = (* dst) = (PublicationType*)mpool_malloc(ws->Pmemory, sizeof(PublicationType))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0, sizeof(PublicationType));
		if ((err = Iso14827PublicationTypePresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(p->M)
			{
			case DEF_PublicationType_datexPublication_Management_cd:
				if ((err = Iso14827PublicationMgmt_toASN(p, src->x.mgmt)).code) ERR_OUT(&err);
				break;
			case DEF_PublicationType_datexPublish_Data:
				if ((err = Iso14827EndAppMsg_toASN(&p->elements.datexPublish_Data, src->x.msg, ws)).code) ERR_OUT(&err);
				break;
			}
		}
	}
	
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationData_fromASN(Iso14827PublicationData **dst, PublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		INTEGER subSerial, serial;
		Iso14827PublicationData *p = NULL;
		if ((ASN1_GET_PublicationData_datexPublish_SubscribeSerial_nbr(&ws, src, &subSerial)) <0)  {ERR_OUT(&err);}
		else if (( ASN1_GET_PublicationData_datexPublish_Serial_nbr(&ws, src, &serial)) <0)  {ERR_OUT(&err);}
		else if ((p = (*dst) = Iso14827PublicationData_new((u32_t)subSerial, (u32_t)serial,
										src->datexPublish_LatePublicationFlag ? TRUE : FALSE,
													NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)dst);
			
			if ((err = Iso14827PublicationType_fromASN(&p->type, src->datexPublish_Type)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827PublicationData_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827PublicationData_toASN(PublicationData **dst, Iso14827PublicationData *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		PublicationData *p = NULL;
		if ((p = (*dst) = (PublicationData *)mpool_malloc(ws->Pmemory,sizeof(PublicationData))) == NULL) ERR_SET_OUT(&err, EFAULT);
		else
		{
			memset(p, 0,sizeof(PublicationData));
			
			if (( ASN1_SET_PublicationData_datexPublish_SubscribeSerial_nbr(ws, p, src->subscriptionSerial)) < 0) ERR_SET_OUT(&err, EFAULT);
			else if (( ASN1_SET_PublicationData_datexPublish_Serial_nbr(ws, p, src->serial)) < 0) ERR_SET_OUT(&err, EFAULT);
			else if (( ASN1_SET_PublicationData_datexPublish_LatePublicationFlag(ws, p, (BOOLEAN)(src->isLated ? TRUE : FALSE))) < 0) ERR_SET_OUT(&err, EFAULT);
			else if ((err = Iso14827PublicationType_toASN(&p->datexPublish_Type, src->type, ws)).code) ERR_OUT(&err);
		}
	}
	
	
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Publication Data List
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublicationDataList_fromASN(Iso14827PublicationDataList **dst, Publish_Format_datexPublish_Data *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		Iso14827PublicationDataList *p = NULL;
		if ((p = (*dst) = Iso14827PublicationDataList_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			u32_t i;
			ASN1ListNode *node = NULL;
			
			Iso14827PublicationData *e = NULL;
			PublicationData *asnData = NULL;
			
			pthread_cleanup_push(Iso14827PublicationDataList_delAndSetNull, (void *)dst);
			for (i = 0, node = src->head->next; err.code == 0 && i < src->count && node; i++, node = node->next)
			{
				asnData = (PublicationData *)node->data;
//				ASN1_Print_PublicationData(asnData, 0);
				if ((err = Iso14827PublicationData_fromASN(&e, asnData)).code) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&e);
					
					while(p->find(p, e) != NULL) e->serial++;

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

typedef struct Iso14827PublicationDataListToASNArg
{
	Publish_Format_datexPublish_Data *dst;
	ASN1WorkSpace *ws;
} Iso14827PublicationDataListToASNArg;

static Dz1Error _Iso14827PublicationDataList_toASN(void *ptr, Iso14827PublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublicationDataListToASNArg *arg = (Iso14827PublicationDataListToASNArg *)ptr;
	Publish_Format_datexPublish_Data *dst = arg->dst;
	ASN1WorkSpace *ws = arg->ws;
	
	PublicationData *p = NULL;
	
	if ((err = Iso14827PublicationData_toASN(&p, src, ws)).code) ERR_OUT(&err);
	else if (ASN1_Insert_Node(ws, dst, p) < 0) ERR_SET_OUT(&err, EFAULT);
	
	
	return err;
}

static Dz1Error Iso14827PublicationDataList_toASN(Publish_Format_datexPublish_Data *dst, Iso14827PublicationDataList *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublicationDataListToASNArg arg;
	arg.dst = dst;
	arg.ws = ws;
	
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASN1_Creat_Init_List(ws, dst);
		if ((err = src->travel(src, _Iso14827PublicationDataList_toASN, (void *)&arg)).code) ERR_OUT(&err);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publish Format Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublishFormatPresent_fromASN(Iso14827PublishFormatPresent *dst, Publish_Format *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
			case DEF_Publish_Format_datexPublish_Data:
				*dst = Iso14827PublishFormatPresent_dataList;
				break;
			case DEF_Publish_Format_datexPublish_FileName_txt:
				*dst = Iso14827PublishFormatPresent_filename;
				break;
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
		}
	}
	return err;
}

static Dz1Error Iso14827PublishFormatPresent_toASN(Publish_Format *dst, Iso14827PublishFormatPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch(src)
	{
	case Iso14827PublishFormatPresent_dataList:
		dst->M = DEF_Publish_Format_datexPublish_Data;
		break;
	case Iso14827PublishFormatPresent_filename:
		dst->M = DEF_Publish_Format_datexPublish_FileName_txt;
		break;
	case Iso14827PublishFormatPresent_max:
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publish Format
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PublishFormat_fromASN(Iso14827PublishFormat **dst, Publish_Format *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublishFormatPresent present;
	Iso14827PublishFormat *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	if ((err = Iso14827PublishFormatPresent_fromASN(&present, src)).code) ERR_OUT(&err);
	else if ((p = (*dst) = Iso14827PublishFormat_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PublishFormat_delAndSetNull, (void *)dst);
		switch(p->present)
		{
			case Iso14827PublishFormatPresent_dataList:
				if ((err = Iso14827PublicationDataList_fromASN(&p->x.dataList, &src->elements.datexPublish_Data)).code) ERR_OUT(&err);
				break;
			case Iso14827PublishFormatPresent_filename:
				if ((p->x.filename = Dz1Asn1UTF8Str_newFromASN(&src->elements.datexPublish_FileName_txt, &err)) == NULL) ERR_OUT(&err);
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
		}
		pthread_cleanup_pop(err.code); //(Iso14827PublishFormat_delAndSetNull, (void *)dst);
	}

	return err;
}

static Dz1Error Iso14827PublishFormat_toASN(Publish_Format **dst, Iso14827PublishFormat *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Publish_Format *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (Publish_Format *)mpool_malloc(ws->Pmemory, sizeof(Publish_Format))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Publish_Format));
		if ((err = Iso14827PublishFormatPresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(p->M)
			{
			case DEF_Publish_Format_datexPublish_Data:
				if ((err = Iso14827PublicationDataList_toASN(&p->elements.datexPublish_Data, src->x.dataList, ws)).code) ERR_OUT(&err);
				break;
			case DEF_Publish_Format_datexPublish_FileName_txt:
				if (src->x.filename && ASN1_SET_Publish_Format_datexPublish_FileName_txt(ws,
					p,	src->x.filename->data, src->x.filename->size) < 0) ERR_SET_OUT(&err, EFAULT);
				break;
			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Publication_fromASN(Iso14827Publication **dst, Publication *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Iso14827Publication *p = NULL;
		
		if ((p = (*dst) = Iso14827Publication_new(src->datexPublish_Guaranteed_bool ? TRUE : FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Iso14827Publication_delAndSetNull, (void *)dst);

			if ((err = Iso14827PublishFormat_fromASN(&p->fmt, src->datexPublish_Format)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // (Iso14827Publication_delAndSetNull, (void *)dst);
		}
	}
	return err;
}

static Dz1Error Iso14827Publication_toASN(Publication **dst, Iso14827Publication *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Publication *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (Publication *)mpool_malloc(ws->Pmemory, sizeof(Publication))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Publication));

		if (ASN1_SET_Publication_datexPublish_Guaranteed_bool(ws, p, (BOOLEAN)src->guaranteed) < 0)ERR_SET_OUT(&err, ENOMEM);
		else if ((err = Iso14827PublishFormat_toASN(&p->datexPublish_Format, src->fmt, ws)).code) ERR_OUT(&err);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Transfer Done
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827TransferDone_fromASN(Iso14827TransferDone **dst, TransferDone *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TransferDone *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = Iso14827TransferDone_new(NULL, src->datexTransferDone_Success_bool ? TRUE : FALSE, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827TransferDone_delAndSetNull, (void *)dst);

		if ((p->filename = Dz1Asn1UTF8Str_new(src->datexTransferDone_FileName_txt.asnstring, src->datexTransferDone_FileName_txt.nchar, &err)) == NULL) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (Iso14827TransferDone_delAndSetNull, (void *)dst);
	}
	return err;
}

static Dz1Error Iso14827TransferDone_toASN(TransferDone **dst, Iso14827TransferDone *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TransferDone *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (TransferDone *)mpool_malloc(ws->Pmemory, sizeof(TransferDone))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(TransferDone));
		if (ASN1_SET_TransferDone_datexTransferDone_FileName_txt(ws, p, src->filename->data, src->filename->size)< 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_SET_TransferDone_datexTransferDone_Success_bool(ws, p, (BOOLEAN)src->isSuccess) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827AcceptTypePresent_fromASN(Iso14827AcceptTypePresent *dst, Accept_datexAccept_Type *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
		case DEF_Accept_datexAccept_Type_login:
			*dst = Iso14827AcceptTypePresent_login;
			break;
		case DEF_Accept_datexAccept_Type_single_subscription:
			*dst = Iso14827AcceptTypePresent_singleSubscription;
			break;
		case DEF_Accept_datexAccept_Type_registered_subscription:
			*dst = Iso14827AcceptTypePresent_registeredSubscription;
			break;
		case DEF_Accept_datexAccept_Type_publication:
			*dst = Iso14827AcceptTypePresent_publication;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}

static Dz1Error Iso14827AcceptTypePresent_toASN(Accept_datexAccept_Type *dst, Iso14827AcceptTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827AcceptTypePresent_login:
			dst->M = DEF_Accept_datexAccept_Type_login;
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			dst->M = DEF_Accept_datexAccept_Type_single_subscription;
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			dst->M = DEF_Accept_datexAccept_Type_registered_subscription;
			break;
		case Iso14827AcceptTypePresent_publication:
			dst->M = DEF_Accept_datexAccept_Type_publication;
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
static Dz1Error Iso14827AcceptType_fromASN(Iso14827AcceptType **dst, Accept_datexAccept_Type *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827AcceptType *p = NULL;
	Iso14827AcceptTypePresent present;
	ASN1WorkSpace ws;
	
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827AcceptTypePresent_fromASN(&present, src)).code) ERR_OUT(&err);
	else if ((p = (*dst) = Iso14827AcceptType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		INTEGER val = 0;
		pthread_cleanup_push(Iso14827AcceptType_delAndSetNull, (void *)dst);
		
		switch(p->present)
		{
		case Iso14827AcceptTypePresent_login:
			if ((p->x.login = Dz1Asn1OID_newFromASN(&src->elements.login, &err)) == NULL) ERR_OUT(&err);
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			if (( ASN1_GET_Accept_datexAccept_Type_registered_subscription(&ws, src, &val)) <0)  {ERR_OUT(&err);}
			else p->x.registeredSubscription = (u32_t)val;
		default:
			break;
		}
		pthread_cleanup_pop(err.code); // (Iso14827AcceptType_delAndSetNull, (void *)dst);
	}
	
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827AcceptType_toASN(Accept_datexAccept_Type **dst, Iso14827AcceptType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Accept_datexAccept_Type *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (Accept_datexAccept_Type *)mpool_malloc(ws->Pmemory, sizeof(Accept_datexAccept_Type))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Accept_datexAccept_Type));
		if ((err = Iso14827AcceptTypePresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(p->M)
			{
				case DEF_Accept_datexAccept_Type_login:
					if (ASN1_SET_Accept_datexAccept_Type_login(ws, p, src->x.login->data, src->x.login->cnt)< 0) {ERR_OUT(&err);}
					break;
				case DEF_Accept_datexAccept_Type_single_subscription:
					break;
				case DEF_Accept_datexAccept_Type_registered_subscription:
					if (ASN1_SET_Accept_datexAccept_Type_registered_subscription(ws, p, src->x.registeredSubscription) < 0) ERR_SET_OUT(&err, EFAULT);
					break;
				case DEF_Accept_datexAccept_Type_publication:
					break;
				default:
					ERR_SET_OUT(&err, EFAULT);
					break;
			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Accept_fromASN(Iso14827Accept **dst, Accept *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	INTEGER pktNbr=0;
	Iso14827Accept *p = NULL;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (( ASN1_GET_Accept_datexAccept_Packet_nbr(&ws, src, &pktNbr)) <0)  {ERR_OUT(&err);}
	else if ((p = (*dst) = Iso14827Accept_new((u32_t)pktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827Accept_delAndSetNull, (void *)dst);

		if ((err = Iso14827AcceptType_fromASN(&p->acceptType, src->datexAccept_Type)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (Iso14827Accept_delAndSetNull, (void *)dst);
	}

	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827Accept_toASN(Accept **dst, Iso14827Accept *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Accept *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (Accept *)mpool_malloc(ws->Pmemory, sizeof(Accept))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Accept));
		if (ASN1_SET_Accept_datexAccept_Packet_nbr(ws, p, src->pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827AcceptType_toASN(&p->datexAccept_Type, src->acceptType, ws)).code) ERR_OUT(&err);	
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Login
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectLogin_fromASN(Iso14827RejectLogin *dst, RejectType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->elements.datexReject_Login_cd)
		{
		case RejectType_datexReject_Login_cd_other:
			*dst = Iso14827RejectLogin_other;
			break;
		case RejectType_datexReject_Login_cd_unknownDomainName:
			*dst = Iso14827RejectLogin_unknownDomainName;
			break;
		case RejectType_datexReject_Login_cd_accessDenied:
			*dst = Iso14827RejectLogin_accessDenied;
			break;
		case RejectType_datexReject_Login_cd_invalidNamePassword:
			*dst = Iso14827RejectLogin_invalidPassword;
			break;
		case RejectType_datexReject_Login_cd_timeoutTooSmall:
			*dst = Iso14827RejectLogin_timeoutTooSmall;
			break;
		case RejectType_datexReject_Login_cd_timeoutTooLarge:
			*dst = Iso14827RejectLogin_timeoutTooLarge;
			break;
		case RejectType_datexReject_Login_cd_heartbeatTooSmall:
			*dst = Iso14827RejectLogin_heartbeatTooSmall;
			break;
		case RejectType_datexReject_Login_cd_heartbeatTooLarge:
			*dst = Iso14827RejectLogin_heartbeatTooLarge;
			break;
		case RejectType_datexReject_Login_cd_sessionExists:
			*dst = Iso14827RejectLogin_sessionExist;
			break;
		case RejectType_datexReject_Login_cd_maxSessionsReached:
			*dst = Iso14827RejectLogin_maxSessionReached;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectLogin_toASN(RejectType *dst, Iso14827RejectLogin src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectLogin_other:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_other;
			break;
		case Iso14827RejectLogin_unknownDomainName:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_unknownDomainName;
			break;
		case Iso14827RejectLogin_accessDenied:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_accessDenied;
			break;
		case Iso14827RejectLogin_invalidPassword:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_invalidNamePassword;
			break;
		case Iso14827RejectLogin_timeoutTooSmall:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooSmall;
			break;
		case Iso14827RejectLogin_timeoutTooLarge:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooLarge;
			break;
		case Iso14827RejectLogin_heartbeatTooSmall:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooSmall;
			break;
		case Iso14827RejectLogin_heartbeatTooLarge:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooLarge;
			break;
		case Iso14827RejectLogin_sessionExist:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_sessionExists;
			break;
		case Iso14827RejectLogin_maxSessionReached:
			dst->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_maxSessionsReached;
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
static Dz1Error Iso14827RejectSubscription_fromASN(Iso14827RejectSubscription *dst, RejectType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->elements.datexReject_Subscription_cd)
		{
		case RejectType_datexReject_Subscription_cd_other:
			*dst = Iso14827RejectSubscription_other;
			break;
		case RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr:
			*dst = Iso14827RejectSubscription_unknownSubscriptionNbr;
			break;
		case RejectType_datexReject_Subscription_cd_invalidTimes:
			*dst = Iso14827RejectSubscription_invalidTimes;
			break;
		case RejectType_datexReject_Subscription_cd_frequencyTooSmall:
			*dst = Iso14827RejectSubscription_frequencyTooSmall;
			break;
		case RejectType_datexReject_Subscription_cd_frequencyTooLarge:
			*dst = Iso14827RejectSubscription_frequencyTooLarge;
			break;
		case RejectType_datexReject_Subscription_cd_invalid_mode:
			*dst = Iso14827RejectSubscription_invalidMode;
			break;
		case RejectType_datexReject_Subscription_cd_publishFormatNotSupported:
			*dst = Iso14827RejectSubscription_publishFormatNotSupported;
			break;
		case RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId:
			*dst = Iso14827RejectSubscription_unknownSubscriptionMsgId;
			break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId:
			*dst = Iso14827RejectSubscription_invalidSubscriptionMsgId;
			break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionContent:
			*dst = Iso14827RejectSubscription_invalidSubscriptionContent;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectSubscription_toASN(RejectType *dst, Iso14827RejectSubscription src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectSubscription_other:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_other;
			break;
		case Iso14827RejectSubscription_unknownSubscriptionNbr:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr;
			break;
		case Iso14827RejectSubscription_invalidTimes:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidTimes;
			break;
		case Iso14827RejectSubscription_frequencyTooSmall:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooSmall;
			break;
		case Iso14827RejectSubscription_frequencyTooLarge:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooLarge;
			break;
		case Iso14827RejectSubscription_invalidMode:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalid_mode;
			break;
		case Iso14827RejectSubscription_publishFormatNotSupported:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_publishFormatNotSupported;
			break;
		case Iso14827RejectSubscription_unknownSubscriptionMsgId:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId;
			break;
		case Iso14827RejectSubscription_invalidSubscriptionMsgId:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId;
			break;
		case Iso14827RejectSubscription_invalidSubscriptionContent:
			dst->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionContent;
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
static Dz1Error Iso14827RejectPublication_fromASN(Iso14827RejectPublication *dst, RejectType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->elements.datexReject_Publication_cd)
		{
		case RejectType_datexReject_Publication_cd_other:
			*dst = Iso14827RejectPublication_other;
			break;
		case RejectType_datexReject_Publication_cd_invalidPublishFormat:
			*dst = Iso14827RejectPublication_invalidPublishFormat;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectPublication_toASN(RejectType *dst, Iso14827RejectPublication src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectPublication_other:
			dst->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_other;
			break;
		case Iso14827RejectPublication_invalidPublishFormat:
			dst->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_invalidPublishFormat;
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
static Dz1Error Iso14827RejectPubDataReason_fromASN(Iso14827RejectPubDataReason *dst, RejectType_rejectPublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->datexReject_PublicationData_cd)
		{
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_other:
			*dst = Iso14827RejectPubDataReason_other;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription:
			*dst = Iso14827RejectPubDataReason_unknownSubscription;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr:
			*dst = Iso14827RejectPubDataReason_unknownPublicationNbr;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId:
			*dst = Iso14827RejectPubDataReason_unknownPublicationMsgId;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId:
			*dst = Iso14827RejectPubDataReason_invalidPublicationMsgId;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent:
			*dst = Iso14827RejectPubDataReason_invalidPublicationMsgContent;
			break;
		case RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr:
			*dst = Iso14827RejectPubDataReason_repeatedPublicationNbr;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	
	return err;
}

static Dz1Error Iso14827RejectPubDataReason_toASN(RejectType_rejectPublicationData *dst, Iso14827RejectPubDataReason src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectPubDataReason_other:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_other;
			break;
		case Iso14827RejectPubDataReason_unknownSubscription:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription;
			break;
		case Iso14827RejectPubDataReason_unknownPublicationNbr:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr;
			break;
		case Iso14827RejectPubDataReason_unknownPublicationMsgId:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId;
			break;
		case Iso14827RejectPubDataReason_invalidPublicationMsgId:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId;
			break;
		case Iso14827RejectPubDataReason_invalidPublicationMsgContent:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent;
			break;
		case Iso14827RejectPubDataReason_repeatedPublicationNbr:
			dst->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr;
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
static Dz1Error Iso14827RejectPubData_fromASN(Iso14827RejectPubData **dst, RejectType_rejectPublicationData *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER subSerial, pubSerial;
		Iso14827RejectPubDataReason reason;
		//Iso14827RejectPubData *p = NULL;
		
		if (ASN1_GET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(&ws, src, &subSerial) <0)  {ERR_OUT(&err);}
		else if (( ASN1_GET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(&ws, src, &pubSerial)) <0)  {ERR_OUT(&err);}
		else if ((err = Iso14827RejectPubDataReason_fromASN(&reason, src)).code) ERR_OUT(&err);
		else if (( (*dst) = Iso14827RejectPubData_new((u32_t)subSerial, (u32_t)pubSerial, reason, &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827RejectPubData_toASN(RejectType_rejectPublicationData **dst, Iso14827RejectPubData *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	RejectType_rejectPublicationData *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (RejectType_rejectPublicationData *)mpool_malloc(ws->Pmemory, sizeof(RejectType_rejectPublicationData))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(RejectType_rejectPublicationData));
		if ((ASN1_SET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(ws, p, src->subSerial)) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((ASN1_SET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(ws, p, src->pubSerial)) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827RejectPubDataReason_toASN(p, src->reason)).code) ERR_OUT(&err);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Type Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectTypePresent_fronASN(Iso14827RejectTypePresent *dst, RejectType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		switch(src->M)
		{
		case DEF_RejectType_datexReject_Login_cd:
			*dst = Iso14827RejectTypePresent_login;
			break;
		case DEF_RejectType_datexReject_Subscription_cd:
			*dst = Iso14827RejectTypePresent_subscription;
			break;
		case DEF_RejectType_datexReject_Publication_cd:
			*dst = Iso14827RejectTypePresent_publication;
			break;
		case DEF_RejectType_rejectPublicationData:
			*dst = Iso14827RejectTypePresent_pubData;
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
	}
	return err;
}

static Dz1Error Iso14827RejectTypePresent_toASN(RejectType *dst, Iso14827RejectTypePresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(src)
	{
		case Iso14827RejectTypePresent_login:
			dst->M = DEF_RejectType_datexReject_Login_cd;
			break;
		case Iso14827RejectTypePresent_subscription:
			dst->M = DEF_RejectType_datexReject_Subscription_cd;
			break;
		case Iso14827RejectTypePresent_publication:
			dst->M = DEF_RejectType_datexReject_Publication_cd;
			break;
		case Iso14827RejectTypePresent_pubData:
			dst->M = DEF_RejectType_rejectPublicationData;
			break;
		case Iso14827RejectTypePresent_max:
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject Type
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827RejectType_fromASN(Iso14827RejectType **dst, RejectType *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	Iso14827RejectType *p = NULL;
	Iso14827RejectTypePresent present;

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827RejectTypePresent_fronASN(&present, src)).code) ERR_OUT(&err);
	else if ((p = (*dst) = Iso14827RejectType_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827RejectType_delAndSetNull, (void *)dst);
		switch(p->present)
		{
		case Iso14827RejectTypePresent_login:
			if ((err = Iso14827RejectLogin_fromASN(&p->x.login, src)).code) ERR_OUT(&err);
			break;
		case Iso14827RejectTypePresent_subscription:
			if ((err = Iso14827RejectSubscription_fromASN(&p->x.subscription, src)).code) ERR_OUT(&err);
			break;
		case Iso14827RejectTypePresent_publication:
			if ((err = Iso14827RejectPublication_fromASN(&p->x.publication, src)).code) ERR_OUT(&err);
			break;
		case Iso14827RejectTypePresent_pubData:
			if ((err = Iso14827RejectPubData_fromASN(&p->x.pubData, src->elements.rejectPublicationData)).code) ERR_OUT(&err);
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
		}
		pthread_cleanup_pop(err.code); // (Iso14827RejectType_delAndSetNull, (void *)dst);
	}
	return err;
}

static Dz1Error Iso14827RejectType_toASN(RejectType **dst, Iso14827RejectType *src, ASN1WorkSpace *ws)
{
	RejectType *p = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((p = (*dst) = (RejectType *)mpool_malloc(ws->Pmemory, sizeof(RejectType))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(RejectType));
		if ((err = Iso14827RejectTypePresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(p->M)
			{
				case DEF_RejectType_datexReject_Login_cd:
					if ((err = Iso14827RejectLogin_toASN(p, src->x.login)).code) ERR_OUT(&err);
					break;
				case DEF_RejectType_datexReject_Subscription_cd:
					if ((err = Iso14827RejectSubscription_toASN(p, src->x.subscription)).code) ERR_OUT(&err);
					break;
				case DEF_RejectType_datexReject_Publication_cd:
					if ((err = Iso14827RejectPublication_toASN(p, src->x.publication)).code) ERR_OUT(&err);
					break;
				case DEF_RejectType_rejectPublicationData:
					if ((err = Iso14827RejectPubData_toASN(&p->elements.rejectPublicationData, src->x.pubData, ws)).code) ERR_OUT(&err);
					break;
				default:
					ERR_SET_OUT(&err, EFAULT);
					break;

			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827Reject_altReqFromASN(Iso14827SubscriptionType **dst, Reject *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		int status;
		AlternateRequest *altReq = NULL;
		if ((status = ASN1_GET_Reject_datexReject_AlternateRequest(ws, src, &altReq)) == -1) ERR_SET_OUT(&err, EFAULT);
		else if (status == -2) { }
		else if ((err = Iso14827SubscriptionType_fromASN(dst, altReq)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error Iso14827Reject_fromASN(Iso14827Reject **dst, Reject *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	INTEGER pktNbr;
	Iso14827Reject *p = NULL;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (( ASN1_GET_Reject_datexReject_Packet_nbr(&ws, src, &pktNbr)) <0)  {ERR_OUT(&err);}
	else if ((p = (*dst) = Iso14827Reject_new((u32_t)pktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827Reject_delAndSetNull, (void *)dst);

		if ((err = Iso14827RejectType_fromASN(&p->type, src->datexReject_Type)).code) ERR_OUT(&err);
		else if ((err = Iso14827Reject_altReqFromASN(&p->altReq, src, &ws)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (Iso14827Reject_delAndSetNull, (void *)dst);
	}
	pthread_cleanup_pop(1); //((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	return err;
}

static Dz1Error Iso14827Reject_altReqToASN(Reject *dst, Iso14827SubscriptionType *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	AlternateRequest altReq;
	
	if ((err = _Iso14827SubscriptionType_toASN(&altReq, src, ws)).code) ERR_OUT(&err);
	else if (ASN1_SET_Reject_datexReject_AlternateRequest(ws, dst, &altReq) < 0) ERR_SET_OUT(&err, EFAULT);
	
	return err;
}

static Dz1Error Iso14827Reject_toASN(Reject **dst, Iso14827Reject *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Reject *p = NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else if ((p = (*dst) = (Reject *)mpool_malloc(ws->Pmemory, sizeof(Reject))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(Reject));
		if (ASN1_SET_Reject_datexReject_Packet_nbr(ws, p, src->pktNbr) <0) ERR_SET_OUT(&err, EFAULT);
		else if ((err = Iso14827RejectType_toASN(&p->datexReject_Type, src->type, ws)).code) ERR_SET_OUT(&err, EFAULT);
		else if (src->altReq && (err = Iso14827Reject_altReqToASN(p, src->altReq, ws)).code)ERR_SET_OUT(&err, EFAULT);
	}
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// PDUs Present
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Iso14827PDUsPresent_fromASN(Iso14827PDUsPresent *dst, PDUs src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	switch (src.M)
	{
	case DEF_PDUs_datex_Initiate_null:
		*dst = Iso14827PDUsPresent_initiate;
		break;
	case DEF_PDUs_login:
		*dst = Iso14827PDUsPresent_login;
		break;
	case DEF_PDUs_fred:
		*dst = Iso14827PDUsPresent_fred;
		break;
	case DEF_PDUs_terminate:
		*dst = Iso14827PDUsPresent_term;
		break;
	case DEF_PDUs_logout:
		*dst = Iso14827PDUsPresent_logout;
		break;
	case DEF_PDUs_subscription:
		*dst = Iso14827PDUsPresent_subscription;
		break;
	case DEF_PDUs_publication:
		*dst = Iso14827PDUsPresent_publication;
		break;
	case DEF_PDUs_transfer_done:
		*dst = Iso14827PDUsPresent_transferDone;
		break;
	case DEF_PDUs_accept:
		*dst = Iso14827PDUsPresent_ack;
		break;
	case DEF_PDUs_reject:
		*dst = Iso14827PDUsPresent_nak;
		break;
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	
	return err;
}

static Dz1Error Iso14827PDUsPresent_toASN(PDUs *dst, Iso14827PDUsPresent src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(src)
	{
	case Iso14827PDUsPresent_initiate:
		dst->M = DEF_PDUs_datex_Initiate_null;
		break;
	case Iso14827PDUsPresent_login:
		dst->M = DEF_PDUs_login;
		break;
	case Iso14827PDUsPresent_fred:
		dst->M = DEF_PDUs_fred;
		break;
	case Iso14827PDUsPresent_term:
		dst->M = DEF_PDUs_terminate;
		break;
	case Iso14827PDUsPresent_logout:
		dst->M = DEF_PDUs_logout;
		break;
	case Iso14827PDUsPresent_subscription:
		dst->M = DEF_PDUs_subscription;
		break;
	case Iso14827PDUsPresent_publication:
		dst->M = DEF_PDUs_publication;
		break;
	case Iso14827PDUsPresent_transferDone:
		dst->M = DEF_PDUs_transfer_done;
		break;
	case Iso14827PDUsPresent_ack:
		dst->M = DEF_PDUs_accept;
		break;
	case Iso14827PDUsPresent_nak:
		dst->M = DEF_PDUs_reject;
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
static Dz1Error Iso14827PDUs_fromASN(Iso14827PDUs **dst, PDUs *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER val;
		Iso14827PDUsPresent present;
		Iso14827PDUs *p = NULL;
		if ((err = Iso14827PDUsPresent_fromASN(&present, *src)).code) ERR_OUT(&err);
		else if ((p = (*dst) = Iso14827PDUs_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{

			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)dst);
			switch(p->present)
			{
				case Iso14827PDUsPresent_initiate:
					if ((err = Iso14827Initiate_fromASN(&p->x.initiate, src->elements.datex_Initiate_null)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_login:
					if ((err = Iso14827Login_fromASN(&p->x.login, src->elements.login)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_fred:
					if (ASN1_GET_PDUs_fred(&ws, src, &val) < 0) ERR_SET_OUT(&err, EFAULT);
					else p->x.fred = (u32_t)val;
					//if (asn_INTEGER2long(&src->choice.fred, &fred) < 0) ERR_SET_OUT(&err, EFAULT);
					//else { p->x.fred = (u32_t)fred; }
					break;
				case Iso14827PDUsPresent_term:
					if ((err = Iso14827Terminate_fromASN(&p->x.term, src->elements.terminate)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_logout:
					if ((err = Iso14827Logout_fromASN(&p->x.logout, src->elements.logout)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_subscription:
					if ((err = Iso14827Subscription_fromASN(&p->x.subscription, src->elements.subscription)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_publication:
					if ((err = Iso14827Publication_fromASN(&p->x.publication, src->elements.publication)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_transferDone:
					if ((err = Iso14827TransferDone_fromASN(&p->x.transferDone, src->elements.transfer_done)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_ack:
					if ((err = Iso14827Accept_fromASN(&p->x.ack, src->elements.accept)).code) ERR_OUT(&err);
					break;
				case Iso14827PDUsPresent_nak:
					if ((err = Iso14827Reject_fromASN(&p->x.nak, src->elements.reject)).code) ERR_OUT(&err);
					break;
				default:
					ERR_SET_OUT(&err, EINVAL);
					break;
			}
			pthread_cleanup_pop(err.code); // (Iso14827PDUs_delAndSetNull, (void *)dst);
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

static Dz1Error Iso14827PDUs_toASN(PDUs **dst, Iso14827PDUs *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PDUs *p =NULL;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	// 
	else if ((p = (*dst) = (PDUs *)mpool_malloc(ws->Pmemory, sizeof(PDUs))) == NULL) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		memset(p, 0,sizeof(PDUs));
		if ((err = Iso14827PDUsPresent_toASN(p, src->present)).code) ERR_OUT(&err);
		else
		{
			switch(p->M)
			{
			case DEF_PDUs_datex_Initiate_null:
				if ((err = Iso14827Initiate_toASN(&p->elements.datex_Initiate_null, src->x.initiate, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_login:
				if ((err = Iso14827Login_toASN(&p->elements.login, src->x.login, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_fred:
				if ((ASN1_SET_PDUs_fred(ws, p, src->x.fred)) < 0) ERR_SET_OUT(&err, EFAULT);
				break;
			case DEF_PDUs_terminate:
				if ((err = Iso14827Terminate_toASN(&p->elements.terminate, src->x.term)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_logout:
				if ((err = Iso14827Logout_toASN(&p->elements.logout, src->x.logout)).code) ERR_OUT(&err);
				break;	
			case DEF_PDUs_subscription:
				if ((err = Iso14827Subscription_toASN(&p->elements.subscription, src->x.subscription, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_publication:
				if ((err = Iso14827Publication_toASN(&p->elements.publication, src->x.publication, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_transfer_done:
				if ((err = Iso14827TransferDone_toASN(&p->elements.transfer_done, src->x.transferDone, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_accept:
				if ((err = Iso14827Accept_toASN(&p->elements.accept, src->x.ack, ws)).code) ERR_OUT(&err);
				break;
			case DEF_PDUs_reject:
				if ((err = Iso14827Reject_toASN(&p->elements.reject, src->x.nak, ws)).code) ERR_OUT(&err);
				break;
				
			default:
				ERR_SET_OUT(&err, EFAULT);
				break;
			}
		}
	}
	
	
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// C2C Authenticated Message : No Optional Members
///////////////////////////////////////////////////////////////////////////////
Dz1Error Iso14827C2CAuthMsg_fromASN(Iso14827C2CAuthMsg **dst, C2CAuthenticatedMessage *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		INTEGER pktNbr, priority;
		Iso14827C2CAuthMsg *msg = NULL;
		
		if (ASN1_GET_C2CAuthenticatedMessage_datex_DataPacket_number(&ws, src, &pktNbr) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_GET_C2CAuthenticatedMessage_datex_DataPacketPriority_number(&ws, src, &priority) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((msg = (*dst) = Iso14827C2CAuthMsg_new(NULL, (u32_t)pktNbr, (s32_t)priority, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		{
			pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)dst);
			
			if ((msg->authInfo = Dz1Asn1OctetStr_new(src->datex_AuthenticationInfo_text.data, src->datex_AuthenticationInfo_text.numbits, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Iso14827HdrOpt_fromASN(&msg->hdrOpt, src->options)).code) ERR_OUT(&err);
			else if ((err = Iso14827PDUs_fromASN(&msg->pdu, src->pdu)).code) ERR_OUT(&err);
			
			pthread_cleanup_pop(err.code); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)dst);
		}
	}
	
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

Dz1Error Iso14827C2CAuthMsg_toASN(C2CAuthenticatedMessage **dst, Iso14827C2CAuthMsg *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	
	else
	{
		C2CAuthenticatedMessage *p = NULL;
		if ((p = (*dst) = (C2CAuthenticatedMessage *)mpool_malloc(ws->Pmemory, sizeof(C2CAuthenticatedMessage))) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			memset(p, 0,sizeof(C2CAuthenticatedMessage));
			if ((ASN1_SET_C2CAuthenticatedMessage_datex_AuthenticationInfo_text(ws, p, src->authInfo->data, src->authInfo->size)) < 0) ERR_SET_OUT(&err, EFAULT);
			else if ((ASN1_SET_C2CAuthenticatedMessage_datex_DataPacket_number(ws, p, (INTEGER)src->pktNbr)) < 0) ERR_SET_OUT(&err, EFAULT);
			else if ((err = Iso14827HdrOpt_toASN(&p->options, src->hdrOpt, ws)).code) ERR_OUT(&err);
			else if ((err= Iso14827PDUs_toASN(&p->pdu, src->pdu, ws)).code) ERR_OUT(&err);
			else 
			{
				p->datex_DataPacketPriority_number = (long)src->priority;
			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// DatexDataPacket
///////////////////////////////////////////////////////////////////////////////
Dz1Error Iso14827DatexDataPacket_fromASN(Iso14827DatexDataPacket **dst, DatexDataPacket *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);

	else
	{
		Iso14827DatexDataPacket *msg = NULL;

		ENUMERATED v;
		ASNUINT8 *buf = NULL, *crcBuf = NULL;
		ASNUINT32 size = 0, crcSize = 0;
		if (ASN1_GET_DatexDataPacket_datex_Version_number(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_GET_DatexDataPacket_datex_Data(&ws, src, &buf, &size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if (ASN1_GET_DatexDataPacket_datex_Crc_nbr(&ws, src, &crcBuf, &crcSize) < 0) ERR_SET_OUT(&err, EFAULT);
		else
		{
			u16_t crc = (((u16_t)crcBuf[0] & 0xFF) << 8) | ((u16_t)crcBuf[1] & 0xFF);
			if ((msg = (*dst) = Iso14827DatexDataPacket_new((Iso14827DatexVersionNumber)v, NULL, crc, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Iso14827DatexDataPacket_delAndSetNull, (void *)dst);
				if ((msg->data = Dz1Asn1OctetStr_new(buf, size, &err)) == NULL) ERR_OUT(&err);
				pthread_cleanup_pop(err.code); // (Iso14827DatexDataPacket_delAndSetNull, (void *)dst);
			}
		}
	}

	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

Dz1Error Iso14827DatexDataPacket_toASN(DatexDataPacket **dst, Iso14827DatexDataPacket *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);

	else
	{
		DatexDataPacket *p = NULL;
		if ((p = (*dst) = (DatexDataPacket *)mpool_malloc(ws->Pmemory, sizeof(DatexDataPacket))) == NULL) ERR_SET_OUT(&err, ENOMEM);
		else
		{
			u8_t crcBuf[2];
			crcBuf[0] = (u8_t)((src->crc16 & 0xFF) >> 8);
			crcBuf[1] = (u8_t)(src->crc16 & 0xFF);
			memset(p, 0,sizeof(DatexDataPacket));
			if (ASN1_SET_DatexDataPacket_datex_Version_number(ws, p, (ENUMERATED)src->version ) < 0) ERR_SET_OUT(&err, EFAULT);
			else if (ASN1_SET_DatexDataPacket_datex_Data(ws, p, src->data->data, src->data->size) < 0) ERR_SET_OUT(&err, EFAULT);
			else if (ASN1_SET_DatexDataPacket_datex_Crc_nbr(ws, p, crcBuf, 2) < 0) ERR_SET_OUT(&err, EFAULT);
		}
	}
	return err;
}

