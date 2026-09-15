#ifndef ITSK_00144_2_TEST_SCENARIO_DEF_JSON_H
#define ITSK_00144_2_TEST_SCENARIO_DEF_JSON_H

#include <Dz1Json.h>
#include "ITSK00144_2TestScenarioDef.h"

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *ITSK00144_2TestScenarioDef_genJsonSpec(Dz1Error *err);

#endif // ITSK_00144_2_TEST_SCENARIO_DEF_JSON_H
