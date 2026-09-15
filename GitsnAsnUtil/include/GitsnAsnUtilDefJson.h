#ifndef GITSN_ASN_UTIL_DEF_JSON_H
#define GITSN_ASN_UTIL_DEF_JSON_H

#include <Dz1Json.h>
#include "GitsnAsnUtilDef.h"

DZ1_CPPLINK bool_t GitsnAsnUtilDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *GitsnAsnUtilDef_genJsonSpec(Dz1Error *err);

#endif // GITSN_ASN_UTIL_DEF_JSON_H
