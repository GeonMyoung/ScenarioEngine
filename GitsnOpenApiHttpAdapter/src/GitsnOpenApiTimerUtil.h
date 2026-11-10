#ifndef GITSN_OPEN_API_TIMER_UTIL_H_LOCAL
#define GITSN_OPEN_API_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "GitsnOpenApiTimer.h"

DZ1_CPPLINK Dz1Error GitsnOpenApiTimer_set(void *timer, GitsnOpenApiTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error GitsnOpenApiTimer_update(void *timer, GitsnOpenApiTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void GitsnOpenApiTimer_clr(void *timer, GitsnOpenApiTimer *key);

#endif	// GITSN_OPEN_API_TIMER_UTIL_H_LOCAL
