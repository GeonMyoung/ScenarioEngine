#ifndef ITSK00126_V1_EMULATOR_TIMER_UTIL_H_LOCAL
#define ITSK00126_V1_EMULATOR_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "Itsk00126v1EmulatorTimer.h"

DZ1_CPPLINK Dz1Error Itsk00126V1EmulatorTimer_set(void *timer, Itsk00126V1EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error Itsk00126V1EmulatorTimer_update(void *timer, Itsk00126V1EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Itsk00126V1EmulatorTimer_clr(void *timer, Itsk00126V1EmulatorTimer *key);

#endif	// ITSK00126_V1_EMULATOR_TIMER_UTIL_H_LOCAL
