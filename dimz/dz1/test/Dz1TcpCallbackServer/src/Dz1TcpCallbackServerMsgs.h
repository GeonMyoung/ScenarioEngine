#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_MSGS_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackServerDef.h"


typedef struct Dz1TcpCallbackServerMsgDefault
{
	u32_t *dummy;
} Dz1TcpCallbackServerMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerMsgDefault *Dz1TcpCallbackServerMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerMsgDefault *Dz1TcpCallbackServerMsgDefault_gen(Dz1Error *err) { return Dz1TcpCallbackServerMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgDefault_del(Dz1TcpCallbackServerMsgDefault *p);
static __inline__ void Dz1TcpCallbackServerMsgDefault_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerMsgDefault **p = (Dz1TcpCallbackServerMsgDefault **)ptr;
	Dz1TcpCallbackServerMsgDefault_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgDefault_dump(Dz1TcpCallbackServerMsgDefault *p, int tab);

typedef struct Dz1TcpCallbackServerMsgConnected
{
	Dz1SockAddr        *peer;
	Dz1SockAddr        *local;
	Dz1TcpClientSocket *sock;
} Dz1TcpCallbackServerMsgConnected;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerMsgConnected *Dz1TcpCallbackServerMsgConnected_new(Dz1SockAddr *peer, 
																							   Dz1SockAddr *local, 
																							   Dz1TcpClientSocket *sock, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerMsgConnected *Dz1TcpCallbackServerMsgConnected_gen(Dz1Error *err) { return Dz1TcpCallbackServerMsgConnected_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgConnected_del(Dz1TcpCallbackServerMsgConnected *p);
static __inline__ void Dz1TcpCallbackServerMsgConnected_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerMsgConnected **p = (Dz1TcpCallbackServerMsgConnected **)ptr;
	Dz1TcpCallbackServerMsgConnected_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgConnected_dump(Dz1TcpCallbackServerMsgConnected *p, int tab);

typedef struct Dz1TcpCallbackServerMsgReceived
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1Binary   *packet;
} Dz1TcpCallbackServerMsgReceived;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerMsgReceived *Dz1TcpCallbackServerMsgReceived_new(Dz1SockAddr *peer, 
																							 Dz1SockAddr *local, 
																							 Dz1Binary *packet, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerMsgReceived *Dz1TcpCallbackServerMsgReceived_gen(Dz1Error *err) { return Dz1TcpCallbackServerMsgReceived_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgReceived_del(Dz1TcpCallbackServerMsgReceived *p);
static __inline__ void Dz1TcpCallbackServerMsgReceived_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerMsgReceived **p = (Dz1TcpCallbackServerMsgReceived **)ptr;
	Dz1TcpCallbackServerMsgReceived_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgReceived_dump(Dz1TcpCallbackServerMsgReceived *p, int tab);

typedef struct Dz1TcpCallbackServerMsgSent
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpCallbackServerMsgSent;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerMsgSent *Dz1TcpCallbackServerMsgSent_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerMsgSent *Dz1TcpCallbackServerMsgSent_gen(Dz1Error *err) { return Dz1TcpCallbackServerMsgSent_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgSent_del(Dz1TcpCallbackServerMsgSent *p);
static __inline__ void Dz1TcpCallbackServerMsgSent_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerMsgSent **p = (Dz1TcpCallbackServerMsgSent **)ptr;
	Dz1TcpCallbackServerMsgSent_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerMsgSent_dump(Dz1TcpCallbackServerMsgSent *p, int tab);

#endif
