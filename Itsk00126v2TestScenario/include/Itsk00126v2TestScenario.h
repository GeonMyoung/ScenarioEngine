#ifndef ITSK00126_V2_TEST_SCENARIO_H
#define ITSK00126_V2_TEST_SCENARIO_H

#include <Itsk00126v2TestScenarioDef.h>

DZ1_CPPLINK void *Itsk00126V2TestScenario_new(void *tMain, Dz1Str testScenario, Itsk00126V2TestScenarioException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Itsk00126V2TestScenario_del(void *task);

#endif // ITSK00126_V2_TEST_SCENARIO
