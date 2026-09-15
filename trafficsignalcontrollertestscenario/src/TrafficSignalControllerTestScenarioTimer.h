#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TIMER_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioTimer
typedef struct TrafficSignalControllerTestScenarioTimer
{
	u32_t		id;
} TrafficSignalControllerTestScenarioTimer;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestScenarioTimer *TrafficSignalControllerTestScenarioTimer_new(u32_t id, Dz1Error *err);
static __inline__ TrafficSignalControllerTestScenarioTimer *TrafficSignalControllerTestScenarioTimer_gen(Dz1Error *err) { return TrafficSignalControllerTestScenarioTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioTimer_purge(TrafficSignalControllerTestScenarioTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioTimer_del(TrafficSignalControllerTestScenarioTimer *p);
static __inline__ void TrafficSignalControllerTestScenarioTimer_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestScenarioTimer **p = (TrafficSignalControllerTestScenarioTimer **)ptr;
	if (p) { TrafficSignalControllerTestScenarioTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioTimer_dump(TrafficSignalControllerTestScenarioTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int TrafficSignalControllerTestScenarioTimer_cmp(TrafficSignalControllerTestScenarioTimer *a, TrafficSignalControllerTestScenarioTimer *b);
// TrafficSignalControllerTestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

#endif
