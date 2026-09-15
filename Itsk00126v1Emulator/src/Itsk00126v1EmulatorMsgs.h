#ifndef _DZ1_TDC_ITSK00126V1_EMULATOR_MSGS_H_
#define _DZ1_TDC_ITSK00126V1_EMULATOR_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorMsgDefault
typedef struct Itsk00126V1EmulatorMsgDefault
{
	u32_t		*dummy;
} Itsk00126V1EmulatorMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1EmulatorMsgDefault *Itsk00126V1EmulatorMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Itsk00126V1EmulatorMsgDefault *Itsk00126V1EmulatorMsgDefault_gen(Dz1Error *err) { return Itsk00126V1EmulatorMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorMsgDefault_purge(Itsk00126V1EmulatorMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorMsgDefault_del(Itsk00126V1EmulatorMsgDefault *p);
static __inline__ void Itsk00126V1EmulatorMsgDefault_delAndSetNull(void *ptr)
{
	Itsk00126V1EmulatorMsgDefault **p = (Itsk00126V1EmulatorMsgDefault **)ptr;
	if (p) { Itsk00126V1EmulatorMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorMsgDefault_dump(Itsk00126V1EmulatorMsgDefault *p, int tab);
// Itsk00126V1EmulatorMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
