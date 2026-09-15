#ifndef GITSN_DSRC_EMULATOR_TIMER_UTIL_H_LOCAL
#define GITSN_DSRC_EMULATOR_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "GitsnDsrcEmulatorTimer.h"

DZ1_CPPLINK Dz1Error GitsnDsrcEmulatorTimer_set(void *timer, GitsnDsrcEmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error GitsnDsrcEmulatorTimer_update(void *timer, GitsnDsrcEmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void GitsnDsrcEmulatorTimer_clr(void *timer, GitsnDsrcEmulatorTimer *key);

#endif	// GITSN_DSRC_EMULATOR_TIMER_UTIL_H_LOCAL
