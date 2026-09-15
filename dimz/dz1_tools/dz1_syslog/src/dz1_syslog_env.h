#ifndef _DZ1_TDC_DZ1_SYSLOG_ENV_H_
#define _DZ1_TDC_DZ1_SYSLOG_ENV_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>


typedef struct Dz1SysLogEnv
{
	s32_t  dummy;
} Dz1SysLogEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1SysLogEnv *Dz1SysLogEnv_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogEnv_del(Dz1SysLogEnv *p);
static __inline__ void Dz1SysLogEnv_delAndSetNull(void *ptr)
{
	Dz1SysLogEnv **p = (Dz1SysLogEnv **)ptr;
	Dz1SysLogEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogEnv_dump(Dz1SysLogEnv *p, int tab);

#endif
