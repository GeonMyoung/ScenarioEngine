#ifndef _DZ1_TDC_DZ1_SOCK_UTIL_DEF_H_
#define _DZ1_TDC_DZ1_SOCK_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_io_stream.h"
#include "dz1_elastic_buf.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiverArg
typedef struct Dz1SockUtilReceiverArg
{
	u32_t		parentQueueID;
} Dz1SockUtilReceiverArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilReceiverArg *Dz1SockUtilReceiverArg_new(u32_t parentQueueID, Dz1Error *err);
static __inline__ Dz1SockUtilReceiverArg *Dz1SockUtilReceiverArg_gen(Dz1Error *err) { return Dz1SockUtilReceiverArg_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverArg_purge(Dz1SockUtilReceiverArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverArg_del(Dz1SockUtilReceiverArg *p);
static __inline__ void Dz1SockUtilReceiverArg_delAndSetNull(void *ptr)
{
	Dz1SockUtilReceiverArg **p = (Dz1SockUtilReceiverArg **)ptr;
	if (p) { Dz1SockUtilReceiverArg_del(*p); *p = NULL; }
}
// Dz1SockUtilReceiverArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiver2Arg
typedef struct Dz1SockUtilReceiver2Arg
{
	u32_t		parentQueueID;
	u32_t		sessionID;
} Dz1SockUtilReceiver2Arg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilReceiver2Arg *Dz1SockUtilReceiver2Arg_new(u32_t parentQueueID, 
																			 u32_t sessionID, Dz1Error *err);
static __inline__ Dz1SockUtilReceiver2Arg *Dz1SockUtilReceiver2Arg_gen(Dz1Error *err) { return Dz1SockUtilReceiver2Arg_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2Arg_purge(Dz1SockUtilReceiver2Arg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2Arg_del(Dz1SockUtilReceiver2Arg *p);
static __inline__ void Dz1SockUtilReceiver2Arg_delAndSetNull(void *ptr)
{
	Dz1SockUtilReceiver2Arg **p = (Dz1SockUtilReceiver2Arg **)ptr;
	if (p) { Dz1SockUtilReceiver2Arg_del(*p); *p = NULL; }
}
// Dz1SockUtilReceiver2Arg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorConnected
typedef struct Dz1SockUtilAcceptorConnected
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	u32_t					 acceptorID;
	Dz1TcpClientSocket		*sock;
} Dz1SockUtilAcceptorConnected;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilAcceptorConnected *Dz1SockUtilAcceptorConnected_new(Dz1SockAddr *peer, 
																					   Dz1SockAddr *local, 
																					   u32_t acceptorID, 
																					   Dz1TcpClientSocket *sock, Dz1Error *err);
static __inline__ Dz1SockUtilAcceptorConnected *Dz1SockUtilAcceptorConnected_gen(Dz1Error *err) { return Dz1SockUtilAcceptorConnected_new(NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorConnected_purge(Dz1SockUtilAcceptorConnected *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorConnected_del(Dz1SockUtilAcceptorConnected *p);
static __inline__ void Dz1SockUtilAcceptorConnected_delAndSetNull(void *ptr)
{
	Dz1SockUtilAcceptorConnected **p = (Dz1SockUtilAcceptorConnected **)ptr;
	if (p) { Dz1SockUtilAcceptorConnected_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorConnectedA_dump(Dz1SockUtilAcceptorConnected *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorConnectedW_dump(Dz1SockUtilAcceptorConnected *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilAcceptorConnected_dump Dz1SockUtilAcceptorConnectedW_dump
#else //  UNICODE
#define Dz1SockUtilAcceptorConnected_dump Dz1SockUtilAcceptorConnectedA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilAcceptorConnectedX_dump(Dz1SockUtilAcceptorConnected *p, int tab) { DZ1_DUMP(Dz1SockUtilAcceptorConnected, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilAcceptorConnected_dump Dz1SockUtilAcceptorConnectedA_dump
#define Dz1SockUtilAcceptorConnectedX_dump Dz1SockUtilAcceptorConnectedA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilAcceptorConnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorException
typedef struct Dz1SockUtilAcceptorException
{
	u32_t		acceptorID;
} Dz1SockUtilAcceptorException;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilAcceptorException *Dz1SockUtilAcceptorException_new(u32_t acceptorID, Dz1Error *err);
static __inline__ Dz1SockUtilAcceptorException *Dz1SockUtilAcceptorException_gen(Dz1Error *err) { return Dz1SockUtilAcceptorException_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorException_purge(Dz1SockUtilAcceptorException *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorException_del(Dz1SockUtilAcceptorException *p);
static __inline__ void Dz1SockUtilAcceptorException_delAndSetNull(void *ptr)
{
	Dz1SockUtilAcceptorException **p = (Dz1SockUtilAcceptorException **)ptr;
	if (p) { Dz1SockUtilAcceptorException_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorExceptionA_dump(Dz1SockUtilAcceptorException *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilAcceptorExceptionW_dump(Dz1SockUtilAcceptorException *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilAcceptorException_dump Dz1SockUtilAcceptorExceptionW_dump
#else //  UNICODE
#define Dz1SockUtilAcceptorException_dump Dz1SockUtilAcceptorExceptionA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilAcceptorExceptionX_dump(Dz1SockUtilAcceptorException *p, int tab) { DZ1_DUMP(Dz1SockUtilAcceptorException, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilAcceptorException_dump Dz1SockUtilAcceptorExceptionA_dump
#define Dz1SockUtilAcceptorExceptionX_dump Dz1SockUtilAcceptorExceptionA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilAcceptorException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiverReceived
typedef struct Dz1SockUtilReceiverReceived
{
	Dz1SockAddr		*peer;
	Dz1SockAddr		*local;
	Dz1Binary		*stream;
} Dz1SockUtilReceiverReceived;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilReceiverReceived *Dz1SockUtilReceiverReceived_new(Dz1SockAddr *peer, 
																					 Dz1SockAddr *local, 
																					 Dz1Binary *stream, Dz1Error *err);
static __inline__ Dz1SockUtilReceiverReceived *Dz1SockUtilReceiverReceived_gen(Dz1Error *err) { return Dz1SockUtilReceiverReceived_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverReceived_purge(Dz1SockUtilReceiverReceived *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverReceived_del(Dz1SockUtilReceiverReceived *p);
static __inline__ void Dz1SockUtilReceiverReceived_delAndSetNull(void *ptr)
{
	Dz1SockUtilReceiverReceived **p = (Dz1SockUtilReceiverReceived **)ptr;
	if (p) { Dz1SockUtilReceiverReceived_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverReceivedA_dump(Dz1SockUtilReceiverReceived *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiverReceivedW_dump(Dz1SockUtilReceiverReceived *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilReceiverReceived_dump Dz1SockUtilReceiverReceivedW_dump
#else //  UNICODE
#define Dz1SockUtilReceiverReceived_dump Dz1SockUtilReceiverReceivedA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilReceiverReceivedX_dump(Dz1SockUtilReceiverReceived *p, int tab) { DZ1_DUMP(Dz1SockUtilReceiverReceived, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilReceiverReceived_dump Dz1SockUtilReceiverReceivedA_dump
#define Dz1SockUtilReceiverReceivedX_dump Dz1SockUtilReceiverReceivedA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilReceiverReceived
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTransmiterSent
typedef struct Dz1SockUtilTransmiterSent
{
	Dz1SockAddr		*peer;
	Dz1SockAddr		*local;
} Dz1SockUtilTransmiterSent;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTransmiterSent *Dz1SockUtilTransmiterSent_new(Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1SockUtilTransmiterSent *Dz1SockUtilTransmiterSent_gen(Dz1Error *err) { return Dz1SockUtilTransmiterSent_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiterSent_purge(Dz1SockUtilTransmiterSent *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiterSent_del(Dz1SockUtilTransmiterSent *p);
static __inline__ void Dz1SockUtilTransmiterSent_delAndSetNull(void *ptr)
{
	Dz1SockUtilTransmiterSent **p = (Dz1SockUtilTransmiterSent **)ptr;
	if (p) { Dz1SockUtilTransmiterSent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiterSentA_dump(Dz1SockUtilTransmiterSent *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiterSentW_dump(Dz1SockUtilTransmiterSent *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilTransmiterSent_dump Dz1SockUtilTransmiterSentW_dump
#else //  UNICODE
#define Dz1SockUtilTransmiterSent_dump Dz1SockUtilTransmiterSentA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilTransmiterSentX_dump(Dz1SockUtilTransmiterSent *p, int tab) { DZ1_DUMP(Dz1SockUtilTransmiterSent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilTransmiterSent_dump Dz1SockUtilTransmiterSentA_dump
#define Dz1SockUtilTransmiterSentX_dump Dz1SockUtilTransmiterSentA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilTransmiterSent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiver2Received
typedef struct Dz1SockUtilReceiver2Received
{
	u32_t			 sessionID;
	Dz1Binary		*stream;
} Dz1SockUtilReceiver2Received;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilReceiver2Received *Dz1SockUtilReceiver2Received_new(u32_t sessionID, 
																					   Dz1Binary *stream, Dz1Error *err);
static __inline__ Dz1SockUtilReceiver2Received *Dz1SockUtilReceiver2Received_gen(Dz1Error *err) { return Dz1SockUtilReceiver2Received_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2Received_purge(Dz1SockUtilReceiver2Received *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2Received_del(Dz1SockUtilReceiver2Received *p);
static __inline__ void Dz1SockUtilReceiver2Received_delAndSetNull(void *ptr)
{
	Dz1SockUtilReceiver2Received **p = (Dz1SockUtilReceiver2Received **)ptr;
	if (p) { Dz1SockUtilReceiver2Received_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2ReceivedA_dump(Dz1SockUtilReceiver2Received *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilReceiver2ReceivedW_dump(Dz1SockUtilReceiver2Received *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilReceiver2Received_dump Dz1SockUtilReceiver2ReceivedW_dump
#else //  UNICODE
#define Dz1SockUtilReceiver2Received_dump Dz1SockUtilReceiver2ReceivedA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilReceiver2ReceivedX_dump(Dz1SockUtilReceiver2Received *p, int tab) { DZ1_DUMP(Dz1SockUtilReceiver2Received, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilReceiver2Received_dump Dz1SockUtilReceiver2ReceivedA_dump
#define Dz1SockUtilReceiver2ReceivedX_dump Dz1SockUtilReceiver2ReceivedA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilReceiver2Received
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTransmiter2Sent
typedef struct Dz1SockUtilTransmiter2Sent
{
	u32_t		sessionID;
} Dz1SockUtilTransmiter2Sent;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTransmiter2Sent *Dz1SockUtilTransmiter2Sent_new(u32_t sessionID, Dz1Error *err);
static __inline__ Dz1SockUtilTransmiter2Sent *Dz1SockUtilTransmiter2Sent_gen(Dz1Error *err) { return Dz1SockUtilTransmiter2Sent_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiter2Sent_purge(Dz1SockUtilTransmiter2Sent *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiter2Sent_del(Dz1SockUtilTransmiter2Sent *p);
static __inline__ void Dz1SockUtilTransmiter2Sent_delAndSetNull(void *ptr)
{
	Dz1SockUtilTransmiter2Sent **p = (Dz1SockUtilTransmiter2Sent **)ptr;
	if (p) { Dz1SockUtilTransmiter2Sent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiter2SentA_dump(Dz1SockUtilTransmiter2Sent *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTransmiter2SentW_dump(Dz1SockUtilTransmiter2Sent *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilTransmiter2Sent_dump Dz1SockUtilTransmiter2SentW_dump
#else //  UNICODE
#define Dz1SockUtilTransmiter2Sent_dump Dz1SockUtilTransmiter2SentA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilTransmiter2SentX_dump(Dz1SockUtilTransmiter2Sent *p, int tab) { DZ1_DUMP(Dz1SockUtilTransmiter2Sent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilTransmiter2Sent_dump Dz1SockUtilTransmiter2SentA_dump
#define Dz1SockUtilTransmiter2SentX_dump Dz1SockUtilTransmiter2SentA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilTransmiter2Sent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectEntry
typedef struct Dz1SockUtilBulkConnectEntry
{
	Dz1SockAddr		*addr;
	u32_t			 thid;
} Dz1SockUtilBulkConnectEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectEntry *Dz1SockUtilBulkConnectEntry_new(Dz1SockAddr *addr, 
																					 u32_t thid, Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectEntry *Dz1SockUtilBulkConnectEntry_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEntry_purge(Dz1SockUtilBulkConnectEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEntry_del(Dz1SockUtilBulkConnectEntry *p);
static __inline__ void Dz1SockUtilBulkConnectEntry_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectEntry **p = (Dz1SockUtilBulkConnectEntry **)ptr;
	if (p) { Dz1SockUtilBulkConnectEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEntryA_dump(Dz1SockUtilBulkConnectEntry *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectEntryW_dump(Dz1SockUtilBulkConnectEntry *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectEntry_dump Dz1SockUtilBulkConnectEntryW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectEntry_dump Dz1SockUtilBulkConnectEntryA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectEntryX_dump(Dz1SockUtilBulkConnectEntry *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectEntry, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectEntry_dump Dz1SockUtilBulkConnectEntryA_dump
#define Dz1SockUtilBulkConnectEntryX_dump Dz1SockUtilBulkConnectEntryA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectResult
typedef struct Dz1SockUtilBulkConnectResult
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	void					*userData;
} Dz1SockUtilBulkConnectResult;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilBulkConnectResult *Dz1SockUtilBulkConnectResult_new(Dz1SockAddr *peer, 
																					   Dz1SockAddr *local, 
																					   Dz1TcpClientSocket *sock, 
																					   void *userData, Dz1Error *err);
static __inline__ Dz1SockUtilBulkConnectResult *Dz1SockUtilBulkConnectResult_gen(Dz1Error *err) { return Dz1SockUtilBulkConnectResult_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectResult_purge(Dz1SockUtilBulkConnectResult *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectResult_del(Dz1SockUtilBulkConnectResult *p);
static __inline__ void Dz1SockUtilBulkConnectResult_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnectResult **p = (Dz1SockUtilBulkConnectResult **)ptr;
	if (p) { Dz1SockUtilBulkConnectResult_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectResultA_dump(Dz1SockUtilBulkConnectResult *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilBulkConnectResultW_dump(Dz1SockUtilBulkConnectResult *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilBulkConnectResult_dump Dz1SockUtilBulkConnectResultW_dump
#else //  UNICODE
#define Dz1SockUtilBulkConnectResult_dump Dz1SockUtilBulkConnectResultA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilBulkConnectResultX_dump(Dz1SockUtilBulkConnectResult *p, int tab) { DZ1_DUMP(Dz1SockUtilBulkConnectResult, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilBulkConnectResult_dump Dz1SockUtilBulkConnectResultA_dump
#define Dz1SockUtilBulkConnectResultX_dump Dz1SockUtilBulkConnectResultA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilRxBuf
typedef struct Dz1SockUtilRxBuf
{
	u32_t				 elastic_size;
	Dz1Stream			*st;
	Dz1ElasticBuf		*elb;
} Dz1SockUtilRxBuf;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilRxBuf *Dz1SockUtilRxBuf_new(u32_t elastic_size, Dz1Error *err);	// User Customized
static __inline__ Dz1SockUtilRxBuf *Dz1SockUtilRxBuf_gen(Dz1Error *err) { return Dz1SockUtilRxBuf_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilRxBuf_purge(Dz1SockUtilRxBuf *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilRxBuf_del(Dz1SockUtilRxBuf *p);
static __inline__ void Dz1SockUtilRxBuf_delAndSetNull(void *ptr)
{
	Dz1SockUtilRxBuf **p = (Dz1SockUtilRxBuf **)ptr;
	if (p) { Dz1SockUtilRxBuf_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilRxBufA_dump(Dz1SockUtilRxBuf *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilRxBufW_dump(Dz1SockUtilRxBuf *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilRxBuf_dump Dz1SockUtilRxBufW_dump
#else //  UNICODE
#define Dz1SockUtilRxBuf_dump Dz1SockUtilRxBufA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilRxBufX_dump(Dz1SockUtilRxBuf *p, int tab) { DZ1_DUMP(Dz1SockUtilRxBuf, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilRxBuf_dump Dz1SockUtilRxBufA_dump
#define Dz1SockUtilRxBufX_dump Dz1SockUtilRxBufA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilRxBuf
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxEntry
struct Dz1SockUtilTxEntry;

typedef struct Dz1SockUtilTxEntry
{
	struct Dz1SockUtilTxEntry		*next;
	Dz1Binary						*chunk;
} Dz1SockUtilTxEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTxEntry *Dz1SockUtilTxEntry_new(struct Dz1SockUtilTxEntry *next_ref, 
																   Dz1Binary *chunk, Dz1Error *err);
static __inline__ Dz1SockUtilTxEntry *Dz1SockUtilTxEntry_gen(Dz1Error *err) { return Dz1SockUtilTxEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SockUtilTxEntry_copy(Dz1SockUtilTxEntry *dst, Dz1SockUtilTxEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTxEntry *Dz1SockUtilTxEntry_clone(Dz1SockUtilTxEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxEntry_purge(Dz1SockUtilTxEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxEntry_del(Dz1SockUtilTxEntry *p);
static __inline__ void Dz1SockUtilTxEntry_delAndSetNull(void *ptr)
{
	Dz1SockUtilTxEntry **p = (Dz1SockUtilTxEntry **)ptr;
	if (p) { Dz1SockUtilTxEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxEntryA_dump(Dz1SockUtilTxEntry *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxEntryW_dump(Dz1SockUtilTxEntry *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilTxEntry_dump Dz1SockUtilTxEntryW_dump
#else //  UNICODE
#define Dz1SockUtilTxEntry_dump Dz1SockUtilTxEntryA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilTxEntryX_dump(Dz1SockUtilTxEntry *p, int tab) { DZ1_DUMP(Dz1SockUtilTxEntry, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilTxEntry_dump Dz1SockUtilTxEntryA_dump
#define Dz1SockUtilTxEntryX_dump Dz1SockUtilTxEntryA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilTxEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxFifo
typedef struct Dz1SockUtilTxFifo
{
	Dz1SockUtilTxEntry		*head;
	Dz1SockUtilTxEntry		*tail;
} Dz1SockUtilTxFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTxFifo *Dz1SockUtilTxFifo_new(Dz1Error *err);
static __inline__ Dz1SockUtilTxFifo *Dz1SockUtilTxFifo_gen(Dz1Error *err) { return Dz1SockUtilTxFifo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SockUtilTxFifo_copy(Dz1SockUtilTxFifo *dst, Dz1SockUtilTxFifo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilTxFifo *Dz1SockUtilTxFifo_clone(Dz1SockUtilTxFifo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxFifo_purge(Dz1SockUtilTxFifo *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxFifo_del(Dz1SockUtilTxFifo *p);	// User Customized
static __inline__ void Dz1SockUtilTxFifo_delAndSetNull(void *ptr)
{
	Dz1SockUtilTxFifo **p = (Dz1SockUtilTxFifo **)ptr;
	if (p) { Dz1SockUtilTxFifo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxFifoA_dump(Dz1SockUtilTxFifo *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilTxFifoW_dump(Dz1SockUtilTxFifo *p, int tab);
#ifdef UNICODE
#define Dz1SockUtilTxFifo_dump Dz1SockUtilTxFifoW_dump
#else //  UNICODE
#define Dz1SockUtilTxFifo_dump Dz1SockUtilTxFifoA_dump
#endif //  UNICODE
static __inline__ void Dz1SockUtilTxFifoX_dump(Dz1SockUtilTxFifo *p, int tab) { DZ1_DUMP(Dz1SockUtilTxFifo, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SockUtilTxFifo_dump Dz1SockUtilTxFifoA_dump
#define Dz1SockUtilTxFifoX_dump Dz1SockUtilTxFifoA_dump
#endif // UNIX_SYSTEM
// Dz1SockUtilTxFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CallbackSockIO
typedef struct Dz1CallbackSockIO
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Dz1CallbackSockIO;

DZ1_CPPLINK DZ1_DLLPORT void Dz1CallbackSockIO_purge(Dz1CallbackSockIO *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CallbackSockIO_del(Dz1CallbackSockIO *p);
static __inline__ void Dz1CallbackSockIO_delAndSetNull(void *ptr)
{
	Dz1CallbackSockIO **p = (Dz1CallbackSockIO **)ptr;
	if (p) { Dz1CallbackSockIO_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CallbackSockIOA_dump(Dz1CallbackSockIO *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1CallbackSockIOW_dump(Dz1CallbackSockIO *p, int tab);
#ifdef UNICODE
#define Dz1CallbackSockIO_dump Dz1CallbackSockIOW_dump
#else //  UNICODE
#define Dz1CallbackSockIO_dump Dz1CallbackSockIOA_dump
#endif //  UNICODE
static __inline__ void Dz1CallbackSockIOX_dump(Dz1CallbackSockIO *p, int tab) { DZ1_DUMP(Dz1CallbackSockIO, p, tab); }
#else // UNIX_SYSTEM
#define Dz1CallbackSockIO_dump Dz1CallbackSockIOA_dump
#define Dz1CallbackSockIOX_dump Dz1CallbackSockIOA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1CallbackSockIO_cmp(Dz1CallbackSockIO *a, Dz1CallbackSockIO *b); 
// Dz1CallbackSockIO
////////////////////////////////////////////////////////////////////////////////

#endif
