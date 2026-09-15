#ifndef _DZ1_TDC_I_T_S_K00100_3_UTIL_DEF_H_
#define _DZ1_TDC_I_T_S_K00100_3_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001003Util
typedef struct ITSK001003Util
{
	s32_t		dummy;
} ITSK001003Util;

DZ1_CPPLINK DZ1_DLLPORT ITSK001003Util *ITSK001003Util_new(s32_t dummy, Dz1Error *err);
static __inline__ ITSK001003Util *ITSK001003Util_gen(Dz1Error *err) { return ITSK001003Util_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001003Util_purge(ITSK001003Util *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001003Util_del(ITSK001003Util *p);
static __inline__ void ITSK001003Util_delAndSetNull(void *ptr)
{
	ITSK001003Util **p = (ITSK001003Util **)ptr;
	if (p) { ITSK001003Util_del(*p); *p = NULL; }
}
// ITSK001003Util
////////////////////////////////////////////////////////////////////////////////

#endif
