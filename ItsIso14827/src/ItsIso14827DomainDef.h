#ifndef _DZ1_TDC_ITS_ISO14827_DOMAIN_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_DOMAIN_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827ServerDomainDef.h"
#include "ItsIso14827ClientDomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainKey
typedef struct ItsIso14827DomainKey
{
	ItsIso14827DomainType		 type;
	Dz1Asn1UTF8Str				*name;
} ItsIso14827DomainKey;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainKey *ItsIso14827DomainKey_new(ItsIso14827DomainType type, 
																	   Dz1Asn1UTF8Str *name, Dz1Error *err);
static __inline__ ItsIso14827DomainKey *ItsIso14827DomainKey_gen(Dz1Error *err) { return ItsIso14827DomainKey_new(ItsIso14827DomainType_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827DomainKey_copy(ItsIso14827DomainKey *dst, ItsIso14827DomainKey *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainKey *ItsIso14827DomainKey_clone(ItsIso14827DomainKey *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainKey_purge(ItsIso14827DomainKey *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainKey_del(ItsIso14827DomainKey *p);
static __inline__ void ItsIso14827DomainKey_delAndSetNull(void *ptr)
{
	ItsIso14827DomainKey **p = (ItsIso14827DomainKey **)ptr;
	if (p) { ItsIso14827DomainKey_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainKey_dump(ItsIso14827DomainKey *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainKey_cmp(ItsIso14827DomainKey *a, ItsIso14827DomainKey *b); 
// ItsIso14827DomainKey
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPresent
typedef enum ItsIso14827DomainPresent
{
	ItsIso14827DomainPresent_server,
	ItsIso14827DomainPresent_client,
	ItsIso14827DomainPresent_max
} ItsIso14827DomainPresent;

DZ1_CPPLINK str_t ItsIso14827DomainPresentStrA(ItsIso14827DomainPresent v);
DZ1_CPPLINK ItsIso14827DomainPresent ItsIso14827DomainPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827DomainPresentStrW(ItsIso14827DomainPresent v);
DZ1_CPPLINK ItsIso14827DomainPresent ItsIso14827DomainPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827DomainPresentStr ItsIso14827DomainPresentStrW
#define ItsIso14827DomainPresentFromStr ItsIso14827DomainPresentFromStrW
#else // UNICODE
#define ItsIso14827DomainPresentStr ItsIso14827DomainPresentStrA
#define ItsIso14827DomainPresentFromStr ItsIso14827DomainPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827DomainPresentStr ItsIso14827DomainPresentStrA
#define ItsIso14827DomainPresentFromStr ItsIso14827DomainPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainPresent *ItsIso14827DomainPresent_new(ItsIso14827DomainPresent *src, Dz1Error *err);
static __inline__ ItsIso14827DomainPresent *ItsIso14827DomainPresent_gen(Dz1Error *err) { ItsIso14827DomainPresent v = ItsIso14827DomainPresent_max; return ItsIso14827DomainPresent_new(&v, err); }
static __inline__ void ItsIso14827DomainPresent_del(ItsIso14827DomainPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827DomainPresent_delAndSetNull(void *ptr)
{
	ItsIso14827DomainPresent **p = (ItsIso14827DomainPresent **)ptr;
	if (p != NULL) { ItsIso14827DomainPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPresent_dump(ItsIso14827DomainPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainPresent_cmp(ItsIso14827DomainPresent *a, ItsIso14827DomainPresent *b);
// ItsIso14827DomainPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Domain
typedef struct ItsIso14827Domain
{
	ItsIso14827DomainPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ItsIso14827ServerDomain		*server;
		ItsIso14827ClientDomain		*client;
	} x;
} ItsIso14827Domain;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827Domain *ItsIso14827Domain_new(ItsIso14827DomainPresent present, void *ptr, Dz1Error *err);
static __inline__ ItsIso14827Domain *ItsIso14827Domain_gen(Dz1Error *err) { return ItsIso14827Domain_new(ItsIso14827DomainPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Domain_purge(ItsIso14827Domain *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Domain_del(ItsIso14827Domain *p);
static __inline__ void ItsIso14827Domain_delAndSetNull(void *ptr)
{
	ItsIso14827Domain **p = (ItsIso14827Domain **)ptr;
	if (p != NULL) { ItsIso14827Domain_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Domain_dump(ItsIso14827Domain *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827Domain_cmp(ItsIso14827Domain *a, ItsIso14827Domain *b);
// ItsIso14827Domain
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainList
typedef struct ItsIso14827DomainList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827DomainList *p);
	Dz1Error (*travel)(struct ItsIso14827DomainList *p, Dz1Error (*func)(void *ptr, ItsIso14827Domain *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827DomainList *p, Dz1Error (*func)(void *ptr, ItsIso14827Domain *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827DomainList *p, Dz1Error (*func)(void *ptr, ItsIso14827Domain *entry), void *ptr);
	ItsIso14827Domain **(*get_array)(struct ItsIso14827DomainList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827DomainList *p, ItsIso14827Domain *data);
	bool_t (*remove)(struct ItsIso14827DomainList *p, ItsIso14827Domain *key);
	ItsIso14827Domain *(*extract)(struct ItsIso14827DomainList *p, ItsIso14827Domain *key);
	ItsIso14827Domain *(*find)(struct ItsIso14827DomainList *p, ItsIso14827Domain *key);
	int (*cmp)(ItsIso14827Domain *a, ItsIso14827Domain *b);
} ItsIso14827DomainList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainList *ItsIso14827DomainList_new(Dz1Error *err);
static __inline__ ItsIso14827DomainList *ItsIso14827DomainList_gen(Dz1Error *err) { return ItsIso14827DomainList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainList_purge(ItsIso14827DomainList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainList_del(ItsIso14827DomainList *p);
static __inline__ void ItsIso14827DomainList_delAndSetNull(void *ptr)
{
	ItsIso14827DomainList **p = (ItsIso14827DomainList **)ptr;
	if (p != NULL) { ItsIso14827DomainList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainList_dump(ItsIso14827DomainList *p, int tab);

// ItsIso14827DomainList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSessionEntry
typedef struct ItsIso14827DomainSessionEntry
{
	ItsIso14827SessionKey		*session;
	ItsIso14827DomainKey		*domain;
} ItsIso14827DomainSessionEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainSessionEntry *ItsIso14827DomainSessionEntry_new(ItsIso14827SessionKey *session, 
																						 ItsIso14827DomainKey *domain, Dz1Error *err);
static __inline__ ItsIso14827DomainSessionEntry *ItsIso14827DomainSessionEntry_gen(Dz1Error *err) { return ItsIso14827DomainSessionEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionEntry_purge(ItsIso14827DomainSessionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionEntry_del(ItsIso14827DomainSessionEntry *p);
static __inline__ void ItsIso14827DomainSessionEntry_delAndSetNull(void *ptr)
{
	ItsIso14827DomainSessionEntry **p = (ItsIso14827DomainSessionEntry **)ptr;
	if (p) { ItsIso14827DomainSessionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionEntry_dump(ItsIso14827DomainSessionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainSessionEntry_cmp(ItsIso14827DomainSessionEntry *a, ItsIso14827DomainSessionEntry *b); 
// ItsIso14827DomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSessionList
typedef struct ItsIso14827DomainSessionList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827DomainSessionList *p);
	Dz1Error (*travel)(struct ItsIso14827DomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827DomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainSessionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827DomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainSessionEntry *entry), void *ptr);
	ItsIso14827DomainSessionEntry **(*get_array)(struct ItsIso14827DomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *data);
	bool_t (*remove)(struct ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key);
	ItsIso14827DomainSessionEntry *(*extract)(struct ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key);
	ItsIso14827DomainSessionEntry *(*find)(struct ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key);
	int (*cmp)(ItsIso14827DomainSessionEntry *a, ItsIso14827DomainSessionEntry *b);
} ItsIso14827DomainSessionList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainSessionList *ItsIso14827DomainSessionList_new(Dz1Error *err);
static __inline__ ItsIso14827DomainSessionList *ItsIso14827DomainSessionList_gen(Dz1Error *err) { return ItsIso14827DomainSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionList_purge(ItsIso14827DomainSessionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionList_del(ItsIso14827DomainSessionList *p);
static __inline__ void ItsIso14827DomainSessionList_delAndSetNull(void *ptr)
{
	ItsIso14827DomainSessionList **p = (ItsIso14827DomainSessionList **)ptr;
	if (p != NULL) { ItsIso14827DomainSessionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSessionList_dump(ItsIso14827DomainSessionList *p, int tab);

// ItsIso14827DomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainMgr
typedef struct ItsIso14827DomainMgr
{
	ItsIso14827DomainList			*domains;
	ItsIso14827DomainSessionList	*sessions;
} ItsIso14827DomainMgr;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainMgr *ItsIso14827DomainMgr_new(Dz1Error *err);
static __inline__ ItsIso14827DomainMgr *ItsIso14827DomainMgr_gen(Dz1Error *err) { return ItsIso14827DomainMgr_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainMgr_purge(ItsIso14827DomainMgr *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainMgr_del(ItsIso14827DomainMgr *p);
static __inline__ void ItsIso14827DomainMgr_delAndSetNull(void *ptr)
{
	ItsIso14827DomainMgr **p = (ItsIso14827DomainMgr **)ptr;
	if (p) { ItsIso14827DomainMgr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainMgr_dump(ItsIso14827DomainMgr *p, int tab);
// ItsIso14827DomainMgr
////////////////////////////////////////////////////////////////////////////////

#endif
