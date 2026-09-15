#ifndef DZ1_TCP_CALLBACK_SERVER_TIMER_UTIL_H_LOCAL
#define DZ1_TCP_CALLBACK_SERVER_TIMER_UTIL_H_LOCAL

#include "Dz1TcpCallbackServerTimer.h"

DZ1_CPPLINK Dz1Error _reg_session_term_timer(void *timer, Dz1TcpCallbackSession *node, u32_t timeout_sec);
DZ1_CPPLINK Dz1Error _reg_summary_timer(void *timer);

#endif
