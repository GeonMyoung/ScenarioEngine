#ifndef ITSK00144_2_EMULATOR_TIMER_UTIL_H_LOCAL
#define ITSK00144_2_EMULATOR_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "ITSK00144_2EmulatorTimer.h"

#define ITSK_00144_2_TIMER_KEEPALIVE 0x00000001

DZ1_CPPLINK Dz1Error ITSK001442EmulatorTimer_set(void *timer, ITSK001442EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error ITSK001442EmulatorTimer_update(void *timer, ITSK001442EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void ITSK001442EmulatorTimer_clr(void *timer, ITSK001442EmulatorTimer *key);

#endif	// ITSK00144_2_EMULATOR_TIMER_UTIL_H_LOCAL
