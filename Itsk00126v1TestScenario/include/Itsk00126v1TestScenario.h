#ifndef ITSK00126_V1_TEST_SCENARIO_H
#define ITSK00126_V1_TEST_SCENARIO_H

#include <Itsk00126v1TestScenarioDef.h>

DZ1_CPPLINK void *Itsk00126V1TestScenario_new(void *tMain, Dz1Str testScenario, Itsk00126V1TestScenarioException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Itsk00126V1TestScenario_del(void *task);

#endif // ITSK00126_V1_TEST_SCENARIO
