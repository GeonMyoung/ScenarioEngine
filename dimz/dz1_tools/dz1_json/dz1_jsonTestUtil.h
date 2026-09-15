#ifndef DZ1_JSON_TEST_UTIL_H
#define DZ1_JSON_TEST_UTIL_H

#include <Dz1Json.h>
#include "dz1_jsonTestDef.h"

DZ1_CPPLINK_VAR Dz1JsonNewLine test_line_mode;

DZ1_CPPLINK Dz1Error Dz1Json_testString(Dz1JsonSpec *spec);
DZ1_CPPLINK Dz1Error Dz1Json_testStringList(Dz1JsonSpec *spec);
DZ1_CPPLINK Dz1Error Dz1Json_testBinary(Dz1JsonSpec *spec);

DZ1_CPPLINK Dz1Error Dz1Json_testReal32(Dz1JsonSpec *spec);
DZ1_CPPLINK Dz1Error Dz1Json_testReal64(Dz1JsonSpec *spec);

DZ1_CPPLINK Dz1Error Dz1Json_testMyStruct(Dz1JsonSpec *spec);
DZ1_CPPLINK Dz1Error Dz1Json_testMyUnion(Dz1JsonSpec *spec);

DZ1_CPPLINK Dz1Error Dz1Json_testMyStructList(Dz1JsonSpec *spec);
DZ1_CPPLINK Dz1Error Dz1Json_testMyUnionList(Dz1JsonSpec *spec);

DZ1_CPPLINK Dz1Error Dz1Json_testMyComponent(Dz1JsonSpec *spec);

#endif

