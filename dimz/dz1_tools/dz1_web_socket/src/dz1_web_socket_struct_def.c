////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_web_socket_struct_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockInitInfo
Dz1WebSockInitInfo *Dz1WebSockInitInfo_new(Dz1WebSocketScheme scheme, 
										   str_t host_u8, 
										   u16_t port, 
										   str_t path_u8, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockInitInfo *__internal_ret = (Dz1WebSockInitInfo *)Dz1Calloc(sizeof(Dz1WebSockInitInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSockInitInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (host_u8 && (__internal_ret->host_u8 = dz1_built_in_str_clone(host_u8, errp)) == NULL) ERR_OUT(errp);
		else if (path_u8 && (__internal_ret->path_u8 = dz1_built_in_str_clone(path_u8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->scheme = scheme;
			__internal_ret->port = port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockInitInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSockInitInfo_purge(Dz1WebSockInitInfo *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->host_u8);
	dz1_built_in_str_del(p->path_u8);
}

void Dz1WebSockInitInfo_del(Dz1WebSockInitInfo *p)
{
	if (p == NULL) return;
	Dz1WebSockInitInfo_purge(p);
	Dz1Free(p);
}

// Dz1WebSockInitInfo
////////////////////////////////////////////////////////////////////////////////

