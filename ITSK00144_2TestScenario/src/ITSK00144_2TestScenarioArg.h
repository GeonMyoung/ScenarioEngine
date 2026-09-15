#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_ARG_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioArg
typedef struct ITSK001442TestScenarioArg
{
	void								*tMain;
	Dz1Str								 testScenario;
	ITSK001442TestScenarioException		 exceptionProc;
	void								*exceptionArg;
} ITSK001442TestScenarioArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442TestScenarioArg *ITSK001442TestScenarioArg_new(void *tMain, 
																				 Dz1Str testScenario, 
																				 ITSK001442TestScenarioException exceptionProc, 
																				 void *exceptionArg, Dz1Error *err);
static __inline__ ITSK001442TestScenarioArg *ITSK001442TestScenarioArg_gen(Dz1Error *err) { return ITSK001442TestScenarioArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioArg_purge(ITSK001442TestScenarioArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioArg_del(ITSK001442TestScenarioArg *p);
static __inline__ void ITSK001442TestScenarioArg_delAndSetNull(void *ptr)
{
	ITSK001442TestScenarioArg **p = (ITSK001442TestScenarioArg **)ptr;
	if (p) { ITSK001442TestScenarioArg_del(*p); *p = NULL; }
}
// ITSK001442TestScenarioArg
////////////////////////////////////////////////////////////////////////////////

#endif
