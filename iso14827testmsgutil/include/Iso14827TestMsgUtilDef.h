#ifndef _DZ1_TDC_ISO14827_TEST_MSG_UTIL_DEF_H_
#define _DZ1_TDC_ISO14827_TEST_MSG_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestMsgUtil
typedef struct Iso14827TestMsgUtil
{
	s32_t		dummy;
} Iso14827TestMsgUtil;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestMsgUtil *Iso14827TestMsgUtil_new(s32_t dummy, Dz1Error *err);
static __inline__ Iso14827TestMsgUtil *Iso14827TestMsgUtil_gen(Dz1Error *err) { return Iso14827TestMsgUtil_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestMsgUtil_purge(Iso14827TestMsgUtil *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestMsgUtil_del(Iso14827TestMsgUtil *p);
static __inline__ void Iso14827TestMsgUtil_delAndSetNull(void *ptr)
{
	Iso14827TestMsgUtil **p = (Iso14827TestMsgUtil **)ptr;
	if (p) { Iso14827TestMsgUtil_del(*p); *p = NULL; }
}
// Iso14827TestMsgUtil
////////////////////////////////////////////////////////////////////////////////

#endif
