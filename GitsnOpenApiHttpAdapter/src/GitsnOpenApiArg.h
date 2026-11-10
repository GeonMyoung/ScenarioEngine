#ifndef _DZ1_TDC_GITSN_OPEN_API_ARG_H_
#define _DZ1_TDC_GITSN_OPEN_API_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiArg
typedef struct GitsnOpenApiArg
{
	Dz1SockAddr							*listen_addr;
	str_t								 servant_name_u8;
	GitsnOpenApiCallback				 http_cb;
	void								*http_cb_ptr;
	GitsnOpenApiException				 exceptionProc;
	void								*exceptionArg;
	u32_t								 server_idle_timeout_ms;
	bool_t								 advertise_keep_alive;
	GitsnOpenApiConnectionCallback		 connection_cb;
	void								*connection_cb_arg;
} GitsnOpenApiArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiArg *GitsnOpenApiArg_new(Dz1SockAddr *listen_addr, 
															 str_t servant_name_u8, 
															 GitsnOpenApiCallback http_cb, 
															 void *http_cb_ptr, 
															 GitsnOpenApiException exceptionProc, 
															 void *exceptionArg, Dz1Error *err);
static __inline__ GitsnOpenApiArg *GitsnOpenApiArg_gen(Dz1Error *err) { return GitsnOpenApiArg_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiArg_purge(GitsnOpenApiArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiArg_del(GitsnOpenApiArg *p);
static __inline__ void GitsnOpenApiArg_delAndSetNull(void *ptr)
{
	GitsnOpenApiArg **p = (GitsnOpenApiArg **)ptr;
	if (p) { GitsnOpenApiArg_del(*p); *p = NULL; }
}
// GitsnOpenApiArg
////////////////////////////////////////////////////////////////////////////////

#endif
