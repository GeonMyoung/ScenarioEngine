#ifndef _DZ1_TDC_DZ1_SOCK_UTIL_DATA_H_
#define _DZ1_TDC_DZ1_SOCK_UTIL_DATA_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1SockUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorArg
typedef struct Dz1SockUtilAcceptorArg
{
	u32_t		parentQueueID;
	u32_t		acceptorID;
} Dz1SockUtilAcceptorArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilAcceptorArg *Dz1SockUtilAcceptorArg_new(u32_t parentQueueID, 
																		   u32_t acceptorID, Dz1Error *err);
static __inline__ Dz1SockUtilAcceptorArg *Dz1SockUtilAcceptorArg_gen(Dz1Error *err) { return Dz1SockUtilAcceptorArg_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorArg_purge(Dz1SockUtilAcceptorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorArg_del(Dz1SockUtilAcceptorArg *p);
static __inline__ void Dz1SockUtilAcceptorArg_delAndSetNull(void *ptr)
{
	Dz1SockUtilAcceptorArg **p = (Dz1SockUtilAcceptorArg **)ptr;
	if (p) { Dz1SockUtilAcceptorArg_del(*p); *p = NULL; }
}
// Dz1SockUtilAcceptorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeust
struct Dz1SockUtilBulkConnectReqeust;
// Dz1SockUtilBulkConnectReqeust
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeustIndex
typedef struct Dz1SockUtilBulkConnectReqeustIndex
{
	void *storage;
	unsigned int (*count)(struct Dz1SockUtilBulkConnectReqeustIndex *p);
	Dz1Error (*travel)(struct Dz1SockUtilBulkConnectReqeustIndex *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1SockUtilBulkConnectReqeustIndex *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1SockUtilBulkConnectReqeustIndex *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	struct Dz1SockUtilBulkConnectReqeust **(*get_array)(struct Dz1SockUtilBulkConnectReqeustIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1SockUtilBulkConnectReqeustIndex *p, struct Dz1SockUtilBulkConnectReqeust *data);
	bool_t (*remove)(struct Dz1SockUtilBulkConnectReqeustIndex *p, struct Dz1SockUtilBulkConnectReqeust *key);
	struct Dz1SockUtilBulkConnectReqeust *(*extract)(struct Dz1SockUtilBulkConnectReqeustIndex *p, struct Dz1SockUtilBulkConnectReqeust *key);
	struct Dz1SockUtilBulkConnectReqeust *(*find)(struct Dz1SockUtilBulkConnectReqeustIndex *p, struct Dz1SockUtilBulkConnectReqeust *key);
	int (*cmp)(struct Dz1SockUtilBulkConnectReqeust *a, struct Dz1SockUtilBulkConnectReqeust *b);
} Dz1SockUtilBulkConnectReqeustIndex;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectReqeustIndex *Dz1SockUtilBulkConnectReqeustIndex_new(Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectReqeustIndex *Dz1SockUtilBulkConnectReqeustIndex_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectReqeustIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustIndex_purge(Dz1SockUtilBulkConnectReqeustIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustIndex_del(Dz1SockUtilBulkConnectReqeustIndex *p);
static __inline__ void Dz1SockUtilBulkConnectReqeustIndex_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectReqeustIndex **p = (Dz1SockUtilBulkConnectReqeustIndex **)ptr;
	if (p != NULL) { Dz1SockUtilBulkConnectReqeustIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustIndexA_dump(Dz1SockUtilBulkConnectReqeustIndex *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustIndexW_dump(Dz1SockUtilBulkConnectReqeustIndex *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectReqeustIndex_dump Dz1SockUtilBulkConnectReqeustIndexW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectReqeustIndex_dump Dz1SockUtilBulkConnectReqeustIndexA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectReqeustIndexX_dump(Dz1SockUtilBulkConnectReqeustIndex *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectReqeustIndex, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectReqeustIndex_dump Dz1SockUtilBulkConnectReqeustIndexA_dump
#define Dz1SockUtilBulkConnectReqeustIndexX_dump Dz1SockUtilBulkConnectReqeustIndexA_dump
#endif // UNIX_SYSTEM

// Dz1SockUtilBulkConnectReqeustIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeustFifo
typedef struct Dz1SockUtilBulkConnectReqeustFifo
{
	void *storage;
	unsigned int (*count)(struct Dz1SockUtilBulkConnectReqeustFifo *p);
	Dz1Error (*travel)(struct Dz1SockUtilBulkConnectReqeustFifo *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1SockUtilBulkConnectReqeustFifo *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1SockUtilBulkConnectReqeustFifo *p, Dz1Error (*func)(void *ptr, struct Dz1SockUtilBulkConnectReqeust *entry), void *ptr);
	struct Dz1SockUtilBulkConnectReqeust **(*get_array)(struct Dz1SockUtilBulkConnectReqeustFifo *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1SockUtilBulkConnectReqeustFifo *p, struct Dz1SockUtilBulkConnectReqeust *data);
	struct Dz1SockUtilBulkConnectReqeust *(*extract)(struct Dz1SockUtilBulkConnectReqeustFifo *p, struct Dz1SockUtilBulkConnectReqeust *ptr);
	struct Dz1SockUtilBulkConnectReqeust *(*getHead)(struct Dz1SockUtilBulkConnectReqeustFifo *p);
	int (*cmp)(struct Dz1SockUtilBulkConnectReqeust *a, struct Dz1SockUtilBulkConnectReqeust *b);
} Dz1SockUtilBulkConnectReqeustFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectReqeustFifo *Dz1SockUtilBulkConnectReqeustFifo_new(Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectReqeustFifo *Dz1SockUtilBulkConnectReqeustFifo_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectReqeustFifo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectReqeustFifo *Dz1SockUtilBulkConnectReqeustFifo_clone(Dz1SockUtilBulkConnectReqeustFifo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustFifo_purge(Dz1SockUtilBulkConnectReqeustFifo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustFifo_del(Dz1SockUtilBulkConnectReqeustFifo *p);
static __inline__ void Dz1SockUtilBulkConnectReqeustFifo_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectReqeustFifo **p = (Dz1SockUtilBulkConnectReqeustFifo **)ptr;
	if (p != NULL) { Dz1SockUtilBulkConnectReqeustFifo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustFifoA_dump(Dz1SockUtilBulkConnectReqeustFifo *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectReqeustFifoW_dump(Dz1SockUtilBulkConnectReqeustFifo *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectReqeustFifo_dump Dz1SockUtilBulkConnectReqeustFifoW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectReqeustFifo_dump Dz1SockUtilBulkConnectReqeustFifoA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectReqeustFifoX_dump(Dz1SockUtilBulkConnectReqeustFifo *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectReqeustFifo, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectReqeustFifo_dump Dz1SockUtilBulkConnectReqeustFifoA_dump
#define Dz1SockUtilBulkConnectReqeustFifoX_dump Dz1SockUtilBulkConnectReqeustFifoA_dump
#endif // UNIX_SYSTEM

// Dz1SockUtilBulkConnectReqeustFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectingEntry
struct Dz1SockUtilBulkConnectReqeust;

typedef struct Dz1SockUtilBulkConnectingEntry
{
	struct Dz1SockUtilBulkConnectReqeust	*req;
	u32_t									 thid;
} Dz1SockUtilBulkConnectingEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectingEntry *Dz1SockUtilBulkConnectingEntry_new(struct Dz1SockUtilBulkConnectReqeust *req_ref, 
																						   u32_t thid, Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectingEntry *Dz1SockUtilBulkConnectingEntry_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectingEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingEntry_purge(Dz1SockUtilBulkConnectingEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingEntry_del(Dz1SockUtilBulkConnectingEntry *p);
static __inline__ void Dz1SockUtilBulkConnectingEntry_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectingEntry **p = (Dz1SockUtilBulkConnectingEntry **)ptr;
	if (p) { Dz1SockUtilBulkConnectingEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingEntryA_dump(Dz1SockUtilBulkConnectingEntry *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingEntryW_dump(Dz1SockUtilBulkConnectingEntry *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectingEntry_dump Dz1SockUtilBulkConnectingEntryW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectingEntry_dump Dz1SockUtilBulkConnectingEntryA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectingEntryX_dump(Dz1SockUtilBulkConnectingEntry *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectingEntry, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectingEntry_dump Dz1SockUtilBulkConnectingEntryA_dump
#define Dz1SockUtilBulkConnectingEntryX_dump Dz1SockUtilBulkConnectingEntryA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1SockUtilBulkConnectingEntry_cmp(Dz1SockUtilBulkConnectingEntry *a, Dz1SockUtilBulkConnectingEntry *b); 
// Dz1SockUtilBulkConnectingEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectingList
typedef struct Dz1SockUtilBulkConnectingList
{
	void *storage;
	unsigned int (*count)(struct Dz1SockUtilBulkConnectingList *p);
	Dz1Error (*travel)(struct Dz1SockUtilBulkConnectingList *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectingEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1SockUtilBulkConnectingList *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectingEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1SockUtilBulkConnectingList *p, Dz1Error (*func)(void *ptr, Dz1SockUtilBulkConnectingEntry *entry), void *ptr);
	Dz1SockUtilBulkConnectingEntry **(*get_array)(struct Dz1SockUtilBulkConnectingList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *data);
	bool_t (*remove)(struct Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key);
	Dz1SockUtilBulkConnectingEntry *(*extract)(struct Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key);
	Dz1SockUtilBulkConnectingEntry *(*find)(struct Dz1SockUtilBulkConnectingList *p, Dz1SockUtilBulkConnectingEntry *key);
	int (*cmp)(Dz1SockUtilBulkConnectingEntry *a, Dz1SockUtilBulkConnectingEntry *b);
} Dz1SockUtilBulkConnectingList;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectingList *Dz1SockUtilBulkConnectingList_new(Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectingList *Dz1SockUtilBulkConnectingList_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectingList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingList_purge(Dz1SockUtilBulkConnectingList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingList_del(Dz1SockUtilBulkConnectingList *p);
static __inline__ void Dz1SockUtilBulkConnectingList_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectingList **p = (Dz1SockUtilBulkConnectingList **)ptr;
	if (p != NULL) { Dz1SockUtilBulkConnectingList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingListA_dump(Dz1SockUtilBulkConnectingList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectingListW_dump(Dz1SockUtilBulkConnectingList *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectingList_dump Dz1SockUtilBulkConnectingListW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectingList_dump Dz1SockUtilBulkConnectingListA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectingListX_dump(Dz1SockUtilBulkConnectingList *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectingList, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectingList_dump Dz1SockUtilBulkConnectingListA_dump
#define Dz1SockUtilBulkConnectingListX_dump Dz1SockUtilBulkConnectingListA_dump
#endif // UNIX_SYSTEM

// Dz1SockUtilBulkConnectingList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectEnv
typedef struct Dz1SockUtilBulkConnectEnv
{
	u8_t									 maxConcurrency;
	Dz1SockUtilBulkConnectReqeustIndex		*index;
	Dz1SockUtilBulkConnectReqeustFifo		*requestFifo;
	Dz1SockUtilBulkConnectingList			*connectingList;
} Dz1SockUtilBulkConnectEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectEnv *Dz1SockUtilBulkConnectEnv_new(u8_t maxConcurrency, Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectEnv *Dz1SockUtilBulkConnectEnv_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectEnv_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEnv_purge(Dz1SockUtilBulkConnectEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEnv_del(Dz1SockUtilBulkConnectEnv *p);
static __inline__ void Dz1SockUtilBulkConnectEnv_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectEnv **p = (Dz1SockUtilBulkConnectEnv **)ptr;
	if (p) { Dz1SockUtilBulkConnectEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEnvA_dump(Dz1SockUtilBulkConnectEnv *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEnvW_dump(Dz1SockUtilBulkConnectEnv *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectEnv_dump Dz1SockUtilBulkConnectEnvW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectEnv_dump Dz1SockUtilBulkConnectEnvA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectEnvX_dump(Dz1SockUtilBulkConnectEnv *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectEnv, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectEnv_dump Dz1SockUtilBulkConnectEnvA_dump
#define Dz1SockUtilBulkConnectEnvX_dump Dz1SockUtilBulkConnectEnvA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectMsg
typedef struct Dz1SockUtilBulkConnectMsg
{
	Dz1SockAddr				*peer;
	Dz1TcpClientSocket		*sock;
	Dz1SockAddr				*local;
} Dz1SockUtilBulkConnectMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectMsg *Dz1SockUtilBulkConnectMsg_new(Dz1SockAddr *peer, 
																				 Dz1TcpClientSocket *sock, 
																				 Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectMsg *Dz1SockUtilBulkConnectMsg_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectMsg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectMsg_purge(Dz1SockUtilBulkConnectMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectMsg_del(Dz1SockUtilBulkConnectMsg *p);
static __inline__ void Dz1SockUtilBulkConnectMsg_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectMsg **p = (Dz1SockUtilBulkConnectMsg **)ptr;
	if (p) { Dz1SockUtilBulkConnectMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectMsgA_dump(Dz1SockUtilBulkConnectMsg *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectMsgW_dump(Dz1SockUtilBulkConnectMsg *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectMsg_dump Dz1SockUtilBulkConnectMsgW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectMsg_dump Dz1SockUtilBulkConnectMsgA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectMsgX_dump(Dz1SockUtilBulkConnectMsg *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectMsg, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectMsg_dump Dz1SockUtilBulkConnectMsgA_dump
#define Dz1SockUtilBulkConnectMsgX_dump Dz1SockUtilBulkConnectMsgA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectMsg
////////////////////////////////////////////////////////////////////////////////

#endif
