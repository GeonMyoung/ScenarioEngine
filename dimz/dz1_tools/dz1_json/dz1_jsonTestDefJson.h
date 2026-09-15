#ifndef DZ_1_JSON_TEST_DEF_JSON_H
#define DZ_1_JSON_TEST_DEF_JSON_H

#include <Dz1Json.h>
#include "dz1_jsonTestDef.h"

DZ1_CPPLINK bool_t dz1_jsonTestDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *dz1_jsonTestDef_genJsonSpec(Dz1Error *err);

#endif // DZ_1_JSON_TEST_DEF_JSON_H
