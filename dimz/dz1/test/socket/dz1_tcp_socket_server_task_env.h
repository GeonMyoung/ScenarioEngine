#ifndef _DZ1_TDC_DZ1_TCP_SOCKET_SERVER_TASK_ENV_H_
#define _DZ1_TDC_DZ1_TCP_SOCKET_SERVER_TASK_ENV_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_sock_addr.h>

#include "dz1_socket_fifo.h"
#include "libdz1_support.h"

typedef struct ReceiverEntry
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1TcpClientSocket *sock;
	u32_t rcvr;
	Dz1SocketFifo *tx;
} ReceiverEntry;

DZ1_CPPLINK DZ1_DLLPORT ReceiverEntry *ReceiverEntry_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			Dz1TcpClientSocket *sock,
			u32_t rcvr,
			Dz1SocketFifo *tx, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ReceiverEntry_del(ReceiverEntry *p);
static __inline__ void ReceiverEntry_delAndSetNull(void *ptr)
{
	ReceiverEntry **p = (ReceiverEntry **)ptr;
	ReceiverEntry_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void ReceiverEntry_dump(ReceiverEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ReceiverEntry_cmp(ReceiverEntry *a, ReceiverEntry *b);
typedef struct ReceiverList
{
	void *storage;
	Dz1Error (*add)(struct ReceiverList *p, ReceiverEntry *data);
	void (*remove)(struct ReceiverList *p, ReceiverEntry *key);
	ReceiverEntry *(*extract)(struct ReceiverList *p, ReceiverEntry *key);
	Dz1Error (*travel)(struct ReceiverList *p, Dz1Error (*func)(void *ptr, ReceiverEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ReceiverList *p, Dz1Error (*func)(void *ptr, ReceiverEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ReceiverList *p, Dz1Error (*func)(void *ptr, ReceiverEntry *entry), void *ptr);
	ReceiverEntry *(*find)(struct ReceiverList *p, ReceiverEntry *key);
} ReceiverList;

DZ1_CPPLINK DZ1_DLLPORT ReceiverList *ReceiverList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ReceiverList_del(ReceiverList *p);
static __inline__ void ReceiverList_delAndSetNull(void *ptr)
{
	ReceiverList **p = (ReceiverList **)ptr;
	ReceiverList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void ReceiverList_dump(ReceiverList *p, int tab);
typedef struct AcceptorEntry
{
	u16_t port;
	u32_t acceptor;
} AcceptorEntry;

DZ1_CPPLINK DZ1_DLLPORT AcceptorEntry *AcceptorEntry_new(u16_t port, u32_t acceptor, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void AcceptorEntry_del(AcceptorEntry *p);
static __inline__ void AcceptorEntry_delAndSetNull(void *ptr)
{
	AcceptorEntry **p = (AcceptorEntry **)ptr;
	AcceptorEntry_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void AcceptorEntry_dump(AcceptorEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int AcceptorEntry_cmp(AcceptorEntry *a, AcceptorEntry *b);
typedef struct AcceptorList
{
	void *storage;
	Dz1Error (*add)(struct AcceptorList *p, AcceptorEntry *data);
	void (*remove)(struct AcceptorList *p, AcceptorEntry *key);
	AcceptorEntry *(*extract)(struct AcceptorList *p, AcceptorEntry *key);
	Dz1Error (*travel)(struct AcceptorList *p, Dz1Error (*func)(void *ptr, AcceptorEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct AcceptorList *p, Dz1Error (*func)(void *ptr, AcceptorEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct AcceptorList *p, Dz1Error (*func)(void *ptr, AcceptorEntry *entry), void *ptr);
	AcceptorEntry *(*find)(struct AcceptorList *p, AcceptorEntry *key);
} AcceptorList;

DZ1_CPPLINK DZ1_DLLPORT AcceptorList *AcceptorList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void AcceptorList_del(AcceptorList *p);
static __inline__ void AcceptorList_delAndSetNull(void *ptr)
{
	AcceptorList **p = (AcceptorList **)ptr;
	AcceptorList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void AcceptorList_dump(AcceptorList *p, int tab);
typedef struct Dz1TcpSocketServerTaskEnv
{
	void *tSelf;
	AcceptorList *acceptors;
	ReceiverList *receivers;
} Dz1TcpSocketServerTaskEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSocketServerTaskEnv *Dz1TcpSocketServerTaskEnv_new(
			void *tSelf, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerTaskEnv_del(Dz1TcpSocketServerTaskEnv *p);
static __inline__ void Dz1TcpSocketServerTaskEnv_delAndSetNull(void *ptr)
{
	Dz1TcpSocketServerTaskEnv **p = (Dz1TcpSocketServerTaskEnv **)ptr;
	Dz1TcpSocketServerTaskEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerTaskEnv_dump(Dz1TcpSocketServerTaskEnv *p, int tab);
#endif
