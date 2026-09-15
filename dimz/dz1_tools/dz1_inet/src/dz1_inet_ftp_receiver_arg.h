#ifndef _DZ1_TDC_DZ1_INET_FTP_RECEIVER_ARG_H_
#define _DZ1_TDC_DZ1_INET_FTP_RECEIVER_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpReceiverArg
typedef struct Dz1InetFtpReceiverArg
{
	void	*tControl;
} Dz1InetFtpReceiverArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpReceiverArg *Dz1InetFtpReceiverArg_new(void *tControl, Dz1Error *err);
static __inline__ Dz1InetFtpReceiverArg *Dz1InetFtpReceiverArg_gen(Dz1Error *err) { return Dz1InetFtpReceiverArg_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpReceiverArg_purge(Dz1InetFtpReceiverArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpReceiverArg_del(Dz1InetFtpReceiverArg *p);
static __inline__ void Dz1InetFtpReceiverArg_delAndSetNull(void *ptr)
{
	Dz1InetFtpReceiverArg **p = (Dz1InetFtpReceiverArg **)ptr;
	if (p) { Dz1InetFtpReceiverArg_del(*p); *p = NULL; }
}
// Dz1InetFtpReceiverArg
////////////////////////////////////////////////////////////////////////////////

#endif
