#ifndef _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_ARG_H_
#define _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V2TestScenarioArg
typedef struct Itsk00126V2TestScenarioArg
{
	void								*tMain;
	Dz1Str								 testScenario;
	Itsk00126V2TestScenarioException	 exceptionProc;
	void								*exceptionArg;
} Itsk00126V2TestScenarioArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V2TestScenarioArg *Itsk00126V2TestScenarioArg_new(void *tMain, 
																				   Dz1Str testScenario, 
																				   Itsk00126V2TestScenarioException exceptionProc, 
																				   void *exceptionArg, Dz1Error *err);
static __inline__ Itsk00126V2TestScenarioArg *Itsk00126V2TestScenarioArg_gen(Dz1Error *err) { return Itsk00126V2TestScenarioArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioArg_purge(Itsk00126V2TestScenarioArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioArg_del(Itsk00126V2TestScenarioArg *p);
static __inline__ void Itsk00126V2TestScenarioArg_delAndSetNull(void *ptr)
{
	Itsk00126V2TestScenarioArg **p = (Itsk00126V2TestScenarioArg **)ptr;
	if (p) { Itsk00126V2TestScenarioArg_del(*p); *p = NULL; }
}
// Itsk00126V2TestScenarioArg
////////////////////////////////////////////////////////////////////////////////

#endif
