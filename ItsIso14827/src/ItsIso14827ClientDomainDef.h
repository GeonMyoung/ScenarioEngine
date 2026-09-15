#ifndef _DZ1_TDC_ITS_ISO14827_CLIENT_DOMAIN_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_CLIENT_DOMAIN_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SessionDef.h"
#include "ItsIso14827DefLocal.h"
#include "ItsIso14827Domain_txFIFO.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscribeEntry
typedef struct ItsIso14827SubscribeEntry
{
	u32_t						 serial;
	Iso14827SubscriptionData	*data;
	u32_t						*pubSerial;
} ItsIso14827SubscribeEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscribeEntry *ItsIso14827SubscribeEntry_new(u32_t serial, 
																				 Iso14827SubscriptionData *data, Dz1Error *err);
static __inline__ ItsIso14827SubscribeEntry *ItsIso14827SubscribeEntry_gen(Dz1Error *err) { return ItsIso14827SubscribeEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeEntry_purge(ItsIso14827SubscribeEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeEntry_del(ItsIso14827SubscribeEntry *p);
static __inline__ void ItsIso14827SubscribeEntry_delAndSetNull(void *ptr)
{
	ItsIso14827SubscribeEntry **p = (ItsIso14827SubscribeEntry **)ptr;
	if (p) { ItsIso14827SubscribeEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeEntry_dump(ItsIso14827SubscribeEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827SubscribeEntry_cmp(ItsIso14827SubscribeEntry *a, ItsIso14827SubscribeEntry *b); 
// ItsIso14827SubscribeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscribeList
typedef struct ItsIso14827SubscribeList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827SubscribeList *p);
	Dz1Error (*travel)(struct ItsIso14827SubscribeList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscribeEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827SubscribeList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscribeEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827SubscribeList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscribeEntry *entry), void *ptr);
	ItsIso14827SubscribeEntry **(*get_array)(struct ItsIso14827SubscribeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *data);
	bool_t (*remove)(struct ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key);
	ItsIso14827SubscribeEntry *(*extract)(struct ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key);
	ItsIso14827SubscribeEntry *(*find)(struct ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key);
	int (*cmp)(ItsIso14827SubscribeEntry *a, ItsIso14827SubscribeEntry *b);
} ItsIso14827SubscribeList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SubscribeList *ItsIso14827SubscribeList_new(Dz1Error *err);
static __inline__ ItsIso14827SubscribeList *ItsIso14827SubscribeList_gen(Dz1Error *err) { return ItsIso14827SubscribeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeList_purge(ItsIso14827SubscribeList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeList_del(ItsIso14827SubscribeList *p);
static __inline__ void ItsIso14827SubscribeList_delAndSetNull(void *ptr)
{
	ItsIso14827SubscribeList **p = (ItsIso14827SubscribeList **)ptr;
	if (p != NULL) { ItsIso14827SubscribeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SubscribeList_dump(ItsIso14827SubscribeList *p, int tab);

// ItsIso14827SubscribeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionState
typedef enum ItsIso14827ClientDomainSessionState
{
	ItsIso14827ClientDomainSessionState_pending,
	ItsIso14827ClientDomainSessionState_established,
	ItsIso14827ClientDomainSessionState_max
} ItsIso14827ClientDomainSessionState;

DZ1_CPPLINK str_t ItsIso14827ClientDomainSessionStateStrA(ItsIso14827ClientDomainSessionState v);
DZ1_CPPLINK ItsIso14827ClientDomainSessionState ItsIso14827ClientDomainSessionStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827ClientDomainSessionStateStrW(ItsIso14827ClientDomainSessionState v);
DZ1_CPPLINK ItsIso14827ClientDomainSessionState ItsIso14827ClientDomainSessionStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827ClientDomainSessionStateStr ItsIso14827ClientDomainSessionStateStrW
#define ItsIso14827ClientDomainSessionStateFromStr ItsIso14827ClientDomainSessionStateFromStrW
#else // UNICODE
#define ItsIso14827ClientDomainSessionStateStr ItsIso14827ClientDomainSessionStateStrA
#define ItsIso14827ClientDomainSessionStateFromStr ItsIso14827ClientDomainSessionStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827ClientDomainSessionStateStr ItsIso14827ClientDomainSessionStateStrA
#define ItsIso14827ClientDomainSessionStateFromStr ItsIso14827ClientDomainSessionStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainSessionState *ItsIso14827ClientDomainSessionState_new(ItsIso14827ClientDomainSessionState *src, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainSessionState *ItsIso14827ClientDomainSessionState_gen(Dz1Error *err) { ItsIso14827ClientDomainSessionState v = ItsIso14827ClientDomainSessionState_max; return ItsIso14827ClientDomainSessionState_new(&v, err); }
static __inline__ void ItsIso14827ClientDomainSessionState_del(ItsIso14827ClientDomainSessionState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827ClientDomainSessionState_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainSessionState **p = (ItsIso14827ClientDomainSessionState **)ptr;
	if (p != NULL) { ItsIso14827ClientDomainSessionState_del(*p); *p = NULL; }
}
// ItsIso14827ClientDomainSessionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainWaitState
typedef enum ItsIso14827ClientDomainWaitState
{
	ItsIso14827ClientDomainWaitState_none,
	ItsIso14827ClientDomainWaitState_loginResultWait,
	ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait,
	ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait,
	ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait,
	ItsIso14827ClientDomainWaitState_logoutResultWait,
	ItsIso14827ClientDomainWaitState_max
} ItsIso14827ClientDomainWaitState;

DZ1_CPPLINK str_t ItsIso14827ClientDomainWaitStateStrA(ItsIso14827ClientDomainWaitState v);
DZ1_CPPLINK ItsIso14827ClientDomainWaitState ItsIso14827ClientDomainWaitStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827ClientDomainWaitStateStrW(ItsIso14827ClientDomainWaitState v);
DZ1_CPPLINK ItsIso14827ClientDomainWaitState ItsIso14827ClientDomainWaitStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827ClientDomainWaitStateStr ItsIso14827ClientDomainWaitStateStrW
#define ItsIso14827ClientDomainWaitStateFromStr ItsIso14827ClientDomainWaitStateFromStrW
#else // UNICODE
#define ItsIso14827ClientDomainWaitStateStr ItsIso14827ClientDomainWaitStateStrA
#define ItsIso14827ClientDomainWaitStateFromStr ItsIso14827ClientDomainWaitStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827ClientDomainWaitStateStr ItsIso14827ClientDomainWaitStateStrA
#define ItsIso14827ClientDomainWaitStateFromStr ItsIso14827ClientDomainWaitStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainWaitState *ItsIso14827ClientDomainWaitState_new(ItsIso14827ClientDomainWaitState *src, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainWaitState *ItsIso14827ClientDomainWaitState_gen(Dz1Error *err) { ItsIso14827ClientDomainWaitState v = ItsIso14827ClientDomainWaitState_max; return ItsIso14827ClientDomainWaitState_new(&v, err); }
static __inline__ void ItsIso14827ClientDomainWaitState_del(ItsIso14827ClientDomainWaitState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827ClientDomainWaitState_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainWaitState **p = (ItsIso14827ClientDomainWaitState **)ptr;
	if (p != NULL) { ItsIso14827ClientDomainWaitState_del(*p); *p = NULL; }
}
// ItsIso14827ClientDomainWaitState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainServerEntry
typedef struct ItsIso14827ClientDomainServerEntry
{
	Dz1Asn1UTF8Str									*peer;
	Dz1Asn1OctetStr									*user;
	ItsIso14827SessionKey							*key;
	ItsIso14827ClientDomainSessionState				 state;
	u32_t											 subscribeAlloc;
	ItsIso14827SubscribeList						*subscribes;
	ItsIso14827ClientDomainWaitState				 userWaitState;
	void											*userWait;
	ItsIso14827DomainTxFifo							*txFifo;
	u32_t											 heartBeadPeriod;
	u32_t											 responseWaitTime;
	ItsIso14827ClientDomainCallback					*cb;
	ItsIso14827ClientDomainViolatedSubscription		*violatedSub;
	u32_t											 ctrl_flags;
} ItsIso14827ClientDomainServerEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomainServerEntry_new(Dz1Asn1UTF8Str *peer, 
																								   Dz1Asn1OctetStr *user, 
																								   ItsIso14827SessionKey *key, 
																								   u32_t subscribeAlloc, 
																								   ItsIso14827DomainTxFifo *txFifo, 
																								   u32_t heartBeadPeriod, 
																								   u32_t responseWaitTime, 
																								   ItsIso14827ClientDomainCallback *cb_ref, 
																								   ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomainServerEntry_gen(Dz1Error *err) { return ItsIso14827ClientDomainServerEntry_new(NULL, NULL, NULL, 0, NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerEntry_purge(ItsIso14827ClientDomainServerEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerEntry_del(ItsIso14827ClientDomainServerEntry *p);
static __inline__ void ItsIso14827ClientDomainServerEntry_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainServerEntry **p = (ItsIso14827ClientDomainServerEntry **)ptr;
	if (p) { ItsIso14827ClientDomainServerEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerEntry_dump(ItsIso14827ClientDomainServerEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ClientDomainServerEntry_cmp(ItsIso14827ClientDomainServerEntry *a, ItsIso14827ClientDomainServerEntry *b); 
// ItsIso14827ClientDomainServerEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainServerList
typedef struct ItsIso14827ClientDomainServerList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827ClientDomainServerList *p);
	Dz1Error (*travel)(struct ItsIso14827ClientDomainServerList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainServerEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827ClientDomainServerList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainServerEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827ClientDomainServerList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainServerEntry *entry), void *ptr);
	ItsIso14827ClientDomainServerEntry **(*get_array)(struct ItsIso14827ClientDomainServerList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *data);
	bool_t (*remove)(struct ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key);
	ItsIso14827ClientDomainServerEntry *(*extract)(struct ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key);
	ItsIso14827ClientDomainServerEntry *(*find)(struct ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key);
	int (*cmp)(ItsIso14827ClientDomainServerEntry *a, ItsIso14827ClientDomainServerEntry *b);
} ItsIso14827ClientDomainServerList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainServerList *ItsIso14827ClientDomainServerList_new(Dz1Error *err);
static __inline__ ItsIso14827ClientDomainServerList *ItsIso14827ClientDomainServerList_gen(Dz1Error *err) { return ItsIso14827ClientDomainServerList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerList_purge(ItsIso14827ClientDomainServerList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerList_del(ItsIso14827ClientDomainServerList *p);
static __inline__ void ItsIso14827ClientDomainServerList_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainServerList **p = (ItsIso14827ClientDomainServerList **)ptr;
	if (p != NULL) { ItsIso14827ClientDomainServerList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainServerList_dump(ItsIso14827ClientDomainServerList *p, int tab);

// ItsIso14827ClientDomainServerList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionEntry
typedef struct ItsIso14827ClientDomainSessionEntry
{
	Dz1Asn1UTF8Str							*peer;
	Dz1Asn1OctetStr							*user;
	ItsIso14827SessionKey					*key;
	ItsIso14827ClientDomainSessionState		 state;
	u32_t									 subscribeAlloc;
	ItsIso14827SubscribeList				*subscribes;
	ItsIso14827ClientDomainWaitState		 userWaitState;
	void									*userWait;
	ItsIso14827DomainTxFifo					*txFifo;
	u32_t									 heartBeadPeriod;
	u32_t									 responseWaitTime;
	ItsIso14827ClientDomainCallback			*cb;
} ItsIso14827ClientDomainSessionEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainSessionEntry *ItsIso14827ClientDomainSessionEntry_new(Dz1Asn1UTF8Str *peer, 
																									 Dz1Asn1OctetStr *user, 
																									 ItsIso14827SessionKey *key, 
																									 u32_t subscribeAlloc, 
																									 ItsIso14827DomainTxFifo *txFifo, 
																									 u32_t heartBeadPeriod, 
																									 u32_t responseWaitTime, 
																									 ItsIso14827ClientDomainCallback *cb_ref, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainSessionEntry *ItsIso14827ClientDomainSessionEntry_gen(Dz1Error *err) { return ItsIso14827ClientDomainSessionEntry_new(NULL, NULL, NULL, 0, NULL, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionEntry_purge(ItsIso14827ClientDomainSessionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionEntry_del(ItsIso14827ClientDomainSessionEntry *p);
static __inline__ void ItsIso14827ClientDomainSessionEntry_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainSessionEntry **p = (ItsIso14827ClientDomainSessionEntry **)ptr;
	if (p) { ItsIso14827ClientDomainSessionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionEntry_dump(ItsIso14827ClientDomainSessionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ClientDomainSessionEntry_cmp(ItsIso14827ClientDomainSessionEntry *a, ItsIso14827ClientDomainSessionEntry *b); 
// ItsIso14827ClientDomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionList
typedef struct ItsIso14827ClientDomainSessionList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827ClientDomainSessionList *p);
	Dz1Error (*travel)(struct ItsIso14827ClientDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827ClientDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827ClientDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainSessionEntry *entry), void *ptr);
	ItsIso14827ClientDomainSessionEntry **(*get_array)(struct ItsIso14827ClientDomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *data);
	bool_t (*remove)(struct ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key);
	ItsIso14827ClientDomainSessionEntry *(*extract)(struct ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key);
	ItsIso14827ClientDomainSessionEntry *(*find)(struct ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key);
	int (*cmp)(ItsIso14827ClientDomainSessionEntry *a, ItsIso14827ClientDomainSessionEntry *b);
} ItsIso14827ClientDomainSessionList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainSessionList *ItsIso14827ClientDomainSessionList_new(Dz1Error *err);
static __inline__ ItsIso14827ClientDomainSessionList *ItsIso14827ClientDomainSessionList_gen(Dz1Error *err) { return ItsIso14827ClientDomainSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainSessionList *ItsIso14827ClientDomainSessionList_clone(ItsIso14827ClientDomainSessionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionList_purge(ItsIso14827ClientDomainSessionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionList_del(ItsIso14827ClientDomainSessionList *p);
static __inline__ void ItsIso14827ClientDomainSessionList_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainSessionList **p = (ItsIso14827ClientDomainSessionList **)ptr;
	if (p != NULL) { ItsIso14827ClientDomainSessionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainSessionList_dump(ItsIso14827ClientDomainSessionList *p, int tab);

// ItsIso14827ClientDomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomain
typedef struct ItsIso14827ClientDomain
{
	Dz1Asn1UTF8Str							*name;
	ItsIso14827ClientDomainServerList		*servers;
	ItsIso14827ClientDomainSessionList		*sessions;
	ItsIso14827ClientDomainCallback			*callback;
	u32_t									 hdr_opt_flag;
} ItsIso14827ClientDomain;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomain *ItsIso14827ClientDomain_new(Dz1Asn1UTF8Str *name, 
																			 ItsIso14827ClientDomainCallback *callback, Dz1Error *err);
static __inline__ ItsIso14827ClientDomain *ItsIso14827ClientDomain_gen(Dz1Error *err) { return ItsIso14827ClientDomain_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomain_purge(ItsIso14827ClientDomain *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomain_del(ItsIso14827ClientDomain *p);
static __inline__ void ItsIso14827ClientDomain_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomain **p = (ItsIso14827ClientDomain **)ptr;
	if (p) { ItsIso14827ClientDomain_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomain_dump(ItsIso14827ClientDomain *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827ClientDomain_cmp(ItsIso14827ClientDomain *a, ItsIso14827ClientDomain *b); 
// ItsIso14827ClientDomain
////////////////////////////////////////////////////////////////////////////////

#endif
