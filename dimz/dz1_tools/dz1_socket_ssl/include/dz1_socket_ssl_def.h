#ifndef _DZ1_TDC_DZ1_SOCKET_SSL_DEF_H_
#define _DZ1_TDC_DZ1_SOCKET_SSL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// dz1_socket_ssl
typedef struct dz1_socket_ssl
{
	s32_t		dummy;
} dz1_socket_ssl;

DZ1_CPPLINK DZ1_DLLPORT dz1_socket_ssl *dz1_socket_ssl_new(s32_t dummy, Dz1Error *err);
static __inline__ dz1_socket_ssl *dz1_socket_ssl_gen(Dz1Error *err) { return dz1_socket_ssl_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void dz1_socket_ssl_purge(dz1_socket_ssl *p);
DZ1_CPPLINK DZ1_DLLPORT void dz1_socket_ssl_del(dz1_socket_ssl *p);
static __inline__ void dz1_socket_ssl_delAndSetNull(void *ptr)
{
	dz1_socket_ssl **p = (dz1_socket_ssl **)ptr;
	if (p) { dz1_socket_ssl_del(*p); *p = NULL; }
}
// dz1_socket_ssl
////////////////////////////////////////////////////////////////////////////////

#endif
