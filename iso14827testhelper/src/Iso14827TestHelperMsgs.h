#ifndef _DZ1_TDC_ISO14827_TEST_HELPER_MSGS_H_
#define _DZ1_TDC_ISO14827_TEST_HELPER_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperDef.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperMsgDefault
typedef struct Iso14827TestHelperMsgDefault
{
	u32_t		*dummy;
} Iso14827TestHelperMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperMsgDefault *Iso14827TestHelperMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Iso14827TestHelperMsgDefault *Iso14827TestHelperMsgDefault_gen(Dz1Error *err) { return Iso14827TestHelperMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperMsgDefault_purge(Iso14827TestHelperMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperMsgDefault_del(Iso14827TestHelperMsgDefault *p);
static __inline__ void Iso14827TestHelperMsgDefault_delAndSetNull(void *ptr)
{
	Iso14827TestHelperMsgDefault **p = (Iso14827TestHelperMsgDefault **)ptr;
	if (p) { Iso14827TestHelperMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperMsgDefault_dump(Iso14827TestHelperMsgDefault *p, int tab);
// Iso14827TestHelperMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
