#ifndef _DZ1_TDC_DZ1_TCP_SOCKET_SERVER_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_SOCKET_SERVER_MSGS_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_sock_addr.h>

#include "libdz1_support.h"

typedef struct Dz1TcpSocketServerConnected
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1TcpClientSocket *sock;
} Dz1TcpSocketServerConnected;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSocketServerConnected *Dz1TcpSocketServerConnected_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			Dz1TcpClientSocket *sock, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerConnected_del(Dz1TcpSocketServerConnected *p);
static __inline__ void Dz1TcpSocketServerConnected_delAndSetNull(void *ptr)
{
	Dz1TcpSocketServerConnected **p = (Dz1TcpSocketServerConnected **)ptr;
	Dz1TcpSocketServerConnected_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerConnected_dump(Dz1TcpSocketServerConnected *p, int tab);
typedef struct Dz1TcpSocketServerReceived
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1Binary *pkt;
} Dz1TcpSocketServerReceived;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSocketServerReceived *Dz1TcpSocketServerReceived_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			Dz1Binary *pkt, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerReceived_del(Dz1TcpSocketServerReceived *p);
static __inline__ void Dz1TcpSocketServerReceived_delAndSetNull(void *ptr)
{
	Dz1TcpSocketServerReceived **p = (Dz1TcpSocketServerReceived **)ptr;
	Dz1TcpSocketServerReceived_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerReceived_dump(Dz1TcpSocketServerReceived *p, int tab);
typedef struct Dz1TcpSocketServerOpen
{
	u16_t port;
} Dz1TcpSocketServerOpen;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSocketServerOpen *Dz1TcpSocketServerOpen_new(u16_t port, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerOpen_del(Dz1TcpSocketServerOpen *p);
static __inline__ void Dz1TcpSocketServerOpen_delAndSetNull(void *ptr)
{
	Dz1TcpSocketServerOpen **p = (Dz1TcpSocketServerOpen **)ptr;
	Dz1TcpSocketServerOpen_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSocketServerOpen_dump(Dz1TcpSocketServerOpen *p, int tab);
#endif
