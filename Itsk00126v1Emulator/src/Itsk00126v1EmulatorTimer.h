#ifndef _DZ1_TDC_ITSK00126V1_EMULATOR_TIMER_H_
#define _DZ1_TDC_ITSK00126V1_EMULATOR_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorTimer
typedef struct Itsk00126V1EmulatorTimer
{
	u32_t		id;
} Itsk00126V1EmulatorTimer;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1EmulatorTimer *Itsk00126V1EmulatorTimer_new(u32_t id, Dz1Error *err);
static __inline__ Itsk00126V1EmulatorTimer *Itsk00126V1EmulatorTimer_gen(Dz1Error *err) { return Itsk00126V1EmulatorTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorTimer_purge(Itsk00126V1EmulatorTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorTimer_del(Itsk00126V1EmulatorTimer *p);
static __inline__ void Itsk00126V1EmulatorTimer_delAndSetNull(void *ptr)
{
	Itsk00126V1EmulatorTimer **p = (Itsk00126V1EmulatorTimer **)ptr;
	if (p) { Itsk00126V1EmulatorTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorTimer_dump(Itsk00126V1EmulatorTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126V1EmulatorTimer_cmp(Itsk00126V1EmulatorTimer *a, Itsk00126V1EmulatorTimer *b); 
// Itsk00126V1EmulatorTimer
////////////////////////////////////////////////////////////////////////////////

#endif
