#ifndef _DZ1_TDC_DZ1_SYSTEM_INFO_DEF_H_
#define _DZ1_TDC_DZ1_SYSTEM_INFO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SystemInfo
typedef struct Dz1SystemInfo
{
	s32_t		dummy;
} Dz1SystemInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1SystemInfo *Dz1SystemInfo_new(s32_t dummy, Dz1Error *err);
static __inline__ Dz1SystemInfo *Dz1SystemInfo_gen(Dz1Error *err) { return Dz1SystemInfo_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SystemInfo_purge(Dz1SystemInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SystemInfo_del(Dz1SystemInfo *p);
static __inline__ void Dz1SystemInfo_delAndSetNull(void *ptr)
{
	Dz1SystemInfo **p = (Dz1SystemInfo **)ptr;
	if (p) { Dz1SystemInfo_del(*p); *p = NULL; }
}
// Dz1SystemInfo
////////////////////////////////////////////////////////////////////////////////

#endif
