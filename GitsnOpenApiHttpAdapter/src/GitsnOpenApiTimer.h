#ifndef _DZ1_TDC_GITSN_OPEN_API_TIMER_H_
#define _DZ1_TDC_GITSN_OPEN_API_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiTimer
typedef struct GitsnOpenApiTimer
{
	u32_t		id;
} GitsnOpenApiTimer;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiTimer *GitsnOpenApiTimer_new(u32_t id, Dz1Error *err);
static __inline__ GitsnOpenApiTimer *GitsnOpenApiTimer_gen(Dz1Error *err) { return GitsnOpenApiTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiTimer_purge(GitsnOpenApiTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiTimer_del(GitsnOpenApiTimer *p);
static __inline__ void GitsnOpenApiTimer_delAndSetNull(void *ptr)
{
	GitsnOpenApiTimer **p = (GitsnOpenApiTimer **)ptr;
	if (p) { GitsnOpenApiTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiTimer_dump(GitsnOpenApiTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnOpenApiTimer_cmp(GitsnOpenApiTimer *a, GitsnOpenApiTimer *b); 
// GitsnOpenApiTimer
////////////////////////////////////////////////////////////////////////////////

#endif
