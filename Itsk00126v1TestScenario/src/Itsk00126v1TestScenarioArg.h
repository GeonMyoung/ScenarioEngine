#ifndef _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_ARG_H_
#define _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioArg
typedef struct Itsk00126V1TestScenarioArg
{
	void								*tMain;
	Dz1Str								 testScenario;
	Itsk00126V1TestScenarioException	 exceptionProc;
	void								*exceptionArg;
} Itsk00126V1TestScenarioArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1TestScenarioArg *Itsk00126V1TestScenarioArg_new(void *tMain, 
																				   Dz1Str testScenario, 
																				   Itsk00126V1TestScenarioException exceptionProc, 
																				   void *exceptionArg, Dz1Error *err);
static __inline__ Itsk00126V1TestScenarioArg *Itsk00126V1TestScenarioArg_gen(Dz1Error *err) { return Itsk00126V1TestScenarioArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioArg_purge(Itsk00126V1TestScenarioArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioArg_del(Itsk00126V1TestScenarioArg *p);
static __inline__ void Itsk00126V1TestScenarioArg_delAndSetNull(void *ptr)
{
	Itsk00126V1TestScenarioArg **p = (Itsk00126V1TestScenarioArg **)ptr;
	if (p) { Itsk00126V1TestScenarioArg_del(*p); *p = NULL; }
}
// Itsk00126V1TestScenarioArg
////////////////////////////////////////////////////////////////////////////////

#endif
