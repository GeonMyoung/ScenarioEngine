#ifndef _DZ1_TDC_ITSK00126V1_EMULATOR_DEF_H_
#define _DZ1_TDC_ITSK00126V1_EMULATOR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Itsk00126v1TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorException
typedef void (*Itsk00126V1EmulatorException)(void *exceptionArg, Dz1Error *reason);
// Itsk00126V1EmulatorException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorDef
typedef struct Itsk00126V1EmulatorDef
{
	s32_t		dummy;
} Itsk00126V1EmulatorDef;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1EmulatorDef *Itsk00126V1EmulatorDef_new(s32_t dummy, Dz1Error *err);
static __inline__ Itsk00126V1EmulatorDef *Itsk00126V1EmulatorDef_gen(Dz1Error *err) { return Itsk00126V1EmulatorDef_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorDef_purge(Itsk00126V1EmulatorDef *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorDef_del(Itsk00126V1EmulatorDef *p);
static __inline__ void Itsk00126V1EmulatorDef_delAndSetNull(void *ptr)
{
	Itsk00126V1EmulatorDef **p = (Itsk00126V1EmulatorDef **)ptr;
	if (p) { Itsk00126V1EmulatorDef_del(*p); *p = NULL; }
}
// Itsk00126V1EmulatorDef
////////////////////////////////////////////////////////////////////////////////

#endif
