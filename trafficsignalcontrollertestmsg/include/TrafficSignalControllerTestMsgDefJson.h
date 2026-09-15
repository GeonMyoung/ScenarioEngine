#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_DEF_JSON_H
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_DEF_JSON_H

#include <Dz1Json.h>
#include "TrafficSignalControllerTestMsgDef.h"

DZ1_CPPLINK bool_t TrafficSignalControllerTestMsgDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *TrafficSignalControllerTestMsgDef_genJsonSpec(Dz1Error *err);

#endif // TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_DEF_JSON_H
