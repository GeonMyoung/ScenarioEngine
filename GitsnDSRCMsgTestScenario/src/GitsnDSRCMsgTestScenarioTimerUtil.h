#ifndef GITSN_DSRCMSG_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
#define GITSN_DSRCMSG_TEST_SCENARIO_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "GitsnDSRCMsgTestScenarioTimer.h"

DZ1_CPPLINK Dz1Error GitsnDSRCMsgTestScenarioTimer_set(void *timer, GitsnDSRCMsgTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error GitsnDSRCMsgTestScenarioTimer_update(void *timer, GitsnDSRCMsgTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void GitsnDSRCMsgTestScenarioTimer_clr(void *timer, GitsnDSRCMsgTestScenarioTimer *key);

#endif	// GITSN_DSRCMSG_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
