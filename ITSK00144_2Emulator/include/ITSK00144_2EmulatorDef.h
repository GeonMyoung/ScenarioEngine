#ifndef _DZ1_TDC_I_T_S_K00144_2_EMULATOR_DEF_H_
#define _DZ1_TDC_I_T_S_K00144_2_EMULATOR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorException
typedef void (*ITSK001442EmulatorException)(void *exceptionArg, Dz1Error *reason);
// ITSK001442EmulatorException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorDef
typedef struct ITSK001442EmulatorDef
{
	s32_t		dummy;
} ITSK001442EmulatorDef;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442EmulatorDef *ITSK001442EmulatorDef_new(s32_t dummy, Dz1Error *err);
static __inline__ ITSK001442EmulatorDef *ITSK001442EmulatorDef_gen(Dz1Error *err) { return ITSK001442EmulatorDef_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorDef_purge(ITSK001442EmulatorDef *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorDef_del(ITSK001442EmulatorDef *p);
static __inline__ void ITSK001442EmulatorDef_delAndSetNull(void *ptr)
{
	ITSK001442EmulatorDef **p = (ITSK001442EmulatorDef **)ptr;
	if (p) { ITSK001442EmulatorDef_del(*p); *p = NULL; }
}
// ITSK001442EmulatorDef
////////////////////////////////////////////////////////////////////////////////

#endif
