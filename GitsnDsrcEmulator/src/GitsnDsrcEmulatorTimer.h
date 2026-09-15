#ifndef _DZ1_TDC_GITSN_DSRC_EMULATOR_TIMER_H_
#define _DZ1_TDC_GITSN_DSRC_EMULATOR_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorTimer
typedef struct GitsnDsrcEmulatorTimer
{
	u32_t		id;
} GitsnDsrcEmulatorTimer;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorTimer *GitsnDsrcEmulatorTimer_new(u32_t id, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorTimer *GitsnDsrcEmulatorTimer_gen(Dz1Error *err) { return GitsnDsrcEmulatorTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorTimer_purge(GitsnDsrcEmulatorTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorTimer_del(GitsnDsrcEmulatorTimer *p);
static __inline__ void GitsnDsrcEmulatorTimer_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorTimer **p = (GitsnDsrcEmulatorTimer **)ptr;
	if (p) { GitsnDsrcEmulatorTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorTimer_dump(GitsnDsrcEmulatorTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDsrcEmulatorTimer_cmp(GitsnDsrcEmulatorTimer *a, GitsnDsrcEmulatorTimer *b); 
// GitsnDsrcEmulatorTimer
////////////////////////////////////////////////////////////////////////////////

#endif
