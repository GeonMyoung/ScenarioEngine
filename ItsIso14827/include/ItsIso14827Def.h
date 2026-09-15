#ifndef _DZ1_TDC_ITS_ISO14827_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Iso14827dz1.h"
#include "ItsIso14827Types.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Exception
typedef void (*ItsIso14827Exception)(void *exceptionArg, Dz1Error *reason);
// ItsIso14827Exception
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CRCCheck
typedef enum ItsIso14827CRCCheck
{
	ItsIso14827CRCCheck_explict,
	ItsIso14827CRCCheck_warning,
	ItsIso14827CRCCheck_ignore,
	ItsIso14827CRCCheck_max
} ItsIso14827CRCCheck;

DZ1_CPPLINK str_t ItsIso14827CRCCheckStrA(ItsIso14827CRCCheck v);
DZ1_CPPLINK ItsIso14827CRCCheck ItsIso14827CRCCheckFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827CRCCheckStrW(ItsIso14827CRCCheck v);
DZ1_CPPLINK ItsIso14827CRCCheck ItsIso14827CRCCheckFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827CRCCheckStr ItsIso14827CRCCheckStrW
#define ItsIso14827CRCCheckFromStr ItsIso14827CRCCheckFromStrW
#else // UNICODE
#define ItsIso14827CRCCheckStr ItsIso14827CRCCheckStrA
#define ItsIso14827CRCCheckFromStr ItsIso14827CRCCheckFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827CRCCheckStr ItsIso14827CRCCheckStrA
#define ItsIso14827CRCCheckFromStr ItsIso14827CRCCheckFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827CRCCheck *ItsIso14827CRCCheck_new(ItsIso14827CRCCheck *src, Dz1Error *err);
static __inline__ ItsIso14827CRCCheck *ItsIso14827CRCCheck_gen(Dz1Error *err) { ItsIso14827CRCCheck v = ItsIso14827CRCCheck_max; return ItsIso14827CRCCheck_new(&v, err); }
static __inline__ void ItsIso14827CRCCheck_del(ItsIso14827CRCCheck *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827CRCCheck_delAndSetNull(void *ptr)
{
	ItsIso14827CRCCheck **p = (ItsIso14827CRCCheck **)ptr;
	if (p != NULL) { ItsIso14827CRCCheck_del(*p); *p = NULL; }
}
// ItsIso14827CRCCheck
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainType
typedef enum ItsIso14827DomainType
{
	ItsIso14827DomainType_server,
	ItsIso14827DomainType_client,
	ItsIso14827DomainType_max
} ItsIso14827DomainType;

DZ1_CPPLINK str_t ItsIso14827DomainTypeStrA(ItsIso14827DomainType v);
DZ1_CPPLINK ItsIso14827DomainType ItsIso14827DomainTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827DomainTypeStrW(ItsIso14827DomainType v);
DZ1_CPPLINK ItsIso14827DomainType ItsIso14827DomainTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827DomainTypeStr ItsIso14827DomainTypeStrW
#define ItsIso14827DomainTypeFromStr ItsIso14827DomainTypeFromStrW
#else // UNICODE
#define ItsIso14827DomainTypeStr ItsIso14827DomainTypeStrA
#define ItsIso14827DomainTypeFromStr ItsIso14827DomainTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827DomainTypeStr ItsIso14827DomainTypeStrA
#define ItsIso14827DomainTypeFromStr ItsIso14827DomainTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainType *ItsIso14827DomainType_new(ItsIso14827DomainType *src, Dz1Error *err);
static __inline__ ItsIso14827DomainType *ItsIso14827DomainType_gen(Dz1Error *err) { ItsIso14827DomainType v = ItsIso14827DomainType_max; return ItsIso14827DomainType_new(&v, err); }
static __inline__ void ItsIso14827DomainType_del(ItsIso14827DomainType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827DomainType_delAndSetNull(void *ptr)
{
	ItsIso14827DomainType **p = (ItsIso14827DomainType **)ptr;
	if (p != NULL) { ItsIso14827DomainType_del(*p); *p = NULL; }
}
// ItsIso14827DomainType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackDisconnected
typedef void (*ItsIso14827CallbackDisconnected)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user);
// ItsIso14827CallbackDisconnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackAuthenticate
typedef void (*ItsIso14827CallbackAuthenticate)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					Dz1Asn1OctetStr *pass, 
					Dz1Asn1OctetStr *authInfo, 
					s32_t hbDur, 
					s32_t timeout, 
					u8_t codecBits, 
					bool_t is_retried);
// ItsIso14827CallbackAuthenticate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackEstablished
typedef void (*ItsIso14827CallbackEstablished)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					Dz1Asn1Codec selected);
// ItsIso14827CallbackEstablished
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackEchoRequest
typedef void (*ItsIso14827CallbackEchoRequest)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t echoID);
// ItsIso14827CallbackEchoRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackSingle
typedef void (*ItsIso14827CallbackSingle)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackSingle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackEventPrepare
typedef void (*ItsIso14827CallbackEventPrepare)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					u32_t latency_sec, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackEventPrepare
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackPeriodicPrepare
typedef void (*ItsIso14827CallbackPeriodicPrepare)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					u32_t period_sec, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackPeriodicPrepare
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackPublicationStart
typedef void (*ItsIso14827CallbackPublicationStart)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackPublicationStart
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackPublicationInvoke
typedef void (*ItsIso14827CallbackPublicationInvoke)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackPublicationInvoke
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827PublicarionErrorPresent
typedef enum ItsIso14827PublicarionErrorPresent
{
	ItsIso14827PublicarionErrorPresent_pubError,
	ItsIso14827PublicarionErrorPresent_pubDataError,
	ItsIso14827PublicarionErrorPresent_max
} ItsIso14827PublicarionErrorPresent;

DZ1_CPPLINK str_t ItsIso14827PublicarionErrorPresentStrA(ItsIso14827PublicarionErrorPresent v);
DZ1_CPPLINK ItsIso14827PublicarionErrorPresent ItsIso14827PublicarionErrorPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827PublicarionErrorPresentStrW(ItsIso14827PublicarionErrorPresent v);
DZ1_CPPLINK ItsIso14827PublicarionErrorPresent ItsIso14827PublicarionErrorPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827PublicarionErrorPresentStr ItsIso14827PublicarionErrorPresentStrW
#define ItsIso14827PublicarionErrorPresentFromStr ItsIso14827PublicarionErrorPresentFromStrW
#else // UNICODE
#define ItsIso14827PublicarionErrorPresentStr ItsIso14827PublicarionErrorPresentStrA
#define ItsIso14827PublicarionErrorPresentFromStr ItsIso14827PublicarionErrorPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827PublicarionErrorPresentStr ItsIso14827PublicarionErrorPresentStrA
#define ItsIso14827PublicarionErrorPresentFromStr ItsIso14827PublicarionErrorPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827PublicarionErrorPresent *ItsIso14827PublicarionErrorPresent_new(ItsIso14827PublicarionErrorPresent *src, Dz1Error *err);
static __inline__ ItsIso14827PublicarionErrorPresent *ItsIso14827PublicarionErrorPresent_gen(Dz1Error *err) { ItsIso14827PublicarionErrorPresent v = ItsIso14827PublicarionErrorPresent_max; return ItsIso14827PublicarionErrorPresent_new(&v, err); }
#define ItsIso14827PublicarionErrorPresent_clone             ItsIso14827PublicarionErrorPresent_new
static __inline__ void ItsIso14827PublicarionErrorPresent_del(ItsIso14827PublicarionErrorPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827PublicarionErrorPresent_delAndSetNull(void *ptr)
{
	ItsIso14827PublicarionErrorPresent **p = (ItsIso14827PublicarionErrorPresent **)ptr;
	if (p != NULL) { ItsIso14827PublicarionErrorPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827PublicarionErrorPresent_dump(ItsIso14827PublicarionErrorPresent *v, int tab);
// ItsIso14827PublicarionErrorPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827PublicarionError
typedef struct ItsIso14827PublicarionError
{
	ItsIso14827PublicarionErrorPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827RejectPublication		pubError;
		Iso14827RejectPubDataReason		pubDataError;
	} x;
} ItsIso14827PublicarionError;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827PublicarionError *ItsIso14827PublicarionError_new(ItsIso14827PublicarionErrorPresent present, void *ptr, Dz1Error *err);
static __inline__ ItsIso14827PublicarionError *ItsIso14827PublicarionError_gen(Dz1Error *err) { return ItsIso14827PublicarionError_new(ItsIso14827PublicarionErrorPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ItsIso14827PublicarionError_copy(ItsIso14827PublicarionError *dst, ItsIso14827PublicarionError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827PublicarionError *ItsIso14827PublicarionError_clone(ItsIso14827PublicarionError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827PublicarionError_purge(ItsIso14827PublicarionError *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827PublicarionError_del(ItsIso14827PublicarionError *p);
static __inline__ void ItsIso14827PublicarionError_delAndSetNull(void *ptr)
{
	ItsIso14827PublicarionError **p = (ItsIso14827PublicarionError **)ptr;
	if (p != NULL) { ItsIso14827PublicarionError_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827PublicarionError_dump(ItsIso14827PublicarionError *p, int tab);
// ItsIso14827PublicarionError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackSubscriptionPubInfom
typedef void (*ItsIso14827CallbackSubscriptionPubInfom)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					ItsIso14827PublicarionError *reason);
// ItsIso14827CallbackSubscriptionPubInfom
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackSubscriptionStop
typedef void (*ItsIso14827CallbackSubscriptionStop)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID);
// ItsIso14827CallbackSubscriptionStop
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionExpireReasonPresent
typedef enum ItsIso14827SubscriptionExpireReasonPresent
{
	ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired,
	ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected,
	ItsIso14827SubscriptionExpireReasonPresent_clientRequested,
	ItsIso14827SubscriptionExpireReasonPresent_max
} ItsIso14827SubscriptionExpireReasonPresent;

DZ1_CPPLINK str_t ItsIso14827SubscriptionExpireReasonPresentStrA(ItsIso14827SubscriptionExpireReasonPresent v);
DZ1_CPPLINK ItsIso14827SubscriptionExpireReasonPresent ItsIso14827SubscriptionExpireReasonPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827SubscriptionExpireReasonPresentStrW(ItsIso14827SubscriptionExpireReasonPresent v);
DZ1_CPPLINK ItsIso14827SubscriptionExpireReasonPresent ItsIso14827SubscriptionExpireReasonPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827SubscriptionExpireReasonPresentStr ItsIso14827SubscriptionExpireReasonPresentStrW
#define ItsIso14827SubscriptionExpireReasonPresentFromStr ItsIso14827SubscriptionExpireReasonPresentFromStrW
#else // UNICODE
#define ItsIso14827SubscriptionExpireReasonPresentStr ItsIso14827SubscriptionExpireReasonPresentStrA
#define ItsIso14827SubscriptionExpireReasonPresentFromStr ItsIso14827SubscriptionExpireReasonPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827SubscriptionExpireReasonPresentStr ItsIso14827SubscriptionExpireReasonPresentStrA
#define ItsIso14827SubscriptionExpireReasonPresentFromStr ItsIso14827SubscriptionExpireReasonPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionExpireReasonPresent *ItsIso14827SubscriptionExpireReasonPresent_new(ItsIso14827SubscriptionExpireReasonPresent *src, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionExpireReasonPresent *ItsIso14827SubscriptionExpireReasonPresent_gen(Dz1Error *err) { ItsIso14827SubscriptionExpireReasonPresent v = ItsIso14827SubscriptionExpireReasonPresent_max; return ItsIso14827SubscriptionExpireReasonPresent_new(&v, err); }
#define ItsIso14827SubscriptionExpireReasonPresent_clone             ItsIso14827SubscriptionExpireReasonPresent_new
static __inline__ void ItsIso14827SubscriptionExpireReasonPresent_del(ItsIso14827SubscriptionExpireReasonPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827SubscriptionExpireReasonPresent_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionExpireReasonPresent **p = (ItsIso14827SubscriptionExpireReasonPresent **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionExpireReasonPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionExpireReasonPresent_dump(ItsIso14827SubscriptionExpireReasonPresent *v, int tab);
// ItsIso14827SubscriptionExpireReasonPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionExpireReason
typedef struct ItsIso14827SubscriptionExpireReason
{
	ItsIso14827SubscriptionExpireReasonPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t							*subscriptionExpired;
		u32_t							*clientDisconnected;
		Iso14827SubscriptionCancel		 clientRequested;
	} x;
} ItsIso14827SubscriptionExpireReason;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionExpireReason *ItsIso14827SubscriptionExpireReason_new(ItsIso14827SubscriptionExpireReasonPresent present, void *ptr, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionExpireReason *ItsIso14827SubscriptionExpireReason_gen(Dz1Error *err) { return ItsIso14827SubscriptionExpireReason_new(ItsIso14827SubscriptionExpireReasonPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ItsIso14827SubscriptionExpireReason_copy(ItsIso14827SubscriptionExpireReason *dst, ItsIso14827SubscriptionExpireReason *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionExpireReason *ItsIso14827SubscriptionExpireReason_clone(ItsIso14827SubscriptionExpireReason *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionExpireReason_purge(ItsIso14827SubscriptionExpireReason *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionExpireReason_del(ItsIso14827SubscriptionExpireReason *p);
static __inline__ void ItsIso14827SubscriptionExpireReason_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionExpireReason **p = (ItsIso14827SubscriptionExpireReason **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionExpireReason_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionExpireReason_dump(ItsIso14827SubscriptionExpireReason *p, int tab);
// ItsIso14827SubscriptionExpireReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackSubscriptionExpire
typedef void (*ItsIso14827CallbackSubscriptionExpire)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subID, 
					ItsIso14827SubscriptionExpireReason *reason);
// ItsIso14827CallbackSubscriptionExpire
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackSysHealthWarning
typedef void (*ItsIso14827CallbackSysHealthWarning)(void *param);
// ItsIso14827CallbackSysHealthWarning
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainCallback
typedef struct ItsIso14827ServerDomainCallback
{
	ItsIso14827CallbackAuthenticate				 authenticate;
	ItsIso14827CallbackEstablished				 established;
	ItsIso14827CallbackDisconnected				 disconnected;
	ItsIso14827CallbackEchoRequest				 echoRequest;
	ItsIso14827CallbackSingle					 singleRequest;
	ItsIso14827CallbackEventPrepare				 eventPrepare;
	ItsIso14827CallbackPublicationStart			 eventStart;
	ItsIso14827CallbackPeriodicPrepare			 periodicPreapre;
	ItsIso14827CallbackPublicationStart			 periodicStart;
	ItsIso14827CallbackPublicationInvoke		 periodicInvoke;
	ItsIso14827CallbackSubscriptionPubInfom		 pubErrorInform;
	ItsIso14827CallbackSubscriptionStop			 stopped;
	ItsIso14827CallbackSubscriptionExpire		 expired;
	ItsIso14827CallbackSysHealthWarning			 sysHealthWarning;
	void										*param;
} ItsIso14827ServerDomainCallback;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainCallback *ItsIso14827ServerDomainCallback_new(ItsIso14827CallbackAuthenticate authenticate, 
																							 ItsIso14827CallbackEstablished established, 
																							 ItsIso14827CallbackDisconnected disconnected, 
																							 ItsIso14827CallbackEchoRequest echoRequest, 
																							 ItsIso14827CallbackSingle singleRequest, 
																							 ItsIso14827CallbackEventPrepare eventPrepare, 
																							 ItsIso14827CallbackPublicationStart eventStart, 
																							 ItsIso14827CallbackPeriodicPrepare periodicPreapre, 
																							 ItsIso14827CallbackPublicationStart periodicStart, 
																							 ItsIso14827CallbackPublicationInvoke periodicInvoke, 
																							 ItsIso14827CallbackSubscriptionPubInfom pubErrorInform, 
																							 ItsIso14827CallbackSubscriptionStop stopped, 
																							 ItsIso14827CallbackSubscriptionExpire expired, 
																							 ItsIso14827CallbackSysHealthWarning sysHealthWarning, 
																							 void *param, Dz1Error *err);
static __inline__ ItsIso14827ServerDomainCallback *ItsIso14827ServerDomainCallback_gen(Dz1Error *err) { return ItsIso14827ServerDomainCallback_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerDomainCallback_copy(ItsIso14827ServerDomainCallback *dst, ItsIso14827ServerDomainCallback *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainCallback *ItsIso14827ServerDomainCallback_clone(ItsIso14827ServerDomainCallback *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainCallback_purge(ItsIso14827ServerDomainCallback *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainCallback_del(ItsIso14827ServerDomainCallback *p);
static __inline__ void ItsIso14827ServerDomainCallback_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainCallback **p = (ItsIso14827ServerDomainCallback **)ptr;
	if (p) { ItsIso14827ServerDomainCallback_del(*p); *p = NULL; }
}
// ItsIso14827ServerDomainCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientCtrlFlag_HeartBeatOFF
#define ItsIso14827ClientCtrlFlag_HeartBeatOFF			1
// ItsIso14827ClientCtrlFlag_HeartBeatOFF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientCtrlFlag_PubAckDeferred
#define ItsIso14827ClientCtrlFlag_PubAckDeferred			2
// ItsIso14827ClientCtrlFlag_PubAckDeferred
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackInitiated
typedef void (*ItsIso14827CallbackInitiated)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1Codec initial_codec, 
					ItsIso14827SessionKey *key);
// ItsIso14827CallbackInitiated
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackTerminate
typedef void (*ItsIso14827CallbackTerminate)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					Iso14827Terminate reason);
// ItsIso14827CallbackTerminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackPublication
typedef void (*ItsIso14827CallbackPublication)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subscriptionID, 
					u32_t pubSerial, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackPubControl
typedef void (*ItsIso14827CallbackPubControl)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					u32_t subscriptionID, 
					u32_t pubSerial, 
					Iso14827PublicationMgmt cmd);
// ItsIso14827CallbackPubControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainCallback
typedef struct ItsIso14827ClientDomainCallback
{
	ItsIso14827CallbackInitiated		 initiated;
	ItsIso14827CallbackDisconnected		 echo_responsed;
	ItsIso14827CallbackTerminate		 terminate;
	ItsIso14827CallbackPublication		 publication;
	ItsIso14827CallbackPubControl		 pubControl;
	ItsIso14827CallbackDisconnected		 disconnected;
	void								*param;
} ItsIso14827ClientDomainCallback;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainCallback *ItsIso14827ClientDomainCallback_new(ItsIso14827CallbackInitiated initiated, 
																							 ItsIso14827CallbackDisconnected echo_responsed, 
																							 ItsIso14827CallbackTerminate terminate, 
																							 ItsIso14827CallbackPublication publication, 
																							 ItsIso14827CallbackPubControl pubControl, 
																							 ItsIso14827CallbackDisconnected disconnected, 
																							 void *param, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainCallback *ItsIso14827ClientDomainCallback_gen(Dz1Error *err) { return ItsIso14827ClientDomainCallback_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientDomainCallback_copy(ItsIso14827ClientDomainCallback *dst, ItsIso14827ClientDomainCallback *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainCallback *ItsIso14827ClientDomainCallback_clone(ItsIso14827ClientDomainCallback *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainCallback_purge(ItsIso14827ClientDomainCallback *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainCallback_del(ItsIso14827ClientDomainCallback *p);
static __inline__ void ItsIso14827ClientDomainCallback_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainCallback **p = (ItsIso14827ClientDomainCallback **)ptr;
	if (p) { ItsIso14827ClientDomainCallback_del(*p); *p = NULL; }
}
// ItsIso14827ClientDomainCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CallbackViolatedSubRcvd
typedef void (*ItsIso14827CallbackViolatedSubRcvd)(
					void *param, 
					Dz1Asn1UTF8Str *myDomain, 
					Dz1Asn1UTF8Str *peerDomain, 
					Dz1Asn1OctetStr *user, 
					bool_t guaranteed, 
					u32_t subID, 
					str_t oidStr, 
					u8_t *encodedEAM, 
					u32_t encodedEAMSize);
// ItsIso14827CallbackViolatedSubRcvd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventAuth
typedef struct ItsIso14827ServerEventAuth
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	Dz1Asn1OctetStr		*pass;
	Dz1Asn1OctetStr		*authInfo;
	s32_t				 hbDur;
	s32_t				 timeout;
	u8_t				 codecBits;
	bool_t				 is_retried;
} ItsIso14827ServerEventAuth;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventAuth *ItsIso14827ServerEventAuth_new(Dz1Asn1UTF8Str *myDomain, 
																				   Dz1Asn1UTF8Str *peerDomain, 
																				   Dz1Asn1OctetStr *user, 
																				   Dz1Asn1OctetStr *pass, 
																				   Dz1Asn1OctetStr *authInfo, 
																				   s32_t hbDur, 
																				   s32_t timeout, 
																				   u8_t codecBits, 
																				   bool_t is_retried, Dz1Error *err);
static __inline__ ItsIso14827ServerEventAuth *ItsIso14827ServerEventAuth_gen(Dz1Error *err) { return ItsIso14827ServerEventAuth_new(NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventAuth_copy(ItsIso14827ServerEventAuth *dst, ItsIso14827ServerEventAuth *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventAuth *ItsIso14827ServerEventAuth_clone(ItsIso14827ServerEventAuth *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventAuth_purge(ItsIso14827ServerEventAuth *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventAuth_del(ItsIso14827ServerEventAuth *p);
static __inline__ void ItsIso14827ServerEventAuth_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventAuth **p = (ItsIso14827ServerEventAuth **)ptr;
	if (p) { ItsIso14827ServerEventAuth_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventAuth_dump(ItsIso14827ServerEventAuth *p, int tab);
// ItsIso14827ServerEventAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventConnected
typedef struct ItsIso14827ServerEventConnected
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	Dz1Asn1Codec		 selected;
} ItsIso14827ServerEventConnected;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventConnected *ItsIso14827ServerEventConnected_new(Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 Dz1Asn1Codec selected, Dz1Error *err);
static __inline__ ItsIso14827ServerEventConnected *ItsIso14827ServerEventConnected_gen(Dz1Error *err) { return ItsIso14827ServerEventConnected_new(NULL, NULL, NULL, Dz1Asn1Codec_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventConnected_copy(ItsIso14827ServerEventConnected *dst, ItsIso14827ServerEventConnected *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventConnected *ItsIso14827ServerEventConnected_clone(ItsIso14827ServerEventConnected *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventConnected_purge(ItsIso14827ServerEventConnected *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventConnected_del(ItsIso14827ServerEventConnected *p);
static __inline__ void ItsIso14827ServerEventConnected_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventConnected **p = (ItsIso14827ServerEventConnected **)ptr;
	if (p) { ItsIso14827ServerEventConnected_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventConnected_dump(ItsIso14827ServerEventConnected *p, int tab);
// ItsIso14827ServerEventConnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventEcho
typedef struct ItsIso14827ServerEventEcho
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 echoID;
} ItsIso14827ServerEventEcho;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventEcho *ItsIso14827ServerEventEcho_new(Dz1Asn1UTF8Str *myDomain, 
																				   Dz1Asn1UTF8Str *peerDomain, 
																				   Dz1Asn1OctetStr *user, 
																				   u32_t echoID, Dz1Error *err);
static __inline__ ItsIso14827ServerEventEcho *ItsIso14827ServerEventEcho_gen(Dz1Error *err) { return ItsIso14827ServerEventEcho_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventEcho_copy(ItsIso14827ServerEventEcho *dst, ItsIso14827ServerEventEcho *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventEcho *ItsIso14827ServerEventEcho_clone(ItsIso14827ServerEventEcho *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventEcho_purge(ItsIso14827ServerEventEcho *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventEcho_del(ItsIso14827ServerEventEcho *p);
static __inline__ void ItsIso14827ServerEventEcho_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventEcho **p = (ItsIso14827ServerEventEcho **)ptr;
	if (p) { ItsIso14827ServerEventEcho_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventEcho_dump(ItsIso14827ServerEventEcho *p, int tab);
// ItsIso14827ServerEventEcho
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubSignle
typedef struct ItsIso14827ServerEventSubSignle
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 subID;
	str_t				 oidStr;
	u8_t				*encodedEAM;
	u32_t				 encodedEAMSize;
} ItsIso14827ServerEventSubSignle;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubSignle *ItsIso14827ServerEventSubSignle_new(Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 u32_t subID, 
																							 str_t oidStr, 
																							 u8_t *encodedEAM, 
																							 u32_t encodedEAMSize, Dz1Error *err);
static __inline__ ItsIso14827ServerEventSubSignle *ItsIso14827ServerEventSubSignle_gen(Dz1Error *err) { return ItsIso14827ServerEventSubSignle_new(NULL, NULL, NULL, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventSubSignle_copy(ItsIso14827ServerEventSubSignle *dst, ItsIso14827ServerEventSubSignle *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubSignle *ItsIso14827ServerEventSubSignle_clone(ItsIso14827ServerEventSubSignle *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubSignle_purge(ItsIso14827ServerEventSubSignle *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubSignle_del(ItsIso14827ServerEventSubSignle *p);
static __inline__ void ItsIso14827ServerEventSubSignle_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventSubSignle **p = (ItsIso14827ServerEventSubSignle **)ptr;
	if (p) { ItsIso14827ServerEventSubSignle_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubSignle_dump(ItsIso14827ServerEventSubSignle *p, int tab);
// ItsIso14827ServerEventSubSignle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubPrepareED
typedef struct ItsIso14827ServerEventSubPrepareED
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 subID;
	u32_t				 latency_sec;
	str_t				 oidStr;
	u8_t				*encodedEAM;
	u32_t				 encodedEAMSize;
} ItsIso14827ServerEventSubPrepareED;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubPrepareED *ItsIso14827ServerEventSubPrepareED_new(Dz1Asn1UTF8Str *myDomain, 
																								   Dz1Asn1UTF8Str *peerDomain, 
																								   Dz1Asn1OctetStr *user, 
																								   u32_t subID, 
																								   u32_t latency_sec, 
																								   str_t oidStr, 
																								   u8_t *encodedEAM, 
																								   u32_t encodedEAMSize, Dz1Error *err);
static __inline__ ItsIso14827ServerEventSubPrepareED *ItsIso14827ServerEventSubPrepareED_gen(Dz1Error *err) { return ItsIso14827ServerEventSubPrepareED_new(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventSubPrepareED_copy(ItsIso14827ServerEventSubPrepareED *dst, ItsIso14827ServerEventSubPrepareED *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubPrepareED *ItsIso14827ServerEventSubPrepareED_clone(ItsIso14827ServerEventSubPrepareED *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareED_purge(ItsIso14827ServerEventSubPrepareED *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareED_del(ItsIso14827ServerEventSubPrepareED *p);
static __inline__ void ItsIso14827ServerEventSubPrepareED_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventSubPrepareED **p = (ItsIso14827ServerEventSubPrepareED **)ptr;
	if (p) { ItsIso14827ServerEventSubPrepareED_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareED_dump(ItsIso14827ServerEventSubPrepareED *p, int tab);
// ItsIso14827ServerEventSubPrepareED
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubPrepareP
typedef struct ItsIso14827ServerEventSubPrepareP
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 subID;
	u32_t				 period_sec;
	str_t				 oidStr;
	u8_t				*encodedEAM;
	u32_t				 encodedEAMSize;
} ItsIso14827ServerEventSubPrepareP;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubPrepareP *ItsIso14827ServerEventSubPrepareP_new(Dz1Asn1UTF8Str *myDomain, 
																								 Dz1Asn1UTF8Str *peerDomain, 
																								 Dz1Asn1OctetStr *user, 
																								 u32_t subID, 
																								 u32_t period_sec, 
																								 str_t oidStr, 
																								 u8_t *encodedEAM, 
																								 u32_t encodedEAMSize, Dz1Error *err);
static __inline__ ItsIso14827ServerEventSubPrepareP *ItsIso14827ServerEventSubPrepareP_gen(Dz1Error *err) { return ItsIso14827ServerEventSubPrepareP_new(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventSubPrepareP_copy(ItsIso14827ServerEventSubPrepareP *dst, ItsIso14827ServerEventSubPrepareP *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventSubPrepareP *ItsIso14827ServerEventSubPrepareP_clone(ItsIso14827ServerEventSubPrepareP *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareP_purge(ItsIso14827ServerEventSubPrepareP *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareP_del(ItsIso14827ServerEventSubPrepareP *p);
static __inline__ void ItsIso14827ServerEventSubPrepareP_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventSubPrepareP **p = (ItsIso14827ServerEventSubPrepareP **)ptr;
	if (p) { ItsIso14827ServerEventSubPrepareP_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventSubPrepareP_dump(ItsIso14827ServerEventSubPrepareP *p, int tab);
// ItsIso14827ServerEventSubPrepareP
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubStart
typedef struct ItsIso14827ServerEventPubStart
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 subID;
	str_t				 oidStr;
	u8_t				*encodedEAM;
	u32_t				 encodedEAMSize;
} ItsIso14827ServerEventPubStart;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubStart *ItsIso14827ServerEventPubStart_new(Dz1Asn1UTF8Str *myDomain, 
																						   Dz1Asn1UTF8Str *peerDomain, 
																						   Dz1Asn1OctetStr *user, 
																						   u32_t subID, 
																						   str_t oidStr, 
																						   u8_t *encodedEAM, 
																						   u32_t encodedEAMSize, Dz1Error *err);
static __inline__ ItsIso14827ServerEventPubStart *ItsIso14827ServerEventPubStart_gen(Dz1Error *err) { return ItsIso14827ServerEventPubStart_new(NULL, NULL, NULL, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventPubStart_copy(ItsIso14827ServerEventPubStart *dst, ItsIso14827ServerEventPubStart *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubStart *ItsIso14827ServerEventPubStart_clone(ItsIso14827ServerEventPubStart *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStart_purge(ItsIso14827ServerEventPubStart *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStart_del(ItsIso14827ServerEventPubStart *p);
static __inline__ void ItsIso14827ServerEventPubStart_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventPubStart **p = (ItsIso14827ServerEventPubStart **)ptr;
	if (p) { ItsIso14827ServerEventPubStart_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStart_dump(ItsIso14827ServerEventPubStart *p, int tab);
// ItsIso14827ServerEventPubStart
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubInform
typedef struct ItsIso14827ServerEventPubInform
{
	Dz1Asn1UTF8Str					*myDomain;
	Dz1Asn1UTF8Str					*peerDomain;
	Dz1Asn1OctetStr					*user;
	u32_t							 subID;
	ItsIso14827PublicarionError		*reason;
} ItsIso14827ServerEventPubInform;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubInform *ItsIso14827ServerEventPubInform_new(Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 u32_t subID, 
																							 ItsIso14827PublicarionError *reason, Dz1Error *err);
static __inline__ ItsIso14827ServerEventPubInform *ItsIso14827ServerEventPubInform_gen(Dz1Error *err) { return ItsIso14827ServerEventPubInform_new(NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventPubInform_copy(ItsIso14827ServerEventPubInform *dst, ItsIso14827ServerEventPubInform *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubInform *ItsIso14827ServerEventPubInform_clone(ItsIso14827ServerEventPubInform *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubInform_purge(ItsIso14827ServerEventPubInform *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubInform_del(ItsIso14827ServerEventPubInform *p);
static __inline__ void ItsIso14827ServerEventPubInform_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventPubInform **p = (ItsIso14827ServerEventPubInform **)ptr;
	if (p) { ItsIso14827ServerEventPubInform_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubInform_dump(ItsIso14827ServerEventPubInform *p, int tab);
// ItsIso14827ServerEventPubInform
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubStop
typedef struct ItsIso14827ServerEventPubStop
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 subID;
} ItsIso14827ServerEventPubStop;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubStop *ItsIso14827ServerEventPubStop_new(Dz1Asn1UTF8Str *myDomain, 
																						 Dz1Asn1UTF8Str *peerDomain, 
																						 Dz1Asn1OctetStr *user, 
																						 u32_t subID, Dz1Error *err);
static __inline__ ItsIso14827ServerEventPubStop *ItsIso14827ServerEventPubStop_gen(Dz1Error *err) { return ItsIso14827ServerEventPubStop_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventPubStop_copy(ItsIso14827ServerEventPubStop *dst, ItsIso14827ServerEventPubStop *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubStop *ItsIso14827ServerEventPubStop_clone(ItsIso14827ServerEventPubStop *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStop_purge(ItsIso14827ServerEventPubStop *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStop_del(ItsIso14827ServerEventPubStop *p);
static __inline__ void ItsIso14827ServerEventPubStop_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventPubStop **p = (ItsIso14827ServerEventPubStop **)ptr;
	if (p) { ItsIso14827ServerEventPubStop_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubStop_dump(ItsIso14827ServerEventPubStop *p, int tab);
// ItsIso14827ServerEventPubStop
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubExpire
typedef struct ItsIso14827ServerEventPubExpire
{
	Dz1Asn1UTF8Str							*myDomain;
	Dz1Asn1UTF8Str							*peerDomain;
	Dz1Asn1OctetStr							*user;
	u32_t									 subID;
	ItsIso14827SubscriptionExpireReason		*reason;
} ItsIso14827ServerEventPubExpire;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubExpire *ItsIso14827ServerEventPubExpire_new(Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 u32_t subID, 
																							 ItsIso14827SubscriptionExpireReason *reason, Dz1Error *err);
static __inline__ ItsIso14827ServerEventPubExpire *ItsIso14827ServerEventPubExpire_gen(Dz1Error *err) { return ItsIso14827ServerEventPubExpire_new(NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerEventPubExpire_copy(ItsIso14827ServerEventPubExpire *dst, ItsIso14827ServerEventPubExpire *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerEventPubExpire *ItsIso14827ServerEventPubExpire_clone(ItsIso14827ServerEventPubExpire *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubExpire_purge(ItsIso14827ServerEventPubExpire *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubExpire_del(ItsIso14827ServerEventPubExpire *p);
static __inline__ void ItsIso14827ServerEventPubExpire_delAndSetNull(void *ptr)
{
	ItsIso14827ServerEventPubExpire **p = (ItsIso14827ServerEventPubExpire **)ptr;
	if (p) { ItsIso14827ServerEventPubExpire_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerEventPubExpire_dump(ItsIso14827ServerEventPubExpire *p, int tab);
// ItsIso14827ServerEventPubExpire
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventInitiate
typedef struct ItsIso14827ClientEventInitiate
{
	Dz1Asn1UTF8Str				*myDomain;
	Dz1Asn1UTF8Str				*peerDomain;
	Dz1Asn1Codec				 initial_codec;
	ItsIso14827SessionKey		*key;
} ItsIso14827ClientEventInitiate;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventInitiate *ItsIso14827ClientEventInitiate_new(Dz1Asn1UTF8Str *myDomain, 
																						   Dz1Asn1UTF8Str *peerDomain, 
																						   Dz1Asn1Codec initial_codec, 
																						   ItsIso14827SessionKey *key, Dz1Error *err);
static __inline__ ItsIso14827ClientEventInitiate *ItsIso14827ClientEventInitiate_gen(Dz1Error *err) { return ItsIso14827ClientEventInitiate_new(NULL, NULL, Dz1Asn1Codec_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientEventInitiate_copy(ItsIso14827ClientEventInitiate *dst, ItsIso14827ClientEventInitiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventInitiate *ItsIso14827ClientEventInitiate_clone(ItsIso14827ClientEventInitiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventInitiate_purge(ItsIso14827ClientEventInitiate *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventInitiate_del(ItsIso14827ClientEventInitiate *p);
static __inline__ void ItsIso14827ClientEventInitiate_delAndSetNull(void *ptr)
{
	ItsIso14827ClientEventInitiate **p = (ItsIso14827ClientEventInitiate **)ptr;
	if (p) { ItsIso14827ClientEventInitiate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventInitiate_dump(ItsIso14827ClientEventInitiate *p, int tab);
// ItsIso14827ClientEventInitiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventTerminate
typedef struct ItsIso14827ClientEventTerminate
{
	Dz1Asn1UTF8Str			*myDomain;
	Dz1Asn1UTF8Str			*peerDomain;
	Dz1Asn1OctetStr			*user;
	Iso14827Terminate		 reason;
} ItsIso14827ClientEventTerminate;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventTerminate *ItsIso14827ClientEventTerminate_new(Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 Iso14827Terminate reason, Dz1Error *err);
static __inline__ ItsIso14827ClientEventTerminate *ItsIso14827ClientEventTerminate_gen(Dz1Error *err) { return ItsIso14827ClientEventTerminate_new(NULL, NULL, NULL, Iso14827Terminate_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientEventTerminate_copy(ItsIso14827ClientEventTerminate *dst, ItsIso14827ClientEventTerminate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventTerminate *ItsIso14827ClientEventTerminate_clone(ItsIso14827ClientEventTerminate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventTerminate_purge(ItsIso14827ClientEventTerminate *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventTerminate_del(ItsIso14827ClientEventTerminate *p);
static __inline__ void ItsIso14827ClientEventTerminate_delAndSetNull(void *ptr)
{
	ItsIso14827ClientEventTerminate **p = (ItsIso14827ClientEventTerminate **)ptr;
	if (p) { ItsIso14827ClientEventTerminate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventTerminate_dump(ItsIso14827ClientEventTerminate *p, int tab);
// ItsIso14827ClientEventTerminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventPublication
typedef struct ItsIso14827ClientEventPublication
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
	u32_t				 sid;
	u32_t				 pubSerial;
	str_t				 oidStr;
	u8_t				*encodedEAM;
	u32_t				 encodedEAMSize;
} ItsIso14827ClientEventPublication;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventPublication *ItsIso14827ClientEventPublication_new(Dz1Asn1UTF8Str *myDomain, 
																								 Dz1Asn1UTF8Str *peerDomain, 
																								 Dz1Asn1OctetStr *user, 
																								 u32_t sid, 
																								 u32_t pubSerial, 
																								 str_t oidStr, 
																								 u8_t *encodedEAM, 
																								 u32_t encodedEAMSize, Dz1Error *err);
static __inline__ ItsIso14827ClientEventPublication *ItsIso14827ClientEventPublication_gen(Dz1Error *err) { return ItsIso14827ClientEventPublication_new(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientEventPublication_copy(ItsIso14827ClientEventPublication *dst, ItsIso14827ClientEventPublication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventPublication *ItsIso14827ClientEventPublication_clone(ItsIso14827ClientEventPublication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPublication_purge(ItsIso14827ClientEventPublication *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPublication_del(ItsIso14827ClientEventPublication *p);
static __inline__ void ItsIso14827ClientEventPublication_delAndSetNull(void *ptr)
{
	ItsIso14827ClientEventPublication **p = (ItsIso14827ClientEventPublication **)ptr;
	if (p) { ItsIso14827ClientEventPublication_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPublication_dump(ItsIso14827ClientEventPublication *p, int tab);
// ItsIso14827ClientEventPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventPubControl
typedef struct ItsIso14827ClientEventPubControl
{
	Dz1Asn1UTF8Str				*myDomain;
	Dz1Asn1UTF8Str				*peerDomain;
	Dz1Asn1OctetStr				*user;
	u32_t						 sid;
	u32_t						 pubSerial;
	Iso14827PublicationMgmt		 cmd;
} ItsIso14827ClientEventPubControl;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventPubControl *ItsIso14827ClientEventPubControl_new(Dz1Asn1UTF8Str *myDomain, 
																							   Dz1Asn1UTF8Str *peerDomain, 
																							   Dz1Asn1OctetStr *user, 
																							   u32_t sid, 
																							   u32_t pubSerial, 
																							   Iso14827PublicationMgmt cmd, Dz1Error *err);
static __inline__ ItsIso14827ClientEventPubControl *ItsIso14827ClientEventPubControl_gen(Dz1Error *err) { return ItsIso14827ClientEventPubControl_new(NULL, NULL, NULL, 0, 0, Iso14827PublicationMgmt_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientEventPubControl_copy(ItsIso14827ClientEventPubControl *dst, ItsIso14827ClientEventPubControl *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientEventPubControl *ItsIso14827ClientEventPubControl_clone(ItsIso14827ClientEventPubControl *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPubControl_purge(ItsIso14827ClientEventPubControl *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPubControl_del(ItsIso14827ClientEventPubControl *p);
static __inline__ void ItsIso14827ClientEventPubControl_delAndSetNull(void *ptr)
{
	ItsIso14827ClientEventPubControl **p = (ItsIso14827ClientEventPubControl **)ptr;
	if (p) { ItsIso14827ClientEventPubControl_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientEventPubControl_dump(ItsIso14827ClientEventPubControl *p, int tab);
// ItsIso14827ClientEventPubControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827EventDisconnected
typedef struct ItsIso14827EventDisconnected
{
	Dz1Asn1UTF8Str		*myDomain;
	Dz1Asn1UTF8Str		*peerDomain;
	Dz1Asn1OctetStr		*user;
} ItsIso14827EventDisconnected;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827EventDisconnected *ItsIso14827EventDisconnected_new(Dz1Asn1UTF8Str *myDomain, 
																					   Dz1Asn1UTF8Str *peerDomain, 
																					   Dz1Asn1OctetStr *user, Dz1Error *err);
static __inline__ ItsIso14827EventDisconnected *ItsIso14827EventDisconnected_gen(Dz1Error *err) { return ItsIso14827EventDisconnected_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827EventDisconnected_copy(ItsIso14827EventDisconnected *dst, ItsIso14827EventDisconnected *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827EventDisconnected *ItsIso14827EventDisconnected_clone(ItsIso14827EventDisconnected *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827EventDisconnected_purge(ItsIso14827EventDisconnected *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827EventDisconnected_del(ItsIso14827EventDisconnected *p);
static __inline__ void ItsIso14827EventDisconnected_delAndSetNull(void *ptr)
{
	ItsIso14827EventDisconnected **p = (ItsIso14827EventDisconnected **)ptr;
	if (p) { ItsIso14827EventDisconnected_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827EventDisconnected_dump(ItsIso14827EventDisconnected *p, int tab);
// ItsIso14827EventDisconnected
////////////////////////////////////////////////////////////////////////////////

#endif
