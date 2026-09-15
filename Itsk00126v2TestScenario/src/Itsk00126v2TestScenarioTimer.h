#ifndef _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_TIMER_H_
#define _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V2TestScenarioTimer
typedef struct Itsk00126V2TestScenarioTimer
{
	u32_t		id;
} Itsk00126V2TestScenarioTimer;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V2TestScenarioTimer *Itsk00126V2TestScenarioTimer_new(u32_t id, Dz1Error *err);
static __inline__ Itsk00126V2TestScenarioTimer *Itsk00126V2TestScenarioTimer_gen(Dz1Error *err) { return Itsk00126V2TestScenarioTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioTimer_purge(Itsk00126V2TestScenarioTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioTimer_del(Itsk00126V2TestScenarioTimer *p);
static __inline__ void Itsk00126V2TestScenarioTimer_delAndSetNull(void *ptr)
{
	Itsk00126V2TestScenarioTimer **p = (Itsk00126V2TestScenarioTimer **)ptr;
	if (p) { Itsk00126V2TestScenarioTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioTimer_dump(Itsk00126V2TestScenarioTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126V2TestScenarioTimer_cmp(Itsk00126V2TestScenarioTimer *a, Itsk00126V2TestScenarioTimer *b); 
// Itsk00126V2TestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

#endif
