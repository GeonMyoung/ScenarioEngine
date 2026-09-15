#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_TIMER_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioTimer
typedef struct ITSK001442TestScenarioTimer
{
	u32_t		id;
} ITSK001442TestScenarioTimer;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442TestScenarioTimer *ITSK001442TestScenarioTimer_new(u32_t id, Dz1Error *err);
static __inline__ ITSK001442TestScenarioTimer *ITSK001442TestScenarioTimer_gen(Dz1Error *err) { return ITSK001442TestScenarioTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioTimer_purge(ITSK001442TestScenarioTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioTimer_del(ITSK001442TestScenarioTimer *p);
static __inline__ void ITSK001442TestScenarioTimer_delAndSetNull(void *ptr)
{
	ITSK001442TestScenarioTimer **p = (ITSK001442TestScenarioTimer **)ptr;
	if (p) { ITSK001442TestScenarioTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioTimer_dump(ITSK001442TestScenarioTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK001442TestScenarioTimer_cmp(ITSK001442TestScenarioTimer *a, ITSK001442TestScenarioTimer *b); 
// ITSK001442TestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

#endif
