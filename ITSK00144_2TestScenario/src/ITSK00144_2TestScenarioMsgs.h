#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_MSGS_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioMsgDefault
typedef struct ITSK001442TestScenarioMsgDefault
{
	u32_t		*dummy;
} ITSK001442TestScenarioMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442TestScenarioMsgDefault *ITSK001442TestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ ITSK001442TestScenarioMsgDefault *ITSK001442TestScenarioMsgDefault_gen(Dz1Error *err) { return ITSK001442TestScenarioMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioMsgDefault_purge(ITSK001442TestScenarioMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioMsgDefault_del(ITSK001442TestScenarioMsgDefault *p);
static __inline__ void ITSK001442TestScenarioMsgDefault_delAndSetNull(void *ptr)
{
	ITSK001442TestScenarioMsgDefault **p = (ITSK001442TestScenarioMsgDefault **)ptr;
	if (p) { ITSK001442TestScenarioMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioMsgDefault_dump(ITSK001442TestScenarioMsgDefault *p, int tab);
// ITSK001442TestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
