#ifndef _DZ1_TDC_DZ1_SYSLOG_TIMER_H_
#define _DZ1_TDC_DZ1_SYSLOG_TIMER_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>


typedef struct Dz1SysLogTimer
{
	s32_t  id;
} Dz1SysLogTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1SysLogTimer *Dz1SysLogTimer_new(s32_t id, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogTimer_del(Dz1SysLogTimer *p);
static __inline__ void Dz1SysLogTimer_delAndSetNull(void *ptr)
{
	Dz1SysLogTimer **p = (Dz1SysLogTimer **)ptr;
	Dz1SysLogTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SysLogTimer_dump(Dz1SysLogTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1SysLogTimer_cmp(Dz1SysLogTimer *a, Dz1SysLogTimer *b);

#endif
