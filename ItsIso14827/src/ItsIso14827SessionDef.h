#ifndef _DZ1_TDC_ITS_ISO14827_SESSION_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_SESSION_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"
#include "dz1_io_stream_support.h"
#include "dz1_fsm2.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainKey
struct ItsIso14827DomainKey;
// ItsIso14827DomainKey
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionEntry
typedef struct ItsIso14827SessionEntry
{
	ItsIso14827SessionKey		*key;
	Dz1TcpClientSocket			*sock;
	u32_t						 receiver;
	Dz1ElasticBuf				*buf;
	Dz1Asn1Codec				 codecRule;
	ItsIso14827CRCCheck			 CRCCheck;
	u32_t						 txSerial;
	u32_t						*rxSerial;
	void						*initiator;
	void						*uRsc;
	void						*timer;
} ItsIso14827SessionEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionEntry *ItsIso14827SessionEntry_new(ItsIso14827SessionKey *key, 
																			 Dz1TcpClientSocket *sock, 
																			 u32_t receiver, 
																			 Dz1ElasticBuf *buf, 
																			 Dz1Asn1Codec codecRule, 
																			 ItsIso14827CRCCheck CRCCheck, 
																			 void *initiator, 
																			 void *uRsc, 
																			 void *timer, Dz1Error *err);
static __inline__ ItsIso14827SessionEntry *ItsIso14827SessionEntry_gen(Dz1Error *err) { return ItsIso14827SessionEntry_new(NULL, NULL, 0, NULL, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionEntry_purge(ItsIso14827SessionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionEntry_del(ItsIso14827SessionEntry *p);
static __inline__ void ItsIso14827SessionEntry_delAndSetNull(void *ptr)
{
	ItsIso14827SessionEntry **p = (ItsIso14827SessionEntry **)ptr;
	if (p) { ItsIso14827SessionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionEntry_dump(ItsIso14827SessionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827SessionEntry_cmp(ItsIso14827SessionEntry *a, ItsIso14827SessionEntry *b); 
// ItsIso14827SessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionList
typedef struct ItsIso14827SessionList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827SessionList *p);
	Dz1Error (*travel)(struct ItsIso14827SessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SessionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827SessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SessionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827SessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SessionEntry *entry), void *ptr);
	ItsIso14827SessionEntry **(*get_array)(struct ItsIso14827SessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827SessionList *p, ItsIso14827SessionEntry *data);
	bool_t (*remove)(struct ItsIso14827SessionList *p, ItsIso14827SessionEntry *key);
	ItsIso14827SessionEntry *(*extract)(struct ItsIso14827SessionList *p, ItsIso14827SessionEntry *key);
	ItsIso14827SessionEntry *(*find)(struct ItsIso14827SessionList *p, ItsIso14827SessionEntry *key);
	int (*cmp)(ItsIso14827SessionEntry *a, ItsIso14827SessionEntry *b);
} ItsIso14827SessionList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionList *ItsIso14827SessionList_new(Dz1Error *err);
static __inline__ ItsIso14827SessionList *ItsIso14827SessionList_gen(Dz1Error *err) { return ItsIso14827SessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionList_purge(ItsIso14827SessionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionList_del(ItsIso14827SessionList *p);
static __inline__ void ItsIso14827SessionList_delAndSetNull(void *ptr)
{
	ItsIso14827SessionList **p = (ItsIso14827SessionList **)ptr;
	if (p != NULL) { ItsIso14827SessionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionList_dump(ItsIso14827SessionList *p, int tab);

// ItsIso14827SessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827AcceptorEntry
typedef struct ItsIso14827AcceptorEntry
{
	Dz1SockAddr				*server;
	u32_t					 thID;
	Dz1Asn1Codec			 initial;
	ItsIso14827CRCCheck		 CRCCheck;
	s32_t					 ref;
} ItsIso14827AcceptorEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827AcceptorEntry *ItsIso14827AcceptorEntry_new(Dz1SockAddr *server, 
																			   u32_t thID, 
																			   Dz1Asn1Codec initial, 
																			   ItsIso14827CRCCheck CRCCheck, Dz1Error *err);
static __inline__ ItsIso14827AcceptorEntry *ItsIso14827AcceptorEntry_gen(Dz1Error *err) { return ItsIso14827AcceptorEntry_new(NULL, 0, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorEntry_purge(ItsIso14827AcceptorEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorEntry_del(ItsIso14827AcceptorEntry *p);
static __inline__ void ItsIso14827AcceptorEntry_delAndSetNull(void *ptr)
{
	ItsIso14827AcceptorEntry **p = (ItsIso14827AcceptorEntry **)ptr;
	if (p) { ItsIso14827AcceptorEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorEntry_dump(ItsIso14827AcceptorEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827AcceptorEntry_cmp(ItsIso14827AcceptorEntry *a, ItsIso14827AcceptorEntry *b); 
// ItsIso14827AcceptorEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827AcceptorList
typedef struct ItsIso14827AcceptorList
{
	void *storage;
	unsigned int (*count)(struct ItsIso14827AcceptorList *p);
	Dz1Error (*travel)(struct ItsIso14827AcceptorList *p, Dz1Error (*func)(void *ptr, ItsIso14827AcceptorEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ItsIso14827AcceptorList *p, Dz1Error (*func)(void *ptr, ItsIso14827AcceptorEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ItsIso14827AcceptorList *p, Dz1Error (*func)(void *ptr, ItsIso14827AcceptorEntry *entry), void *ptr);
	ItsIso14827AcceptorEntry **(*get_array)(struct ItsIso14827AcceptorList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *data);
	bool_t (*remove)(struct ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key);
	ItsIso14827AcceptorEntry *(*extract)(struct ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key);
	ItsIso14827AcceptorEntry *(*find)(struct ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key);
	int (*cmp)(ItsIso14827AcceptorEntry *a, ItsIso14827AcceptorEntry *b);
} ItsIso14827AcceptorList;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827AcceptorList *ItsIso14827AcceptorList_new(Dz1Error *err);
static __inline__ ItsIso14827AcceptorList *ItsIso14827AcceptorList_gen(Dz1Error *err) { return ItsIso14827AcceptorList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorList_purge(ItsIso14827AcceptorList *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorList_del(ItsIso14827AcceptorList *p);
static __inline__ void ItsIso14827AcceptorList_delAndSetNull(void *ptr)
{
	ItsIso14827AcceptorList **p = (ItsIso14827AcceptorList **)ptr;
	if (p != NULL) { ItsIso14827AcceptorList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827AcceptorList_dump(ItsIso14827AcceptorList *p, int tab);

// ItsIso14827AcceptorList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr
typedef struct ItsIso14827SessionMgr
{
	u32_t						 myQueueID;
	ItsIso14827AcceptorList		*listener;
	u32_t						 allocSID;
	ItsIso14827SessionList		*sessions;
	bool_t						 debug_dump;
} ItsIso14827SessionMgr;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SessionMgr *ItsIso14827SessionMgr_new(u32_t myQueueID, Dz1Error *err);
static __inline__ ItsIso14827SessionMgr *ItsIso14827SessionMgr_gen(Dz1Error *err) { return ItsIso14827SessionMgr_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionMgr_purge(ItsIso14827SessionMgr *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionMgr_del(ItsIso14827SessionMgr *p);
static __inline__ void ItsIso14827SessionMgr_delAndSetNull(void *ptr)
{
	ItsIso14827SessionMgr **p = (ItsIso14827SessionMgr **)ptr;
	if (p) { ItsIso14827SessionMgr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SessionMgr_dump(ItsIso14827SessionMgr *p, int tab);
// ItsIso14827SessionMgr
////////////////////////////////////////////////////////////////////////////////

#endif
