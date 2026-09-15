#ifndef _DZ1_TDC_DZ1_WEB_SOCKET_STRUCT_DEF_H_
#define _DZ1_TDC_DZ1_WEB_SOCKET_STRUCT_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_web_socket_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockInitInfo
typedef struct Dz1WebSockInitInfo
{
	Dz1WebSocketScheme		scheme;
	str_t					host_u8;
	u16_t					port;
	str_t					path_u8;
} Dz1WebSockInitInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockInitInfo *Dz1WebSockInitInfo_new(Dz1WebSocketScheme scheme, 
																   str_t host_u8, 
																   u16_t port, 
																   str_t path_u8, Dz1Error *err);
static __inline__ Dz1WebSockInitInfo *Dz1WebSockInitInfo_gen(Dz1Error *err) { return Dz1WebSockInitInfo_new(Dz1WebSocketScheme_max, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockInitInfo_purge(Dz1WebSockInitInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockInitInfo_del(Dz1WebSockInitInfo *p);
static __inline__ void Dz1WebSockInitInfo_delAndSetNull(void *ptr)
{
	Dz1WebSockInitInfo **p = (Dz1WebSockInitInfo **)ptr;
	if (p) { Dz1WebSockInitInfo_del(*p); *p = NULL; }
}
// Dz1WebSockInitInfo
////////////////////////////////////////////////////////////////////////////////

#endif
