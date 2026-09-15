#ifndef GITSN_DSRCMSG_TEST_SCENARIO_DEF_JSON_H
#define GITSN_DSRCMSG_TEST_SCENARIO_DEF_JSON_H

#include <Dz1Json.h>
#include "GitsnDSRCMsgTestScenarioDef.h"

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *GitsnDSRCMsgTestScenarioDef_genJsonSpec(Dz1Error *err);

#endif // GITSN_DSRCMSG_TEST_SCENARIO_DEF_JSON_H
