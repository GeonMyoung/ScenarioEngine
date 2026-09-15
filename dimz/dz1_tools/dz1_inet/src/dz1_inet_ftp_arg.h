#ifndef _DZ1_TDC_DZ1_INET_FTP_ARG_H_
#define _DZ1_TDC_DZ1_INET_FTP_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpArg
typedef struct Dz1InetFtpArg
{
	str_t					 localCharSetName;
	Dz1InetFtpException		 func;
	void					*ptr;
} Dz1InetFtpArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpArg *Dz1InetFtpArg_new(str_t localCharSetName, 
														 Dz1InetFtpException func, 
														 void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpArg *Dz1InetFtpArg_gen(Dz1Error *err) { return Dz1InetFtpArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpArg_purge(Dz1InetFtpArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpArg_del(Dz1InetFtpArg *p);
static __inline__ void Dz1InetFtpArg_delAndSetNull(void *ptr)
{
	Dz1InetFtpArg **p = (Dz1InetFtpArg **)ptr;
	if (p) { Dz1InetFtpArg_del(*p); *p = NULL; }
}
// Dz1InetFtpArg
////////////////////////////////////////////////////////////////////////////////

#endif
