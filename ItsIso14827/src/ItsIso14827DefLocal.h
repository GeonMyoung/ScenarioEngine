#ifndef _DZ1_TDC_ITS_ISO14827_DEF_LOCAL_H_
#define _DZ1_TDC_ITS_ISO14827_DEF_LOCAL_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CodecOIDMap
typedef struct ItsIso14827CodecOIDMap
{
	Dz1Asn1OID		*oid;
	Dz1Asn1Codec	 mean;
} ItsIso14827CodecOIDMap;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827CodecOIDMap *ItsIso14827CodecOIDMap_new(Dz1Asn1OID *oid, 
																		   Dz1Asn1Codec mean, Dz1Error *err);
static __inline__ ItsIso14827CodecOIDMap *ItsIso14827CodecOIDMap_gen(Dz1Error *err) { return ItsIso14827CodecOIDMap_new(NULL, Dz1Asn1Codec_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMap_purge(ItsIso14827CodecOIDMap *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMap_del(ItsIso14827CodecOIDMap *p);
static __inline__ void ItsIso14827CodecOIDMap_delAndSetNull(void *ptr)
{
	ItsIso14827CodecOIDMap **p = (ItsIso14827CodecOIDMap **)ptr;
	if (p) { ItsIso14827CodecOIDMap_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMap_dump(ItsIso14827CodecOIDMap *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827CodecOIDMap_cmp(ItsIso14827CodecOIDMap *a, ItsIso14827CodecOIDMap *b); 
// ItsIso14827CodecOIDMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CodecOIDMapList
typedef struct ItsIso14827CodecOIDMapList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827CodecOIDMapList *p);
	Dz1Error (*travel)(struct ItsIso14827CodecOIDMapList *p, Dz1Error (*func)(void *ptr, ItsIso14827CodecOIDMap *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827CodecOIDMapList *p, Dz1Error (*func)(void *ptr, ItsIso14827CodecOIDMap *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827CodecOIDMapList *p, Dz1Error (*func)(void *ptr, ItsIso14827CodecOIDMap *entry), void *ptr);
	ItsIso14827CodecOIDMap **(*get_array)(struct ItsIso14827CodecOIDMapList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *data);
	bool_t (*remove)(struct ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key);
	ItsIso14827CodecOIDMap *(*extract)(struct ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key);
	ItsIso14827CodecOIDMap *(*find)(struct ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key);
	int (*cmp)(ItsIso14827CodecOIDMap *a, ItsIso14827CodecOIDMap *b);
} ItsIso14827CodecOIDMapList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827CodecOIDMapList *ItsIso14827CodecOIDMapList_new(Dz1Error *err);
static __inline__ ItsIso14827CodecOIDMapList *ItsIso14827CodecOIDMapList_gen(Dz1Error *err) { return ItsIso14827CodecOIDMapList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMapList_purge(ItsIso14827CodecOIDMapList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMapList_del(ItsIso14827CodecOIDMapList *p);
static __inline__ void ItsIso14827CodecOIDMapList_delAndSetNull(void *ptr)
{
	ItsIso14827CodecOIDMapList **p = (ItsIso14827CodecOIDMapList **)ptr;
	if (p != NULL) { ItsIso14827CodecOIDMapList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827CodecOIDMapList_dump(ItsIso14827CodecOIDMapList *p, int tab);

// ItsIso14827CodecOIDMapList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainViolatedPublication
typedef struct ItsIso14827ServerDomainViolatedPublication
{
	ItsIso14827CallbackPublication		 inform;
	void								*param;
} ItsIso14827ServerDomainViolatedPublication;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainViolatedPublication *ItsIso14827ServerDomainViolatedPublication_new(ItsIso14827CallbackPublication inform, 
																												   void *param, Dz1Error *err);
static __inline__ ItsIso14827ServerDomainViolatedPublication *ItsIso14827ServerDomainViolatedPublication_gen(Dz1Error *err) { return ItsIso14827ServerDomainViolatedPublication_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ServerDomainViolatedPublication_copy(ItsIso14827ServerDomainViolatedPublication *dst, ItsIso14827ServerDomainViolatedPublication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ServerDomainViolatedPublication *ItsIso14827ServerDomainViolatedPublication_clone(ItsIso14827ServerDomainViolatedPublication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainViolatedPublication_purge(ItsIso14827ServerDomainViolatedPublication *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainViolatedPublication_del(ItsIso14827ServerDomainViolatedPublication *p);
static __inline__ void ItsIso14827ServerDomainViolatedPublication_delAndSetNull(void *ptr)
{
	ItsIso14827ServerDomainViolatedPublication **p = (ItsIso14827ServerDomainViolatedPublication **)ptr;
	if (p) { ItsIso14827ServerDomainViolatedPublication_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ServerDomainViolatedPublication_dump(ItsIso14827ServerDomainViolatedPublication *p, int tab);
// ItsIso14827ServerDomainViolatedPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainViolatedSubscription
typedef struct ItsIso14827ClientDomainViolatedSubscription
{
	ItsIso14827CallbackViolatedSubRcvd		 inform;
	void									*param;
} ItsIso14827ClientDomainViolatedSubscription;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainViolatedSubscription *ItsIso14827ClientDomainViolatedSubscription_new(ItsIso14827CallbackViolatedSubRcvd inform, 
																													 void *param, Dz1Error *err);
static __inline__ ItsIso14827ClientDomainViolatedSubscription *ItsIso14827ClientDomainViolatedSubscription_gen(Dz1Error *err) { return ItsIso14827ClientDomainViolatedSubscription_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ItsIso14827ClientDomainViolatedSubscription_copy(ItsIso14827ClientDomainViolatedSubscription *dst, ItsIso14827ClientDomainViolatedSubscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClientDomainViolatedSubscription *ItsIso14827ClientDomainViolatedSubscription_clone(ItsIso14827ClientDomainViolatedSubscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainViolatedSubscription_purge(ItsIso14827ClientDomainViolatedSubscription *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainViolatedSubscription_del(ItsIso14827ClientDomainViolatedSubscription *p);
static __inline__ void ItsIso14827ClientDomainViolatedSubscription_delAndSetNull(void *ptr)
{
	ItsIso14827ClientDomainViolatedSubscription **p = (ItsIso14827ClientDomainViolatedSubscription **)ptr;
	if (p) { ItsIso14827ClientDomainViolatedSubscription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClientDomainViolatedSubscription_dump(ItsIso14827ClientDomainViolatedSubscription *p, int tab);
// ItsIso14827ClientDomainViolatedSubscription
////////////////////////////////////////////////////////////////////////////////

#endif
