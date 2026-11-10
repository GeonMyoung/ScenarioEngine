#ifndef _DZ1_TDC_GITSN_OPEN_API_MSGS_H_
#define _DZ1_TDC_GITSN_OPEN_API_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiMsgDefault
typedef struct GitsnOpenApiMsgDefault
{
	u32_t		*dummy;
} GitsnOpenApiMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiMsgDefault *GitsnOpenApiMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ GitsnOpenApiMsgDefault *GitsnOpenApiMsgDefault_gen(Dz1Error *err) { return GitsnOpenApiMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsgDefault_purge(GitsnOpenApiMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsgDefault_del(GitsnOpenApiMsgDefault *p);
static __inline__ void GitsnOpenApiMsgDefault_delAndSetNull(void *ptr)
{
	GitsnOpenApiMsgDefault **p = (GitsnOpenApiMsgDefault **)ptr;
	if (p) { GitsnOpenApiMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsgDefault_dump(GitsnOpenApiMsgDefault *p, int tab);
// GitsnOpenApiMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
