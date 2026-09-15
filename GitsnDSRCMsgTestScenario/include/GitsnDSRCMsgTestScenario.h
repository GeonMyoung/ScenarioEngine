#ifndef GITSN_DSRCMSG_TEST_SCENARIO_H
#define GITSN_DSRCMSG_TEST_SCENARIO_H

#include <GitsnDSRCMsgTestScenarioDef.h>

DZ1_CPPLINK void *GitsnDSRCMsgTestScenario_new(void *tMain, Dz1Str testScenario, GitsnDSRCMsgTestScenarioException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void GitsnDSRCMsgTestScenario_del(void *task);

#endif // GITSN_DSRCMSG_TEST_SCENARIO
