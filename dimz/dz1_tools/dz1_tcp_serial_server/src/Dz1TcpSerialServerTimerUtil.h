#ifndef DZ1_TCP_SERIAL_SERVER_TIMER_UTIL_H_LOCAL
#define DZ1_TCP_SERIAL_SERVER_TIMER_UTIL_H_LOCAL
#include <dz1_task.h>
#include "Dz1TcpSerialServerTimer.h"

DZ1_CPPLINK Dz1Error Dz1TcpSerialServerTimer_set(void *timer, Dz1TcpSerialServerTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerTimer_update(void *timer, Dz1TcpSerialServerTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Dz1TcpSerialServerTimer_clr(void *timer, Dz1TcpSerialServerTimer *key);

#endif
