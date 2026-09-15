#ifndef _DZ1_TDC_DZ1_INET_FTP_TIMER_H_
#define _DZ1_TDC_DZ1_INET_FTP_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTimer
typedef struct Dz1InetFtpTimer
{
	Dz1SockAddr		*peer;
	Dz1SockAddr		*local;
	u32_t			 id;
} Dz1InetFtpTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTimer *Dz1InetFtpTimer_new(Dz1SockAddr *peer, 
															 Dz1SockAddr *local, 
															 u32_t id, Dz1Error *err);
static __inline__ Dz1InetFtpTimer *Dz1InetFtpTimer_gen(Dz1Error *err) { return Dz1InetFtpTimer_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTimer_purge(Dz1InetFtpTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTimer_del(Dz1InetFtpTimer *p);
static __inline__ void Dz1InetFtpTimer_delAndSetNull(void *ptr)
{
	Dz1InetFtpTimer **p = (Dz1InetFtpTimer **)ptr;
	if (p) { Dz1InetFtpTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTimer_dump(Dz1InetFtpTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1InetFtpTimer_cmp(Dz1InetFtpTimer *a, Dz1InetFtpTimer *b); 
// Dz1InetFtpTimer
////////////////////////////////////////////////////////////////////////////////

#endif
