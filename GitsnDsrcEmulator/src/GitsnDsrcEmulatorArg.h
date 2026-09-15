#ifndef _DZ1_TDC_GITSN_DSRC_EMULATOR_ARG_H_
#define _DZ1_TDC_GITSN_DSRC_EMULATOR_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorArg
typedef struct GitsnDsrcEmulatorArg
{
	GitsnDsrcEmulatorException		 exceptionProc;
	void							*exceptionArg;
} GitsnDsrcEmulatorArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorArg *GitsnDsrcEmulatorArg_new(GitsnDsrcEmulatorException exceptionProc, 
																	   void *exceptionArg, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorArg *GitsnDsrcEmulatorArg_gen(Dz1Error *err) { return GitsnDsrcEmulatorArg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorArg_purge(GitsnDsrcEmulatorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorArg_del(GitsnDsrcEmulatorArg *p);
static __inline__ void GitsnDsrcEmulatorArg_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorArg **p = (GitsnDsrcEmulatorArg **)ptr;
	if (p) { GitsnDsrcEmulatorArg_del(*p); *p = NULL; }
}
// GitsnDsrcEmulatorArg
////////////////////////////////////////////////////////////////////////////////

#endif
