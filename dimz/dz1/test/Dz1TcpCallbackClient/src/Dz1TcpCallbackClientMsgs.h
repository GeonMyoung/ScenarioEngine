#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_MSGS_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackClientDef.h"

typedef struct Dz1TcpCallbackClientMsgDefault
{
	u32_t *dummy;
} Dz1TcpCallbackClientMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientMsgDefault *Dz1TcpCallbackClientMsgDefault_new(u32_t *dummy, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgDefault_del(Dz1TcpCallbackClientMsgDefault *p);
static __inline__ void Dz1TcpCallbackClientMsgDefault_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientMsgDefault **p = (Dz1TcpCallbackClientMsgDefault **)ptr;
	Dz1TcpCallbackClientMsgDefault_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgDefault_dump(Dz1TcpCallbackClientMsgDefault *p, int tab);

typedef struct Dz1TcpCallbackClientMsgReceived
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1Binary   *packet;
} Dz1TcpCallbackClientMsgReceived;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientMsgReceived *Dz1TcpCallbackClientMsgReceived_new(Dz1SockAddr *peer, 
																							 Dz1SockAddr *local, 
																							 Dz1Binary *packet, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgReceived_del(Dz1TcpCallbackClientMsgReceived *p);
static __inline__ void Dz1TcpCallbackClientMsgReceived_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientMsgReceived **p = (Dz1TcpCallbackClientMsgReceived **)ptr;
	Dz1TcpCallbackClientMsgReceived_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgReceived_dump(Dz1TcpCallbackClientMsgReceived *p, int tab);

typedef struct Dz1TcpCallbackClientMsgSent
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpCallbackClientMsgSent;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientMsgSent *Dz1TcpCallbackClientMsgSent_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgSent_del(Dz1TcpCallbackClientMsgSent *p);
static __inline__ void Dz1TcpCallbackClientMsgSent_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientMsgSent **p = (Dz1TcpCallbackClientMsgSent **)ptr;
	Dz1TcpCallbackClientMsgSent_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientMsgSent_dump(Dz1TcpCallbackClientMsgSent *p, int tab);

#endif
