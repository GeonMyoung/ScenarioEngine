#ifndef _DZ1_TDC_GITSN_DSRC_EMULATOR_MSGS_H_
#define _DZ1_TDC_GITSN_DSRC_EMULATOR_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorMsgDefault
typedef struct GitsnDsrcEmulatorMsgDefault
{
	u32_t		*dummy;
} GitsnDsrcEmulatorMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorMsgDefault *GitsnDsrcEmulatorMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorMsgDefault *GitsnDsrcEmulatorMsgDefault_gen(Dz1Error *err) { return GitsnDsrcEmulatorMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorMsgDefault_purge(GitsnDsrcEmulatorMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorMsgDefault_del(GitsnDsrcEmulatorMsgDefault *p);
static __inline__ void GitsnDsrcEmulatorMsgDefault_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorMsgDefault **p = (GitsnDsrcEmulatorMsgDefault **)ptr;
	if (p) { GitsnDsrcEmulatorMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorMsgDefault_dump(GitsnDsrcEmulatorMsgDefault *p, int tab);
// GitsnDsrcEmulatorMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
