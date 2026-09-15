#ifndef DZ1_INET_FTP_TIMER_UTIL_H_LOCAL
#define DZ1_INET_FTP_TIMER_UTIL_H_LOCAL

#include <dz1_task_timer.h>
#include "dz1_inet_ftp_timer.h"

#define DZ1_INET_FTP_PKT_WAIT			0x00000001

DZ1_CPPLINK Dz1Error Dz1InetFtpTimer_reg(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local, u32_t timerID,
										 u64_t duration_us, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Dz1InetFtpTimer_dereg(void *timer, Dz1InetFtpSession *session, u32_t timerID);

DZ1_CPPLINK Dz1Error Dz1InetFtpTimer_resetMsgWait(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local);
DZ1_CPPLINK void Dz1InetFtpTimer_clearMsgWait(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local);

#endif

