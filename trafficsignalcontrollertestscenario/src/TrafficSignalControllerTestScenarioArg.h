#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ARG_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioDef.h"
#include "TrafficSignalControllerTestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioArg
typedef struct TrafficSignalControllerTestScenarioArg
{
	void											*tMain;
	Dz1Str											 testScenario;
	TrafficSignalControllerTestScenarioException	 exceptionProc;
	void											*exceptionArg;
} TrafficSignalControllerTestScenarioArg;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestScenarioArg *TrafficSignalControllerTestScenarioArg_new(void *tMain, 
																										   Dz1Str testScenario, 
																										   TrafficSignalControllerTestScenarioException exceptionProc, 
																										   void *exceptionArg, Dz1Error *err);
static __inline__ TrafficSignalControllerTestScenarioArg *TrafficSignalControllerTestScenarioArg_gen(Dz1Error *err) { return TrafficSignalControllerTestScenarioArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioArg_purge(TrafficSignalControllerTestScenarioArg *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioArg_del(TrafficSignalControllerTestScenarioArg *p);
static __inline__ void TrafficSignalControllerTestScenarioArg_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestScenarioArg **p = (TrafficSignalControllerTestScenarioArg **)ptr;
	if (p) { TrafficSignalControllerTestScenarioArg_del(*p); *p = NULL; }
}
// TrafficSignalControllerTestScenarioArg
////////////////////////////////////////////////////////////////////////////////

#endif
