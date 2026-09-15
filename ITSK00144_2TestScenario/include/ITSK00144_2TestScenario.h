#ifndef ITSK00144_2_TEST_SCENARIO_H
#define ITSK00144_2_TEST_SCENARIO_H

#include <ITSK00144_2TestScenarioDef.h>

DZ1_CPPLINK void *ITSK001442TestScenario_new(void *tMain, Dz1Str testScenario, ITSK001442TestScenarioException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void ITSK001442TestScenario_del(void *task);

#endif // ITSK00144_2_TEST_SCENARIO
