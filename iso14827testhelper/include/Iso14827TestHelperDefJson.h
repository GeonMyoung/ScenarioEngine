#ifndef ISO_14827_TEST_HELPER_DEF_JSON_H
#define ISO_14827_TEST_HELPER_DEF_JSON_H

#include <Dz1Json.h>
#include "Iso14827TestHelperDef.h"

DZ1_CPPLINK bool_t Iso14827TestHelperDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *Iso14827TestHelperDef_genJsonSpec(Dz1Error *err);

#endif // ISO_14827_TEST_HELPER_DEF_JSON_H
