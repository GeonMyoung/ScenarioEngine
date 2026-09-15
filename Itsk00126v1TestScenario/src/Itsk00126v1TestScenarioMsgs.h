#ifndef _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_MSGS_H_
#define _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioMsgDefault
typedef struct Itsk00126V1TestScenarioMsgDefault
{
	u32_t		*dummy;
} Itsk00126V1TestScenarioMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1TestScenarioMsgDefault *Itsk00126V1TestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Itsk00126V1TestScenarioMsgDefault *Itsk00126V1TestScenarioMsgDefault_gen(Dz1Error *err) { return Itsk00126V1TestScenarioMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioMsgDefault_purge(Itsk00126V1TestScenarioMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioMsgDefault_del(Itsk00126V1TestScenarioMsgDefault *p);
static __inline__ void Itsk00126V1TestScenarioMsgDefault_delAndSetNull(void *ptr)
{
	Itsk00126V1TestScenarioMsgDefault **p = (Itsk00126V1TestScenarioMsgDefault **)ptr;
	if (p) { Itsk00126V1TestScenarioMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioMsgDefault_dump(Itsk00126V1TestScenarioMsgDefault *p, int tab);
// Itsk00126V1TestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
