#ifndef DZ1_TCP_CALLBACK_CLIENT_TIMER_UTIL_H_LOCAL
#define DZ1_TCP_CALLBACK_CLIENT_TIMER_UTIL_H_LOCAL

#include "Dz1TcpCallbackClientEnv.h"
#include "Dz1TcpCallbackClientTimer.h"

#define SESSION_CHK				0
#define TX_TIMEOUT				1
#define TERM_TIMEOUT			2

DZ1_CPPLINK Dz1Error Dz1TcpCallbackClientTimer_reg(void *timer, u32_t id, Dz1SockAddr *peer, Dz1SockAddr *local,
												   u64_t duration_us, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Dz1TcpCallbackClientTimer_dereg(void *timer, u32_t id, Dz1SockAddr *peer, Dz1SockAddr *local);

DZ1_CPPLINK Dz1Error	_reg_term_timer(void *timer, Dz1TcpCallbackSession *session, u32_t dur_sec);
DZ1_CPPLINK void		_dereg_term_timer(void *timer, Dz1TcpCallbackSession *session);

DZ1_CPPLINK Dz1Error	_reg_retry_timer(void *timer, Dz1TcpCallbackSession *session);
DZ1_CPPLINK void		_dereg_retry_timer(void *timer, Dz1TcpCallbackSession *session);

DZ1_CPPLINK Dz1Error	_reg_session_check(void *timer);

#endif