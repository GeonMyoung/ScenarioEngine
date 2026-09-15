#ifndef _DZ1_TDC_I_T_S_K00144_2_EMULATOR_TIMER_H_
#define _DZ1_TDC_I_T_S_K00144_2_EMULATOR_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorTimer
typedef struct ITSK001442EmulatorTimer
{
	u32_t		id;
} ITSK001442EmulatorTimer;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442EmulatorTimer *ITSK001442EmulatorTimer_new(u32_t id, Dz1Error *err);
static __inline__ ITSK001442EmulatorTimer *ITSK001442EmulatorTimer_gen(Dz1Error *err) { return ITSK001442EmulatorTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorTimer_purge(ITSK001442EmulatorTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorTimer_del(ITSK001442EmulatorTimer *p);
static __inline__ void ITSK001442EmulatorTimer_delAndSetNull(void *ptr)
{
	ITSK001442EmulatorTimer **p = (ITSK001442EmulatorTimer **)ptr;
	if (p) { ITSK001442EmulatorTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorTimer_dump(ITSK001442EmulatorTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK001442EmulatorTimer_cmp(ITSK001442EmulatorTimer *a, ITSK001442EmulatorTimer *b); 
// ITSK001442EmulatorTimer
////////////////////////////////////////////////////////////////////////////////

#endif
