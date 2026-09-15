#ifndef _DZ1_TDC_GITSN_DSRC_EMULATOR_DEF_H_
#define _DZ1_TDC_GITSN_DSRC_EMULATOR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorException
typedef void (*GitsnDsrcEmulatorException)(void *exceptionArg, Dz1Error *reason);
// GitsnDsrcEmulatorException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorDef
typedef struct GitsnDsrcEmulatorDef
{
	s32_t		dummy;
} GitsnDsrcEmulatorDef;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorDef *GitsnDsrcEmulatorDef_new(s32_t dummy, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorDef *GitsnDsrcEmulatorDef_gen(Dz1Error *err) { return GitsnDsrcEmulatorDef_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorDef_purge(GitsnDsrcEmulatorDef *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorDef_del(GitsnDsrcEmulatorDef *p);
static __inline__ void GitsnDsrcEmulatorDef_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorDef **p = (GitsnDsrcEmulatorDef **)ptr;
	if (p) { GitsnDsrcEmulatorDef_del(*p); *p = NULL; }
}
// GitsnDsrcEmulatorDef
////////////////////////////////////////////////////////////////////////////////

#endif
