#ifndef DZ1_TCP_SERIAL_CLIENT_TIMER_UTIL_H_LOCAL
#define DZ1_TCP_SERIAL_CLIENT_TIMER_UTIL_H_LOCAL
#include <dz1_task.h>
#include "Dz1TcpSerialClientTimer.h"

DZ1_CPPLINK Dz1Error Dz1TcpSerialClientTimer_set(void *timer, Dz1TcpSerialClientTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error Dz1TcpSerialClientTimer_update(void *timer, Dz1TcpSerialClientTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Dz1TcpSerialClientTimer_clr(void *timer, Dz1TcpSerialClientTimer *key);

#endif
