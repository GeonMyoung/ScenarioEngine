#ifndef _DZ1_TDC_ITS_ISO14827_SERVER_DOMAIN_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_SERVER_DOMAIN_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DefLocal.h"
#include "ItsIso14827SessionDef.h"
#include "ItsIso14827Domain_txFIFO.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionState
typedef enum ItsIso14827SubscriptionState
{
	ItsIso14827SubscriptionState_waitAddConfirm,
	ItsIso14827SubscriptionState_established,
	ItsIso14827SubscriptionState_waitUpdateConfirm,
	ItsIso14827SubscriptionState_waitDeleteConfirm,
	ItsIso14827SubscriptionState_max
} ItsIso14827SubscriptionState;

DZ1_CPPLINK str_t ItsIso14827SubscriptionStateStrA(ItsIso14827SubscriptionState v);
DZ1_CPPLINK ItsIso14827SubscriptionState ItsIso14827SubscriptionStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827SubscriptionStateStrW(ItsIso14827SubscriptionState v);
DZ1_CPPLINK ItsIso14827SubscriptionState ItsIso14827SubscriptionStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827SubscriptionStateStr ItsIso14827SubscriptionStateStrW
#define ItsIso14827SubscriptionStateFromStr ItsIso14827SubscriptionStateFromStrW
#else // UNICODE
#define ItsIso14827SubscriptionStateStr ItsIso14827SubscriptionStateStrA
#define ItsIso14827SubscriptionStateFromStr ItsIso14827SubscriptionStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827SubscriptionStateStr ItsIso14827SubscriptionStateStrA
#define ItsIso14827SubscriptionStateFromStr ItsIso14827SubscriptionStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionState *ItsIso14827SubscriptionState_new(ItsIso14827SubscriptionState *src, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionState *ItsIso14827SubscriptionState_gen(Dz1Error *err) { ItsIso14827SubscriptionState v = ItsIso14827SubscriptionState_max; return ItsIso14827SubscriptionState_new(&v, err); }
static __inline__ void ItsIso14827SubscriptionState_del(ItsIso14827SubscriptionState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827SubscriptionState_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionState **p = (ItsIso14827SubscriptionState **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionState_del(*p); *p = NULL; }
}
// ItsIso14827SubscriptionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionEvent
typedef enum ItsIso14827SubscriptionEvent
{
	ItsIso14827SubscriptionEvent_create,
	ItsIso14827SubscriptionEvent_update,
	ItsIso14827SubscriptionEvent_delete,
	ItsIso14827SubscriptionEvent_accept,
	ItsIso14827SubscriptionEvent_reject,
	ItsIso14827SubscriptionEvent_publication,
	ItsIso14827SubscriptionEvent_peerReject,
	ItsIso14827SubscriptionEvent_max
} ItsIso14827SubscriptionEvent;

DZ1_CPPLINK str_t ItsIso14827SubscriptionEventStrA(ItsIso14827SubscriptionEvent v);
DZ1_CPPLINK ItsIso14827SubscriptionEvent ItsIso14827SubscriptionEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827SubscriptionEventStrW(ItsIso14827SubscriptionEvent v);
DZ1_CPPLINK ItsIso14827SubscriptionEvent ItsIso14827SubscriptionEventFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827SubscriptionEventStr ItsIso14827SubscriptionEventStrW
#define ItsIso14827SubscriptionEventFromStr ItsIso14827SubscriptionEventFromStrW
#else // UNICODE
#define ItsIso14827SubscriptionEventStr ItsIso14827SubscriptionEventStrA
#define ItsIso14827SubscriptionEventFromStr ItsIso14827SubscriptionEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827SubscriptionEventStr ItsIso14827SubscriptionEventStrA
#define ItsIso14827SubscriptionEventFromStr ItsIso14827SubscriptionEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionEvent *ItsIso14827SubscriptionEvent_new(ItsIso14827SubscriptionEvent *src, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionEvent *ItsIso14827SubscriptionEvent_gen(Dz1Error *err) { ItsIso14827SubscriptionEvent v = ItsIso14827SubscriptionEvent_max; return ItsIso14827SubscriptionEvent_new(&v, err); }
static __inline__ void ItsIso14827SubscriptionEvent_del(ItsIso14827SubscriptionEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827SubscriptionEvent_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionEvent **p = (ItsIso14827SubscriptionEvent **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionEvent_del(*p); *p = NULL; }
}
// ItsIso14827SubscriptionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionReq
typedef struct ItsIso14827SubscriptionReq
{
	u32_t						 pktNbr;
	Iso14827SubscriptionData	*data;
} ItsIso14827SubscriptionReq;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionReq *ItsIso14827SubscriptionReq_new(u32_t pktNbr, 
																				   Iso14827SubscriptionData *data, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionReq *ItsIso14827SubscriptionReq_gen(Dz1Error *err) { return ItsIso14827SubscriptionReq_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionReq_purge(ItsIso14827SubscriptionReq *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionReq_del(ItsIso14827SubscriptionReq *p);
static __inline__ void ItsIso14827SubscriptionReq_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionReq **p = (ItsIso14827SubscriptionReq **)ptr;
	if (p) { ItsIso14827SubscriptionReq_del(*p); *p = NULL; }
}
// ItsIso14827SubscriptionReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionOperPresent
typedef enum ItsIso14827SubscriptionOperPresent
{
	ItsIso14827SubscriptionOperPresent_create,
	ItsIso14827SubscriptionOperPresent_update,
	ItsIso14827SubscriptionOperPresent_terminate,
	ItsIso14827SubscriptionOperPresent_max
} ItsIso14827SubscriptionOperPresent;

DZ1_CPPLINK str_t ItsIso14827SubscriptionOperPresentStrA(ItsIso14827SubscriptionOperPresent v);
DZ1_CPPLINK ItsIso14827SubscriptionOperPresent ItsIso14827SubscriptionOperPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827SubscriptionOperPresentStrW(ItsIso14827SubscriptionOperPresent v);
DZ1_CPPLINK ItsIso14827SubscriptionOperPresent ItsIso14827SubscriptionOperPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827SubscriptionOperPresentStr ItsIso14827SubscriptionOperPresentStrW
#define ItsIso14827SubscriptionOperPresentFromStr ItsIso14827SubscriptionOperPresentFromStrW
#else // UNICODE
#define ItsIso14827SubscriptionOperPresentStr ItsIso14827SubscriptionOperPresentStrA
#define ItsIso14827SubscriptionOperPresentFromStr ItsIso14827SubscriptionOperPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827SubscriptionOperPresentStr ItsIso14827SubscriptionOperPresentStrA
#define ItsIso14827SubscriptionOperPresentFromStr ItsIso14827SubscriptionOperPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionOperPresent *ItsIso14827SubscriptionOperPresent_new(ItsIso14827SubscriptionOperPresent *src, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionOperPresent *ItsIso14827SubscriptionOperPresent_gen(Dz1Error *err) { ItsIso14827SubscriptionOperPresent v = ItsIso14827SubscriptionOperPresent_max; return ItsIso14827SubscriptionOperPresent_new(&v, err); }
static __inline__ void ItsIso14827SubscriptionOperPresent_del(ItsIso14827SubscriptionOperPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827SubscriptionOperPresent_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionOperPresent **p = (ItsIso14827SubscriptionOperPresent **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionOperPresent_del(*p); *p = NULL; }
}
// ItsIso14827SubscriptionOperPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionOper
typedef struct ItsIso14827SubscriptionOper
{
	ItsIso14827SubscriptionOperPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ItsIso14827SubscriptionReq		*create;
		ItsIso14827SubscriptionReq		*update;
		u32_t							 terminate;
	} x;
} ItsIso14827SubscriptionOper;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionOper *ItsIso14827SubscriptionOper_new(ItsIso14827SubscriptionOperPresent present, void *ptr, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionOper *ItsIso14827SubscriptionOper_gen(Dz1Error *err) { return ItsIso14827SubscriptionOper_new(ItsIso14827SubscriptionOperPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionOper_purge(ItsIso14827SubscriptionOper *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionOper_del(ItsIso14827SubscriptionOper *p);
static __inline__ void ItsIso14827SubscriptionOper_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionOper **p = (ItsIso14827SubscriptionOper **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionOper_del(*p); *p = NULL; }
}
// ItsIso14827SubscriptionOper
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerSubscriptionFsmArg
struct ItsIso14827ServerDomain;
struct ItsIso14827ServerDomainClientEntry;
struct ItsIso14827SubscriptionEntry;

typedef struct ItsIso14827ServerSubscriptionFsmArg
{
	struct ItsIso14827ServerDomain					*server;
	struct ItsIso14827ServerDomainClientEntry		*client;
	Dz1Asn1UTF8Str									*domainName;
	struct ItsIso14827SubscriptionEntry				*subscription;
	ItsIso14827SubscriptionOper						*oper;
	ItsIso14827SubscriptionOper						*retried;
} ItsIso14827ServerSubscriptionFsmArg;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerSubscriptionFsmArg *ItsIso14827ServerSubscriptionFsmArg_new(struct ItsIso14827ServerDomain *server_ref, 
																									 struct ItsIso14827ServerDomainClientEntry *client_ref, 
																									 Dz1Asn1UTF8Str *domainName, 
																									 struct ItsIso14827SubscriptionEntry *subscription_ref, Dz1Error *err);
static __inline__ ItsIso14827ServerSubscriptionFsmArg *ItsIso14827ServerSubscriptionFsmArg_gen(Dz1Error *err) { return ItsIso14827ServerSubscriptionFsmArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerSubscriptionFsmArg_purge(ItsIso14827ServerSubscriptionFsmArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerSubscriptionFsmArg_del(ItsIso14827ServerSubscriptionFsmArg *p);
static __inline__ void ItsIso14827ServerSubscriptionFsmArg_delAndSetNull(void *ptr)
{
	ItsIso14827ServerSubscriptionFsmArg **p = (ItsIso14827ServerSubscriptionFsmArg **)ptr;
	if (p) { ItsIso14827ServerSubscriptionFsmArg_del(*p); *p = NULL; }
}
// ItsIso14827ServerSubscriptionFsmArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionDate
typedef struct ItsIso14827SubscriptionDate
{
	u32_t		year;
	u32_t		mon;
	u32_t		day;
} ItsIso14827SubscriptionDate;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionDate *ItsIso14827SubscriptionDate_new(u32_t year, 
																					 u32_t mon, 
																					 u32_t day, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionDate *ItsIso14827SubscriptionDate_gen(Dz1Error *err) { return ItsIso14827SubscriptionDate_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionDate_purge(ItsIso14827SubscriptionDate *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionDate_del(ItsIso14827SubscriptionDate *p);
static __inline__ void ItsIso14827SubscriptionDate_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionDate **p = (ItsIso14827SubscriptionDate **)ptr;
	if (p) { ItsIso14827SubscriptionDate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionDate_dump(ItsIso14827SubscriptionDate *p, int tab);
// ItsIso14827SubscriptionDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionEntry
typedef struct ItsIso14827SubscriptionEntry
{
	u32_t							 serial;
	Dz1Fsm2							*fsm;
	u32_t							 pktNbr;
	Iso14827SubscriptionData		*data;
	u32_t							 pubSerial;
	bool_t							 isActive;
	bool_t							 isPaused;
	time_t							 start;
	time_t							 end;
	ItsIso14827SubscriptionDate		*daily;
} ItsIso14827SubscriptionEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionEntry *ItsIso14827SubscriptionEntry_new(u32_t serial, 
																					   Dz1Fsm2 *fsm, 
																					   u32_t pktNbr, 
																					   Iso14827SubscriptionData *data, Dz1Error *err);
static __inline__ ItsIso14827SubscriptionEntry *ItsIso14827SubscriptionEntry_gen(Dz1Error *err) { return ItsIso14827SubscriptionEntry_new(0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionEntry_purge(ItsIso14827SubscriptionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionEntry_del(ItsIso14827SubscriptionEntry *p);
static __inline__ void ItsIso14827SubscriptionEntry_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionEntry **p = (ItsIso14827SubscriptionEntry **)ptr;
	if (p) { ItsIso14827SubscriptionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionEntry_dump(ItsIso14827SubscriptionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827SubscriptionEntry_cmp(ItsIso14827SubscriptionEntry *a, ItsIso14827SubscriptionEntry *b); 
// ItsIso14827SubscriptionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionList
typedef struct ItsIso14827SubscriptionList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827SubscriptionList *p);
	Dz1Error (*travel)(struct ItsIso14827SubscriptionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscriptionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827SubscriptionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscriptionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827SubscriptionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscriptionEntry *entry), void *ptr);
	ItsIso14827SubscriptionEntry **(*get_array)(struct ItsIso14827SubscriptionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *data);
	bool_t (*remove)(struct ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key);
	ItsIso14827SubscriptionEntry *(*extract)(struct ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key);
	ItsIso14827SubscriptionEntry *(*find)(struct ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key);
	int (*cmp)(ItsIso14827SubscriptionEntry *a, ItsIso14827SubscriptionEntry *b);
} ItsIso14827SubscriptionList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscriptionList *ItsIso14827SubscriptionList_new(Dz1Error *err);
static __inline__ ItsIso14827SubscriptionList *ItsIso14827SubscriptionList_gen(Dz1Error *err) { return ItsIso14827SubscriptionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionList_purge(ItsIso14827SubscriptionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionList_del(ItsIso14827SubscriptionList *p);
static __inline__ void ItsIso14827SubscriptionList_delAndSetNull(void *ptr)
{
	ItsIso14827SubscriptionList **p = (ItsIso14827SubscriptionList **)ptr;
	if (p != NULL) { ItsIso14827SubscriptionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscriptionList_dump(ItsIso14827SubscriptionList *p, int tab);

// ItsIso14827SubscriptionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientState
typedef enum ItsIso14827ServerDomainClientState
{
	ItsIso14827ServerDomainClientState_waitLoginResult,
	ItsIso14827ServerDomainClientState_established,
	ItsIso14827ServerDomainClientState_terminated,
	ItsIso14827ServerDomainClientState_max
} ItsIso14827ServerDomainClientState;

DZ1_CPPLINK str_t ItsIso14827ServerDomainClientStateStrA(ItsIso14827ServerDomainClientState v);
DZ1_CPPLINK ItsIso14827ServerDomainClientState ItsIso14827ServerDomainClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827ServerDomainClientStateStrW(ItsIso14827ServerDomainClientState v);
DZ1_CPPLINK ItsIso14827ServerDomainClientState ItsIso14827ServerDomainClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827ServerDomainClientStateStr ItsIso14827ServerDomainClientStateStrW
#define ItsIso14827ServerDomainClientStateFromStr ItsIso14827ServerDomainClientStateFromStrW
#else // UNICODE
#define ItsIso14827ServerDomainClientStateStr ItsIso14827ServerDomainClientStateStrA
#define ItsIso14827ServerDomainClientStateFromStr ItsIso14827ServerDomainClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827ServerDomainClientStateStr ItsIso14827ServerDomainClientStateStrA
#define ItsIso14827ServerDomainClientStateFromStr ItsIso14827ServerDomainClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainClientState *ItsIso14827ServerDomainClientState_new(ItsIso14827ServerDomainClientState *src, Dz1Error *err);
static __inline__ ItsIso14827ServerDomainClientState *ItsIso14827ServerDomainClientState_gen(Dz1Error *err) { ItsIso14827ServerDomainClientState v = ItsIso14827ServerDomainClientState_max; return ItsIso14827ServerDomainClientState_new(&v, err); }
static __inline__ void ItsIso14827ServerDomainClientState_del(ItsIso14827ServerDomainClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827ServerDomainClientState_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainClientState **p = (ItsIso14827ServerDomainClientState **)ptr;
	if (p != NULL) { ItsIso14827ServerDomainClientState_del(*p); *p = NULL; }
}
// ItsIso14827ServerDomainClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientEntry
typedef struct ItsIso14827ServerDomainClientEntry
{
	Dz1Asn1UTF8Str									*peer;
	Dz1Asn1OctetStr									*user;
	ItsIso14827SessionKey							*key;
	ItsIso14827SubscriptionList						*subscriptions;
	ItsIso14827DomainTxFifo							*txFifo;
	u32_t											 heartBeadPeriod;
	u32_t											 responseWaitTime;
	ItsIso14827ServerDomainClientState				 state;
	u32_t											 loginPktNbr;
	u32_t											*loginRetriedPktNbr;
	ItsIso14827ServerDomainCallback					*cb;
	ItsIso14827ServerDomainViolatedPublication		*violatedPub;
} ItsIso14827ServerDomainClientEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomainClientEntry_new(Dz1Asn1UTF8Str *peer, 
																								   Dz1Asn1OctetStr *user, 
																								   ItsIso14827SessionKey *key, 
																								   ItsIso14827DomainTxFifo *txFifo, 
																								   u32_t heartBeadPeriod, 
																								   u32_t responseWaitTime, 
																								   u32_t loginPktNbr, 
																								   ItsIso14827ServerDomainCallback *cb_ref, Dz1Error *err);
static __inline__ ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomainClientEntry_gen(Dz1Error *err) { return ItsIso14827ServerDomainClientEntry_new(NULL, NULL, NULL, NULL, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientEntry_purge(ItsIso14827ServerDomainClientEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientEntry_del(ItsIso14827ServerDomainClientEntry *p);
static __inline__ void ItsIso14827ServerDomainClientEntry_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainClientEntry **p = (ItsIso14827ServerDomainClientEntry **)ptr;
	if (p) { ItsIso14827ServerDomainClientEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientEntry_dump(ItsIso14827ServerDomainClientEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ServerDomainClientEntry_cmp(ItsIso14827ServerDomainClientEntry *a, ItsIso14827ServerDomainClientEntry *b); 
// ItsIso14827ServerDomainClientEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientList
typedef struct ItsIso14827ServerDomainClientList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827ServerDomainClientList *p);
	Dz1Error (*travel)(struct ItsIso14827ServerDomainClientList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainClientEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827ServerDomainClientList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainClientEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827ServerDomainClientList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainClientEntry *entry), void *ptr);
	ItsIso14827ServerDomainClientEntry **(*get_array)(struct ItsIso14827ServerDomainClientList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *data);
	bool_t (*remove)(struct ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key);
	ItsIso14827ServerDomainClientEntry *(*extract)(struct ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key);
	ItsIso14827ServerDomainClientEntry *(*find)(struct ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key);
	int (*cmp)(ItsIso14827ServerDomainClientEntry *a, ItsIso14827ServerDomainClientEntry *b);
} ItsIso14827ServerDomainClientList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainClientList *ItsIso14827ServerDomainClientList_new(Dz1Error *err);
static __inline__ ItsIso14827ServerDomainClientList *ItsIso14827ServerDomainClientList_gen(Dz1Error *err) { return ItsIso14827ServerDomainClientList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientList_purge(ItsIso14827ServerDomainClientList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientList_del(ItsIso14827ServerDomainClientList *p);
static __inline__ void ItsIso14827ServerDomainClientList_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainClientList **p = (ItsIso14827ServerDomainClientList **)ptr;
	if (p != NULL) { ItsIso14827ServerDomainClientList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainClientList_dump(ItsIso14827ServerDomainClientList *p, int tab);

// ItsIso14827ServerDomainClientList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainSessionEntry
typedef struct ItsIso14827ServerDomainSessionEntry
{
	Dz1Asn1UTF8Str									*peer;
	Dz1Asn1OctetStr									*user;
	ItsIso14827SessionKey							*key;
	ItsIso14827SubscriptionList						*subscriptions;
	ItsIso14827DomainTxFifo							*txFifo;
	u32_t											 heartBeadPeriod;
	u32_t											 responseWaitTime;
	ItsIso14827ServerDomainClientState				 state;
	u32_t											 loginPktNbr;
	u32_t											*loginRetriedPktNbr;
	ItsIso14827ServerDomainCallback					*cb;
	ItsIso14827ServerDomainViolatedPublication		*violatedPub;
} ItsIso14827ServerDomainSessionEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainSessionEntry *ItsIso14827ServerDomainSessionEntry_new(Dz1Asn1UTF8Str *peer, 
																									 Dz1Asn1OctetStr *user, 
																									 ItsIso14827SessionKey *key, 
																									 ItsIso14827DomainTxFifo *txFifo, 
																									 u32_t heartBeadPeriod, 
																									 u32_t responseWaitTime, 
																									 u32_t loginPktNbr, 
																									 ItsIso14827ServerDomainCallback *cb_ref, Dz1Error *err);
static __inline__ ItsIso14827ServerDomainSessionEntry *ItsIso14827ServerDomainSessionEntry_gen(Dz1Error *err) { return ItsIso14827ServerDomainSessionEntry_new(NULL, NULL, NULL, NULL, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionEntry_purge(ItsIso14827ServerDomainSessionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionEntry_del(ItsIso14827ServerDomainSessionEntry *p);
static __inline__ void ItsIso14827ServerDomainSessionEntry_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainSessionEntry **p = (ItsIso14827ServerDomainSessionEntry **)ptr;
	if (p) { ItsIso14827ServerDomainSessionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionEntry_dump(ItsIso14827ServerDomainSessionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ServerDomainSessionEntry_cmp(ItsIso14827ServerDomainSessionEntry *a, ItsIso14827ServerDomainSessionEntry *b); 
// ItsIso14827ServerDomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainSessionList
typedef struct ItsIso14827ServerDomainSessionList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827ServerDomainSessionList *p);
	Dz1Error (*travel)(struct ItsIso14827ServerDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827ServerDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827ServerDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainSessionEntry *entry), void *ptr);
	ItsIso14827ServerDomainSessionEntry **(*get_array)(struct ItsIso14827ServerDomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *data);
	bool_t (*remove)(struct ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key);
	ItsIso14827ServerDomainSessionEntry *(*extract)(struct ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key);
	ItsIso14827ServerDomainSessionEntry *(*find)(struct ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key);
	int (*cmp)(ItsIso14827ServerDomainSessionEntry *a, ItsIso14827ServerDomainSessionEntry *b);
} ItsIso14827ServerDomainSessionList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainSessionList *ItsIso14827ServerDomainSessionList_new(Dz1Error *err);
static __inline__ ItsIso14827ServerDomainSessionList *ItsIso14827ServerDomainSessionList_gen(Dz1Error *err) { return ItsIso14827ServerDomainSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainSessionList *ItsIso14827ServerDomainSessionList_clone(ItsIso14827ServerDomainSessionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionList_purge(ItsIso14827ServerDomainSessionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionList_del(ItsIso14827ServerDomainSessionList *p);
static __inline__ void ItsIso14827ServerDomainSessionList_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainSessionList **p = (ItsIso14827ServerDomainSessionList **)ptr;
	if (p != NULL) { ItsIso14827ServerDomainSessionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainSessionList_dump(ItsIso14827ServerDomainSessionList *p, int tab);

// ItsIso14827ServerDomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiatorWaitEntry
typedef struct ItsIso14827DomainInitiatorWaitEntry
{
	Dz1Asn1UTF8Str		*peer;
} ItsIso14827DomainInitiatorWaitEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainInitiatorWaitEntry *ItsIso14827DomainInitiatorWaitEntry_new(Dz1Asn1UTF8Str *peer, Dz1Error *err);
static __inline__ ItsIso14827DomainInitiatorWaitEntry *ItsIso14827DomainInitiatorWaitEntry_gen(Dz1Error *err) { return ItsIso14827DomainInitiatorWaitEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitEntry_purge(ItsIso14827DomainInitiatorWaitEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitEntry_del(ItsIso14827DomainInitiatorWaitEntry *p);
static __inline__ void ItsIso14827DomainInitiatorWaitEntry_delAndSetNull(void *ptr)
{
	ItsIso14827DomainInitiatorWaitEntry **p = (ItsIso14827DomainInitiatorWaitEntry **)ptr;
	if (p) { ItsIso14827DomainInitiatorWaitEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitEntry_dump(ItsIso14827DomainInitiatorWaitEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainInitiatorWaitEntry_cmp(ItsIso14827DomainInitiatorWaitEntry *a, ItsIso14827DomainInitiatorWaitEntry *b); 
// ItsIso14827DomainInitiatorWaitEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiatorWaitList
typedef struct ItsIso14827DomainInitiatorWaitList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827DomainInitiatorWaitList *p);
	Dz1Error (*travel)(struct ItsIso14827DomainInitiatorWaitList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainInitiatorWaitEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827DomainInitiatorWaitList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainInitiatorWaitEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827DomainInitiatorWaitList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainInitiatorWaitEntry *entry), void *ptr);
	ItsIso14827DomainInitiatorWaitEntry **(*get_array)(struct ItsIso14827DomainInitiatorWaitList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *data);
	bool_t (*remove)(struct ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key);
	ItsIso14827DomainInitiatorWaitEntry *(*extract)(struct ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key);
	ItsIso14827DomainInitiatorWaitEntry *(*find)(struct ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key);
	int (*cmp)(ItsIso14827DomainInitiatorWaitEntry *a, ItsIso14827DomainInitiatorWaitEntry *b);
} ItsIso14827DomainInitiatorWaitList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainInitiatorWaitList *ItsIso14827DomainInitiatorWaitList_new(Dz1Error *err);
static __inline__ ItsIso14827DomainInitiatorWaitList *ItsIso14827DomainInitiatorWaitList_gen(Dz1Error *err) { return ItsIso14827DomainInitiatorWaitList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitList_purge(ItsIso14827DomainInitiatorWaitList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitList_del(ItsIso14827DomainInitiatorWaitList *p);
static __inline__ void ItsIso14827DomainInitiatorWaitList_delAndSetNull(void *ptr)
{
	ItsIso14827DomainInitiatorWaitList **p = (ItsIso14827DomainInitiatorWaitList **)ptr;
	if (p != NULL) { ItsIso14827DomainInitiatorWaitList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiatorWaitList_dump(ItsIso14827DomainInitiatorWaitList *p, int tab);

// ItsIso14827DomainInitiatorWaitList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomain
typedef struct ItsIso14827ServerDomain
{
	Dz1Asn1UTF8Str							*name;
	u32_t									 maxClients;
	ItsIso14827CodecOIDMapList				*codecOidMap;
	ItsIso14827ServerDomainClientList		*clients;
	ItsIso14827ServerDomainSessionList		*sessions;
	ItsIso14827DomainInitiatorWaitList		*initWaits;
	ItsIso14827ServerDomainCallback			*callback;
	u32_t									 hdr_opt_flag;
} ItsIso14827ServerDomain;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomain *ItsIso14827ServerDomain_new(Dz1Asn1UTF8Str *name, 
																			 u32_t maxClients, 
																			 ItsIso14827CodecOIDMapList *codecOidMap, 
																			 ItsIso14827ServerDomainCallback *callback, Dz1Error *err);
static __inline__ ItsIso14827ServerDomain *ItsIso14827ServerDomain_gen(Dz1Error *err) { return ItsIso14827ServerDomain_new(NULL, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomain_purge(ItsIso14827ServerDomain *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomain_del(ItsIso14827ServerDomain *p);
static __inline__ void ItsIso14827ServerDomain_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomain **p = (ItsIso14827ServerDomain **)ptr;
	if (p) { ItsIso14827ServerDomain_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomain_dump(ItsIso14827ServerDomain *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ServerDomain_cmp(ItsIso14827ServerDomain *a, ItsIso14827ServerDomain *b); 
// ItsIso14827ServerDomain
////////////////////////////////////////////////////////////////////////////////

#endif
