#ifndef _DZ1_TDC_DZ1_SYSLOG_ARG_H_
#define _DZ1_TDC_DZ1_SYSLOG_ARG_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>


typedef struct Dz1SysLogArg
{
	s32_t  dummy;
} Dz1SysLogArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1SysLogArg *Dz1SysLogArg_new(s32_t dummy, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogArg_del(Dz1SysLogArg *p);
static __inline__ void Dz1SysLogArg_delAndSetNull(void *ptr)
{
	Dz1SysLogArg **p = (Dz1SysLogArg **)ptr;
	Dz1SysLogArg_del(*p); *p = NULL;
}

#endif
