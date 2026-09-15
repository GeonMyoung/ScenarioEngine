#ifndef _DZ1_TDC_DZ1_SYSLOG_MSGS_H_
#define _DZ1_TDC_DZ1_SYSLOG_MSGS_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>


typedef struct Dz1SysLogMsg
{
	u32_t  dummy;
} Dz1SysLogMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SysLogMsg *Dz1SysLogMsg_new(u32_t dummy, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogMsg_del(Dz1SysLogMsg *p);
static __inline__ void Dz1SysLogMsg_delAndSetNull(void *ptr)
{
	Dz1SysLogMsg **p = (Dz1SysLogMsg **)ptr;
	Dz1SysLogMsg_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogMsg_dump(Dz1SysLogMsg *p, int tab);

#endif
