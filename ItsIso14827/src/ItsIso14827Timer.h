#ifndef _DZ1_TDC_ITS_ISO14827_TIMER_H_
#define _DZ1_TDC_ITS_ISO14827_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"
#include "ItsIso14827DomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionTimer
typedef struct ItsIso14827SessionTimer
{
	ItsIso14827SessionKey		*key;
	u32_t						 id;
} ItsIso14827SessionTimer;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionTimer *ItsIso14827SessionTimer_new(ItsIso14827SessionKey *key, 
																			 u32_t id, Dz1Error *err);
static __inline__ ItsIso14827SessionTimer *ItsIso14827SessionTimer_gen(Dz1Error *err) { return ItsIso14827SessionTimer_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionTimer_purge(ItsIso14827SessionTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionTimer_del(ItsIso14827SessionTimer *p);
static __inline__ void ItsIso14827SessionTimer_delAndSetNull(void *ptr)
{
	ItsIso14827SessionTimer **p = (ItsIso14827SessionTimer **)ptr;
	if (p) { ItsIso14827SessionTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionTimer_dump(ItsIso14827SessionTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827SessionTimer_cmp(ItsIso14827SessionTimer *a, ItsIso14827SessionTimer *b); 
// ItsIso14827SessionTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTimer
typedef struct ItsIso14827DomainTimer
{
	ItsIso14827DomainKey	*key;
	Dz1Asn1UTF8Str			*peer;
	Dz1Asn1OctetStr			*user;
	u32_t					 id;
} ItsIso14827DomainTimer;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainTimer *ItsIso14827DomainTimer_new(ItsIso14827DomainKey *key, 
																		   Dz1Asn1UTF8Str *peer, 
																		   Dz1Asn1OctetStr *user, 
																		   u32_t id, Dz1Error *err);
static __inline__ ItsIso14827DomainTimer *ItsIso14827DomainTimer_gen(Dz1Error *err) { return ItsIso14827DomainTimer_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTimer_purge(ItsIso14827DomainTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTimer_del(ItsIso14827DomainTimer *p);
static __inline__ void ItsIso14827DomainTimer_delAndSetNull(void *ptr)
{
	ItsIso14827DomainTimer **p = (ItsIso14827DomainTimer **)ptr;
	if (p) { ItsIso14827DomainTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTimer_dump(ItsIso14827DomainTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainTimer_cmp(ItsIso14827DomainTimer *a, ItsIso14827DomainTimer *b); 
// ItsIso14827DomainTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionTimer
typedef struct ItsIso14827SubscriptionTimer
{
	ItsIso14827DomainKey	*key;
	Dz1Asn1UTF8Str			*peer;
	Dz1Asn1OctetStr			*user;
	u32_t					 subID;
	u32_t					 id;
} ItsIso14827SubscriptionTimer;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionTimer *ItsIso14827SubscriptionTimer_new(ItsIso14827DomainKey *key, 
																					   Dz1Asn1UTF8Str *peer, 
																					   Dz1Asn1OctetStr *user, 
																					   u32_t subID, 
																					   u32_t id, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionTimer *ItsIso14827SubscriptionTimer_gen(Dz1Error *err) { return ItsIso14827SubscriptionTimer_new(NULL, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionTimer_purge(ItsIso14827SubscriptionTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionTimer_del(ItsIso14827SubscriptionTimer *p);
static __inline__ void ItsIso14827SubscriptionTimer_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionTimer **p = (ItsIso14827SubscriptionTimer **)ptr;
	if (p) { ItsIso14827SubscriptionTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionTimer_dump(ItsIso14827SubscriptionTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827SubscriptionTimer_cmp(ItsIso14827SubscriptionTimer *a, ItsIso14827SubscriptionTimer *b); 
// ItsIso14827SubscriptionTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827TimerPresent
typedef enum ItsIso14827TimerPresent
{
	ItsIso14827TimerPresent_session,
	ItsIso14827TimerPresent_domain,
	ItsIso14827TimerPresent_subscription,
	ItsIso14827TimerPresent_max
} ItsIso14827TimerPresent;

DZ1_CPPLINK str_t ItsIso14827TimerPresentStrA(ItsIso14827TimerPresent v);
DZ1_CPPLINK ItsIso14827TimerPresent ItsIso14827TimerPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827TimerPresentStrW(ItsIso14827TimerPresent v);
DZ1_CPPLINK ItsIso14827TimerPresent ItsIso14827TimerPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827TimerPresentStr ItsIso14827TimerPresentStrW
#define ItsIso14827TimerPresentFromStr ItsIso14827TimerPresentFromStrW
#else // UNICODE
#define ItsIso14827TimerPresentStr ItsIso14827TimerPresentStrA
#define ItsIso14827TimerPresentFromStr ItsIso14827TimerPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827TimerPresentStr ItsIso14827TimerPresentStrA
#define ItsIso14827TimerPresentFromStr ItsIso14827TimerPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827TimerPresent *ItsIso14827TimerPresent_new(ItsIso14827TimerPresent *src, Dz1Error *err);
static __inline__ ItsIso14827TimerPresent *ItsIso14827TimerPresent_gen(Dz1Error *err) { ItsIso14827TimerPresent v = ItsIso14827TimerPresent_max; return ItsIso14827TimerPresent_new(&v, err); }
static __inline__ void ItsIso14827TimerPresent_del(ItsIso14827TimerPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827TimerPresent_delAndSetNull(void *ptr)
{
	ItsIso14827TimerPresent **p = (ItsIso14827TimerPresent **)ptr;
	if (p != NULL) { ItsIso14827TimerPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827TimerPresent_dump(ItsIso14827TimerPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827TimerPresent_cmp(ItsIso14827TimerPresent *a, ItsIso14827TimerPresent *b);
// ItsIso14827TimerPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Timer
typedef struct ItsIso14827Timer
{
	ItsIso14827TimerPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ItsIso14827SessionTimer			*session;
		ItsIso14827DomainTimer			*domain;
		ItsIso14827SubscriptionTimer	*subscription;
	} x;
} ItsIso14827Timer;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827Timer *ItsIso14827Timer_new(ItsIso14827TimerPresent present, void *ptr, Dz1Error *err);
static __inline__ ItsIso14827Timer *ItsIso14827Timer_gen(Dz1Error *err) { return ItsIso14827Timer_new(ItsIso14827TimerPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Timer_purge(ItsIso14827Timer *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Timer_del(ItsIso14827Timer *p);
static __inline__ void ItsIso14827Timer_delAndSetNull(void *ptr)
{
	ItsIso14827Timer **p = (ItsIso14827Timer **)ptr;
	if (p != NULL) { ItsIso14827Timer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Timer_dump(ItsIso14827Timer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827Timer_cmp(ItsIso14827Timer *a, ItsIso14827Timer *b);
// ItsIso14827Timer
////////////////////////////////////////////////////////////////////////////////

#endif
