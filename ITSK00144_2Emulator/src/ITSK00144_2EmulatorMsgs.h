#ifndef _DZ1_TDC_I_T_S_K00144_2_EMULATOR_MSGS_H_
#define _DZ1_TDC_I_T_S_K00144_2_EMULATOR_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorMsgDefault
typedef struct ITSK001442EmulatorMsgDefault
{
	u32_t		*dummy;
} ITSK001442EmulatorMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442EmulatorMsgDefault *ITSK001442EmulatorMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ ITSK001442EmulatorMsgDefault *ITSK001442EmulatorMsgDefault_gen(Dz1Error *err) { return ITSK001442EmulatorMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorMsgDefault_purge(ITSK001442EmulatorMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorMsgDefault_del(ITSK001442EmulatorMsgDefault *p);
static __inline__ void ITSK001442EmulatorMsgDefault_delAndSetNull(void *ptr)
{
	ITSK001442EmulatorMsgDefault **p = (ITSK001442EmulatorMsgDefault **)ptr;
	if (p) { ITSK001442EmulatorMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorMsgDefault_dump(ITSK001442EmulatorMsgDefault *p, int tab);
// ITSK001442EmulatorMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
