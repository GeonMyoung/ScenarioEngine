#include <dz1_int.h>
#include <dz1_thread_stdio.h>

#include "Iso3309CRC.h"

#include "Iso14827dz1_codec.h"
#include "Iso14827dz1_conv.h"

#include <Iso14827dz1_assist.h>

u8_t Iso14827dz1_getSupportedCodec(void)
{
	u32_t implement = DZ1_ASN1_CODEC_BIT_BER | DZ1_ASN1_CODEC_BIT_APER | DZ1_ASN1_CODEC_BIT_UPER;
	return Dz1GASN_getSupportedCodec() & implement;
}

u8_t Iso14827dz1_codec2Bit(Dz1Asn1Codec codec) { return Dz1GASN_codec2Bit(codec); }

Dz1Asn1Codec Iso14827LoginCodecOID2Codec(Dz1Asn1OID *oid) { return Dz1GASN_oid2Codec(oid); }

///////////////////////////////////////////////////////////////////////////////
// Iso14827Time API
///////////////////////////////////////////////////////////////////////////////
Dz1Error Iso14827Time2Time(time_t *dst, Iso14827Time *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else
	{
		struct tm *tm_p, tm;

		*dst = time(NULL);
		tm_p = localtime(dst);
		tm = *tm_p;

		if (src->year != NULL) tm.tm_year = *src->year - 1900;
		if (src->month != NULL) tm.tm_mon = *src->month - 1;
		if (src->day != NULL) tm.tm_mday = *src->day;
		tm.tm_hour = src->h;
		tm.tm_min = src->m;
		tm.tm_sec = src->s;

		*dst = mktime(&tm);

		if (src->zone)
		{
			Iso14827TimeZone *zone = src->zone;
			int modS = zone->modH * 60 * 60;
			if (zone->modH < 0 ) modS -= (zone->modM * 60);
			else modS += (zone->modM * 60);
			*dst += modS;
		}
	}
	return err;
}

Dz1Error Iso14827Time2Timeval(struct timeval *dst, Iso14827Time *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	time_t temp = 0;
	if (!dst || !src) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Iso14827Time2Time(&temp, src)).code) ERR_OUT(&err);
	else
	{
		dst->tv_sec = (long)temp;
		if (src->frac)
		{
			Iso14827TimeFrac *frac = src->frac;
			switch(frac->present)
			{
				case Iso14827TimeFracPresent_deci: // 1/10    1ds = 0.1 00000
					dst->tv_usec = frac->x.deci * 100000;
					break;
				case Iso14827TimeFracPresent_centi: // 1/100  1cs = 0.01 0000
					dst->tv_usec = frac->x.centi * 10000;
					break;
				case Iso14827TimeFracPresent_milli: // 1/1000	1ms = 0.001 000
					dst->tv_usec = frac->x.milli * 1000;
					break;
				default:
					dst->tv_usec = 0;
					break;
			}
		}
		else dst->tv_usec = 0;
	}
	return err;
}

#define SAFE_DECLARE_PTR(new_name, arg_name) Dz1Error _##arg_name = DZ1_ERROR_INITIALIZER, *##new_name = arg_name == NULL ? &_##arg_name : arg_name
Iso14827Time *Iso14827TimeFromTime(Iso14827Time *dst, time_t tNow, u8_t flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Iso14827Time *t = dst ? dst : NULL;

	if (t == NULL && (t = Iso14827Time_new(NULL, NULL, NULL, 0, 0, 0, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827Time_delAndSetNull, (void *)&t);
		if (flag == ISO14827TIME_FLAG_GMT)
		{
			struct tm *gmt_p = gmtime(&tNow); struct tm gmt = *gmt_p;
			time_t _gmt = mktime(&gmt);

			int diff = (int)(tNow - _gmt);
			int S = diff < 0 ? -diff : diff;
			int H = S / 3600, M;

			s32_t year = gmt.tm_year + 1900;
			s32_t mon = gmt.tm_mon + 1;
			s32_t day = gmt.tm_mday;

			S %= 3600;
			M = S / 60;

			Iso14827TimeZone_delAndSetNull(&t->zone);

			if ((t->year = Dz1s32_clone(&year, errp)) == NULL) ERR_OUT(errp);
			else if ((t->month = Dz1s32_clone(&mon, errp)) == NULL) ERR_OUT(errp);
			else if ((t->day = Dz1s32_clone(&day, errp)) == NULL) ERR_OUT(errp);
			else if ((t->zone = Iso14827TimeZone_new(H, M, errp)) == NULL) ERR_OUT(errp);
			else
			{
				t->h = gmt.tm_hour;
				t->m = gmt.tm_min;
				t->s = gmt.tm_sec;

				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			struct tm *utc_p = localtime(&tNow); struct tm utc = *utc_p;

			s32_t _year = utc.tm_year + 1900, *year = (flag & ISO14827TIME_FLAG_YEAR) ? &_year : NULL;
			s32_t _mon = utc.tm_mon + 1, *mon = (flag & ISO14827TIME_FLAG_MONTH) ? &_mon : NULL;
			s32_t _day = utc.tm_mday, *day = (flag & ISO14827TIME_FLAG_DAY) ? &_day : NULL;

			Dz1s32_delAndSetNull(&t->year);
			Dz1s32_delAndSetNull(&t->month);
			Dz1s32_delAndSetNull(&t->day);
			Iso14827TimeZone_delAndSetNull(&t->zone);

			if (year && (t->year = Dz1s32_clone(year, errp)) == NULL) ERR_OUT(errp);
			else if (mon && (t->month = Dz1s32_clone(mon, errp)) == NULL) ERR_OUT(errp);
			else if (day && (t->day = Dz1s32_clone(day, errp)) == NULL) ERR_OUT(errp);
			else
			{
				t->h = utc.tm_hour;
				t->m = utc.tm_min;
				t->s = utc.tm_sec;

				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Iso14827Time_delAndSetNull, (void *)&t);
	}
	return t;
}

// tvNow를 IsoTime으로 변환하여 리턴, dst가 NULL이면 생성해서 돌려줌
static Iso14827Time *Iso14827TimeFromTimeval(Iso14827Time *dst, struct timeval tvNow, u8_t flag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Iso14827Time *ret = NULL;
	if ((ret = Iso14827TimeFromTime(dst, (time_t)tvNow.tv_sec, flag, errp)) == NULL) ERR_OUT(errp);
	else
	{
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Time Zone is Fixed to KOREA
///////////////////////////////////////////////////////////////////////////////
Iso14827Time *Iso14827Time_get(Iso14827Time *dst, u8_t flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct timeval tvNow = Dz1GetTimeval();
	Iso14827Time *t = Iso14827TimeFromTimeval(dst, tvNow, flag, errp);
	if (t == NULL) ERR_OUT(errp);
	return t;
}

void Iso14827Time_dump(Iso14827Time *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		char temp[32] = { 0, }, *cp = temp;
		if (p->year)
		{
			sprintf(cp, "%04d", (*p->year) % 10000);
			cp += 4;
		}
		if (p->month)
		{
			if (cp != temp) *cp++ = '-';
			sprintf(cp, "%02d", (*p->month) % 100);
			cp += 2;
		}
		if (p->day)
		{
			if (cp != temp) *cp++ = '-';
			sprintf(cp, "%02d", (*p->day) % 100);
			cp += 2;
		}

		if (cp != temp) *cp++ = ' ';

		sprintf(cp, "%02u:%02u:%02u", p->h, p->m, p->s);
		cp += 8;

		if (p->frac)
		{
			Iso14827TimeFrac *frac = p->frac;
			switch(frac->present)
			{
			case Iso14827TimeFracPresent_deci:
				sprintf(cp, ".%1u", frac->x.deci % 10);
				cp += 2;
				break;
			case Iso14827TimeFracPresent_centi:
				sprintf(cp, ".%02u", frac->x.centi % 100);
				cp += 3;
				break;
			case Iso14827TimeFracPresent_milli:
				sprintf(cp, ".%03u", frac->x.milli % 1000);
				cp += 4;
				break;
			default:
				break;
			}
		}
		if (p->zone)
		{
			Iso14827TimeZone *zone = p->zone;
			sprintf(cp, "+%02d:%02d", zone->modH % 100, zone->modM % 100);
			cp += 6;
		}
		*cp++ = '\0';
		Dz1Thread_printf("%s\n", temp);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Currency Code is Fixed to KOREAN
///////////////////////////////////////////////////////////////////////////////
static Iso14827Cost *Iso14827Cost_get(Iso14827HdrForm *form, s32_t cost, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Iso14827Cost *ret = Iso14827Cost_new(NULL, 0, cost, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		//u8_t buf[3] = { 'K', 'R', 'W' };
		pthread_cleanup_push(Iso14827Cost_delAndSetNull, (void *)&ret);

		if ((ret->currency = Dz1Asn1OctetStr_new((u8_t *)form->currency, 3, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Iso14827Cost_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827HdrOpt API
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Dz1Asn1OctetStr_setIpAddr(Dz1Asn1OctetStr **dst, Dz1SockAddr *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t buf[18], *cp = buf;
	size_t sz = 16;
	if ((err = Dz1SockAddr_getAddr(src, cp, &sz)).code) ERR_OUT(&err);
	else
	{
		if (sz == 4)
		{
			u32_t temp = htonl(*(u32_t *)buf);
			memcpy(buf, &temp, 4);
		}
		cp += sz;
		if ((err = Dz1SockAddr_getPort(src, (u16_t *)cp)).code) ERR_OUT(&err);
		else
		{
			u16_t temp = htons(*(u16_t *)cp);
			memcpy(cp, &temp, 2);
		}
		cp += 2;

		if ((*dst = Dz1Asn1OctetStr_new(buf, (u32_t)(cp - buf), &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

Iso14827HdrOpt *Iso14827HdrOpt_get(Iso14827HdrForm *form,
								   Dz1Asn1UTF8Str *destDomain, Dz1SockAddr *destAddr,
								   Dz1Asn1UTF8Str *originDomain, Dz1SockAddr *originAddr,
								   Dz1Asn1UTF8Str *senderDomain, Dz1SockAddr *senderAddr,
								   s32_t *cost, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Iso14827HdrOpt *hdrOpt = NULL;
	//Iso14827Time *t = NULL;
	if ((hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827HdrOpt_delAndSetNull, (void *)&hdrOpt);

		if      (form->destDomainPresent && (hdrOpt->dest = Dz1Asn1UTF8Str_clone(destDomain, errp)) == NULL) ERR_OUT(errp);
		else if (form->destAddrPresent && (*errp = Dz1Asn1OctetStr_setIpAddr(&hdrOpt->destAddr, destAddr)).code) ERR_OUT(errp);
		else if (form->originDomainPresent && (hdrOpt->origin = Dz1Asn1UTF8Str_clone(originDomain, errp)) == NULL) ERR_OUT(errp);
		else if (form->originAddrPresent && (*errp = Dz1Asn1OctetStr_setIpAddr(&hdrOpt->originAddr, originAddr)).code) ERR_OUT(errp);
		else if (form->senderDomainPresent && (hdrOpt->sender = Dz1Asn1UTF8Str_clone(senderDomain, errp)) == NULL) ERR_OUT(errp);
		else if (form->senderAddrPresent && (*errp = Dz1Asn1OctetStr_setIpAddr(&hdrOpt->senderAddr, senderAddr)).code) ERR_OUT(errp);
		else if (cost && (hdrOpt->cost = Iso14827Cost_get(form, *cost, errp)) == NULL) ERR_OUT(errp);
		else if (form->timeFlag && (hdrOpt->t = Iso14827Time_get(NULL, form->timeFlag, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Iso14827HdrOpt_delAndSetNull, (VOID *)&hdrOpt);
	}
	return hdrOpt;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827Login API
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _Iso14827Login_codec(Dz1OIDList *list, Dz1Asn1Codec codec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1OID *oid = NULL;
	if ((oid = Dz1Asn1Codec2OID(codec, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Asn1OID_del, (void *)oid);
		
		if ((err = list->add(list, oid)).code) ERR_OUT(&err);
		
		pthread_cleanup_pop(err.code); // (Dz1Asn1OID_delAndSetNull, (void *)&oid);
	}
	return err;
}

Dz1Error Iso14827Login_codec(Iso14827Login *p, u8_t supportedCodec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (supportedCodec & DZ1_ASN1_CODEC_BIT_BER && (err = _Iso14827Login_codec(p->encRules, Dz1Asn1Codec_ber)).code) ERR_OUT(&err);
	else if (supportedCodec & DZ1_ASN1_CODEC_BIT_APER && (err = _Iso14827Login_codec(p->encRules, Dz1Asn1Codec_aper)).code) ERR_OUT(&err);
	else if (supportedCodec & DZ1_ASN1_CODEC_BIT_UPER && (err = _Iso14827Login_codec(p->encRules, Dz1Asn1Codec_uper)).code) ERR_OUT(&err);
	else if (supportedCodec & DZ1_ASN1_CODEC_BIT_XER && (err = _Iso14827Login_codec(p->encRules, Dz1Asn1Codec_xer)).code) ERR_OUT(&err);
	else if (supportedCodec & DZ1_ASN1_CODEC_BIT_CXER && (err = _Iso14827Login_codec(p->encRules, Dz1Asn1Codec_cxer)).code) ERR_OUT(&err);

	return err;
}

Dz1Error Iso14827ConvTest(Iso14827C2CAuthMsg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CAuthenticatedMessage *dst;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	Dz1Thread_printf("\nSource ----------------------------\n");
	Iso14827C2CAuthMsg_dump(p, 1);

	if ((err = Iso14827C2CAuthMsg_toASN(&dst, p, &ws)).code) ERR_OUT(&err);
	else
	{
		Iso14827C2CAuthMsg *tmp = NULL;

		Dz1Thread_printf("\nConverted ----------------------------\n");
		ASN1_Print_C2CAuthenticatedMessage(dst, 0);

		if ((err = Iso14827C2CAuthMsg_fromASN(&tmp, dst)).code) ERR_OUT(&err);
		else
		{
			Dz1Thread_printf("\nRecovered ----------------------------\n");
			Iso14827C2CAuthMsg_dump(tmp, 1);
			Iso14827C2CAuthMsg_del(tmp);
		}
	}

	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	return err;
}
