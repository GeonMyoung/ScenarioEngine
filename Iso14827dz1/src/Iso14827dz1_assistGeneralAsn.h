#ifndef ISO14827ASN_ASSIST_H_LOCAL
#define ISO14827ASN_ASSIST_H_LOCAL

// 범용 툴 전용
#if defined(GITSN_GENERAL_ASN_TOOL)

#include <dz1_error.h>
#include <dz1_thread_stdio.h>

#include <dz1_socket.h>

#include <libasn1_assist.h>
#include <DatexDataPacket.h>
#include <C2CAuthenticatedMessage.h>


///////////////////////////////////////////////////////////////////////////////
// DatexDataPacket
///////////////////////////////////////////////////////////////////////////////
static __inline__ void DatexDataPacket_del(DatexDataPacket_t *p) { if (p) ASN1MSG_del(DatexDataPacket, p); }
static __inline__ void DatexDataPacket_dump(DatexDataPacket_t *p, int tab) { if (p) ASN1MSG_dump(DatexDataPacket, p, tab); }
static __inline__ void DatexDataPacket_delAndSetNull(void *ptr)
{
	DatexDataPacket_t **p = (DatexDataPacket_t **)ptr;
	DatexDataPacket_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// C2CAuthenticatedMessage
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK C2CAuthenticatedMessage_t *C2CAuthenticatedMessage_new(OCTET_STRING_t *authInfo, long packetNbr, long periority,
																	UTF8String_t *dstDomain, UTF8String_t *srcDomain, Dz1Error *err);
static __inline__ void C2CAuthenticatedMessage_del(C2CAuthenticatedMessage_t *p) { if (p) ASN1MSG_del(C2CAuthenticatedMessage, p); }
static __inline__ void C2CAuthenticatedMessage_dump(C2CAuthenticatedMessage_t *p, int tab) { if (p) ASN1MSG_dump(C2CAuthenticatedMessage, p, tab); }
static __inline__ void C2CAuthenticatedMessage_delAndSetNull(void *ptr)
{
	C2CAuthenticatedMessage_t **p = (C2CAuthenticatedMessage_t **)ptr;
	C2CAuthenticatedMessage_del(*p); *p = NULL;
}
DZ1_CPPLINK int C2CAuthenticatedMessage_cmp(C2CAuthenticatedMessage_t *a, C2CAuthenticatedMessage_t *b);

DZ1_CPPLINK Dz1Error C2CAuthenticatedMessage_sendBER(Dz1TcpClientSocket *s, C2CAuthenticatedMessage_t *msg);

///////////////////////////////////////////////////////////////////////////////
// Subscription
///////////////////////////////////////////////////////////////////////////////
// Create Subscription for Cancel previous registered Subscription
DZ1_CPPLINK Subscription_t *Subscription_cancelNew(long serial, datexSubscribe_CancelReason_cd_e reason, Dz1Error *err);

// Create Subscription for single Subscription
DZ1_CPPLINK Subscription_t *Subscription_new(long serial, BOOLEAN_t persistent, datexSubscribe_Status_cd_e status,
											 datexSubscribe_PublishFormat_cd_e format, long priority, BOOLEAN_t guarantee,
											 str_t oid, struct asn_TYPE_descriptor_s *endAppMsgType, void *endAppMsg, Dz1Error *err);

static __inline__ void Subscription_del(Subscription_t *p) { if (p) ASN1MSG_del(Subscription, p); }
static __inline__ void Subscription_dump(Subscription_t *p, int tab) { if (p) ASN1MSG_dump(Subscription, p, tab); }
DZ1_CPPLINK Subscription_t *Subscription_copy(Subscription_t **dst, Subscription_t *src, Dz1Error *err);
static __inline__ void Subscription_delAndSetNull(void *ptr)
{
	Subscription_t **p = (Subscription_t **)ptr;
	Subscription_del(*p); *p = NULL;
}

// Subscription mode change APIs : Event-Driven
DZ1_CPPLINK Dz1Error Subscription_setModeEventContinuous(Subscription_t *p, long *updateDelaySec, time_t *startTime, time_t *endTime);
DZ1_CPPLINK Dz1Error Subscription_setModeEventDaily(Subscription_t *p, long *updateDelaySec, u8_t dailyBit,
													time_t *startDate, time_t *endDate, time_t *startTime, long *durationSec);

// Subscription mode change APIs : Periodic
DZ1_CPPLINK Dz1Error Subscription_setModePeriodicContinuous(Subscription_t *p, long periodSec, time_t *startTime, time_t *endTime);
DZ1_CPPLINK Dz1Error Subscription_setModePeriodicDaily(Subscription_t *p, long periodSec, u8_t dailyBit,
													time_t *startDate, time_t *endDate, time_t *startTime, long *durationSec);

///////////////////////////////////////////////////////////////////////////////
// SubscriptionType
///////////////////////////////////////////////////////////////////////////////
static __inline__ void SubscriptionType_del(SubscriptionType_t *p) { if (p) ASN1MSG_del(SubscriptionType, p); }
static __inline__ void SubscriptionType_delAndSetNull(void *ptr)
{
	SubscriptionType_t **p = (SubscriptionType_t **)ptr;
	SubscriptionType_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Accept
///////////////////////////////////////////////////////////////////////////////
static __inline__ void Accept_del(Accept_t *p) { if (p) ASN1MSG_del(Accept, p); }
static __inline__ void Accept_dump(Accept_t *p, int tab) { if (p) { ASN1MSG_dump(Accept, p, tab); Dz1Thread_printf("\n"); } }
DZ1_CPPLINK Accept_t *Accept_copy(Accept_t **dst, Accept_t *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Reject
///////////////////////////////////////////////////////////////////////////////
static __inline__ void Reject_del(Reject_t *p) { if (p) ASN1MSG_del(Reject, p); }
static __inline__ void Reject_dump(Reject_t *p, int tab) { if (p) { ASN1MSG_dump(Reject, p, tab);  Dz1Thread_printf("\n"); }}
DZ1_CPPLINK Reject_t *Reject_copy(Reject_t **dst, Reject_t *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// IsoTime
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	TimeConv_full,
	TimeConv_date,
	TimeConv_clock
} TimeConv;

DZ1_CPPLINK IsoTime_t *IsoTime_new(time_t val, TimeConv conv, Dz1Error *err);
static __inline__ void IsoTime_del(IsoTime_t *p) { if (p) ASN1MSG_del(IsoTime, p); }
static __inline__ void IsoTime_dump(IsoTime_t *p, int tab) { if (p) ASN1MSG_dump(IsoTime, p, tab); }
static __inline__ void IsoTime_delAndSetNull(void *ptr)
{
	IsoTime_t **p = (IsoTime_t **)ptr;
	IsoTime_del(*p); *p = NULL;
}

DZ1_CPPLINK time_t IsoTime2time(IsoTime_t *src, Dz1Error *err);

DZ1_CPPLINK Dz1Error DailyBit_set(BIT_STRING_t *dst, u8_t dailyBit);

///////////////////////////////////////////////////////////////////////////////
// Publication
///////////////////////////////////////////////////////////////////////////////
// Create Publication for File Publication
DZ1_CPPLINK Publication_t *Publication_newFile(BOOLEAN_t guarantee, UTF8String_t *file, Dz1Error *err);

// Create Publication for Data Packet Publication
DZ1_CPPLINK Publication_t *Publication_newPacket(BOOLEAN_t guarantee, Dz1Error *err);

DZ1_CPPLINK Publication_t *Publication_copy(Publication_t **dst, Publication_t *src, Dz1Error *err);

// add Publication Management Signal to Packet Publication
DZ1_CPPLINK Dz1Error Publication_addMgmt(Publication_t *p, long subscriptionSerial, long publicationSerial, BOOLEAN_t late, datexPublication_Management_cd_e mgmt);

// add Publication Data to Packet Publication
DZ1_CPPLINK Dz1Error Publication_addData(Publication_t *p, long subscriptionSerial, long publicationSerial, BOOLEAN_t late,	str_t oid, u8_t *encoddedUserData, size_t encoddedUserDataSize);

static __inline__ void Publication_del(Publication_t *p) { if (p) ASN1MSG_del(Publication, p); }
static __inline__ void Publication_dump(Publication_t *p, int tab) { if (p) ASN1MSG_dump(Publication, p, tab); }
static __inline__ void Publication_delAndSetNull(void *ptr)
{
	Publication_t **p = (Publication_t **)ptr;
	Publication_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data
///////////////////////////////////////////////////////////////////////////////
static __inline__ void PublicationData_del(PublicationData_t *p) { if (p) ASN1MSG_del(PublicationData, p); }
static __inline__ void PublicationData_delAndSetNull(void *ptr)
{
	PublicationData_t **p = (PublicationData_t **)ptr;
	PublicationData_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Cost
///////////////////////////////////////////////////////////////////////////////
static __inline__ Cost_del(Cost_t *p) { if (p) ASN1MSG_del(Cost, p); }
static __inline__ Cost_delAndSetNull(void *ptr)
{
	Cost_t **p = (Cost_t **)ptr;
	Cost_del(*p); *p = NULL;
}
#else
DZ1_CPPLINK extern str_t __AssisterGeneralASN__;
#endif
#endif