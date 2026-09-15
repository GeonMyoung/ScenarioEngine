#ifndef ITSK_00126_V_1_TEST_SCENARIO_DEF_JSON_H
#define ITSK_00126_V_1_TEST_SCENARIO_DEF_JSON_H

#include <Dz1Json.h>
#include "Itsk00126v1TestScenarioDef.h"

DZ1_CPPLINK bool_t Itsk00126v1TestScenarioDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *Itsk00126v1TestScenarioDef_genJsonSpec(Dz1Error *err);

#endif // ITSK_00126_V_1_TEST_SCENARIO_DEF_JSON_H
