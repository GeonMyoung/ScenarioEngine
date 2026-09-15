#ifndef ISO14827DZ1_ASSIST_H
#define ISO14827DZ1_ASSIST_H

#include <dz1_error.h>
#include <dz1_gasn_support.h>
//#include <dz1_socket.h>
#include <Iso14827dz1.h>
#include <Iso14827dz1_hdrForm.h>

#define ISO14827LIMITS_HEARTBIT_MIN			1
#define ISO14827LIMITS_HEARTBIT_MAX			300
#define ISO14827LIMITS_TIMEOUT_MAX			600

DZ1_CPPLINK u8_t Iso14827dz1_getSupportedCodec(void);
DZ1_CPPLINK u8_t Iso14827dz1_codec2Bit(Dz1Asn1Codec codec);

static __inline__ bool_t Iso14827dz1_isUsableCodec(Dz1Asn1Codec codec)
{
	u8_t bit = Iso14827dz1_codec2Bit(codec);
	u8_t support = Iso14827dz1_getSupportedCodec();
	return (support & bit) ? TRUE : FALSE;
}

static __inline__ bool_t Iso14827dz1_isUsableCodecs(u8_t codecs)
{
	u8_t support = Iso14827dz1_getSupportedCodec();
	if ((support & codecs) == codecs) return TRUE; else return FALSE;
}

// Internal check Version & CRC for ISO14827 
DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decodeDatex(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encodeDatex(Iso14827C2CAuthMsg *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err);

DZ1_CPPLINK ssize_t Iso14827DatexDataPacket_decode(Iso14827DatexDataPacket **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
DZ1_CPPLINK ssize_t Iso14827DatexDataPacket_encode(Iso14827DatexDataPacket *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err);
DZ1_CPPLINK u16_t Iso3309Crc(u8_t *data, size_t size);

DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decode(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encode(Iso14827C2CAuthMsg *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err);

// User Message CODEC API for Subscription & Publication


#define ISO14827TIME_FLAG_YEAR			0x80
#define ISO14827TIME_FLAG_MONTH			0x40
#define ISO14827TIME_FLAG_DAY			0x20
#define Iso14827TIME_FLAG_TIME			0x10
#define ISO14827TIME_FLAG_NONE			0x00
#define ISO14827TIME_FLAG_ALL			(ISO14827TIME_FLAG_YEAR | ISO14827TIME_FLAG_MONTH | ISO14827TIME_FLAG_DAY | Iso14827TIME_FLAG_TIME)
#define ISO14827TIME_FLAG_UTC			ISO14827TIME_FLAG_ALL
#define ISO14827TIME_FLAG_GMT			0xFF

// 현재 시간을 IsoTime으로 변환해서 가져옴. dst가 NULL이면 할당 하여 만들어옴
DZ1_CPPLINK Iso14827Time	*Iso14827Time_get(Iso14827Time *dst, u8_t flag, Dz1Error *err);

DZ1_CPPLINK Dz1Error		 Iso14827Time2Time(time_t *dst, Iso14827Time *src);

// Iso14827TimeFromTime dst가 NULL 이면 만들어서 tNow를 IsoTime으로 변환 하여 리턴
DZ1_CPPLINK Iso14827Time	*Iso14827TimeFromTime(Iso14827Time *dst, time_t tNow, u8_t flag, Dz1Error *err);

DZ1_CPPLINK Dz1Error		 Iso14827Time2Timeval(struct timeval *dst, Iso14827Time *src);

// All Domain Names are cloned
// if cost is NULL then Cost is omitted
DZ1_CPPLINK Iso14827HdrOpt *Iso14827HdrOpt_get(Iso14827HdrForm *form,
											   Dz1Asn1UTF8Str *destDomain, Dz1SockAddr *destAddr,
											   Dz1Asn1UTF8Str *originDomain, Dz1SockAddr *originAddr,
											   Dz1Asn1UTF8Str *senderDomain, Dz1SockAddr *senderAddr,
											   s32_t *cost, Dz1Error *err);

#define ISO14827DAILY_OTHER			0x80
#define ISO14827DAILY_SUN			0x40
#define ISO14827DAILY_MON			0x20
#define ISO14827DAILY_TUE			0x10
#define ISO14827DAILY_WED			0x08
#define ISO14827DAILY_THU			0x04
#define ISO14827DAILY_FRI			0x02
#define ISO14827DAILY_SAT			0x01
#define ISO14827DAILY_FULLWEEK		(ISO14827DAILY_SUN |\
									 ISO14827DAILY_MON |\
									 ISO14827DAILY_TUE |\
									 ISO14827DAILY_WED |\
									 ISO14827DAILY_THU |\
									 ISO14827DAILY_FRI |\
									 ISO14827DAILY_SAT)

//DZ1_CPPLINK Iso14827Registered *Iso14827Registered_clone(Iso14827Registered *src, Dz1Error *err);

DZ1_CPPLINK Dz1Error Iso14827Login_codec(Iso14827Login *p, u8_t supportedCodec);
DZ1_CPPLINK Dz1Asn1Codec Iso14827LoginCodecOID2Codec(Dz1Asn1OID *oid);

DZ1_CPPLINK Dz1Error Iso14827ConvTest(Iso14827C2CAuthMsg *p);

//DZ1_CPPLINK Dz1Error frameTest(void);

#endif