#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_MSGS_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioMsgDefault
typedef struct TrafficSignalControllerTestScenarioMsgDefault
{
	u32_t		*dummy;
} TrafficSignalControllerTestScenarioMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestScenarioMsgDefault *TrafficSignalControllerTestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ TrafficSignalControllerTestScenarioMsgDefault *TrafficSignalControllerTestScenarioMsgDefault_gen(Dz1Error *err) { return TrafficSignalControllerTestScenarioMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioMsgDefault_purge(TrafficSignalControllerTestScenarioMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioMsgDefault_del(TrafficSignalControllerTestScenarioMsgDefault *p);
static __inline__ void TrafficSignalControllerTestScenarioMsgDefault_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestScenarioMsgDefault **p = (TrafficSignalControllerTestScenarioMsgDefault **)ptr;
	if (p) { TrafficSignalControllerTestScenarioMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioMsgDefault_dump(TrafficSignalControllerTestScenarioMsgDefault *p, int tab);
// TrafficSignalControllerTestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
