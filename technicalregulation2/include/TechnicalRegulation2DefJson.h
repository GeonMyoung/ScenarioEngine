#ifndef TECHNICAL_REGULATION_2_DEF_JSON_H
#define TECHNICAL_REGULATION_2_DEF_JSON_H

#include <Dz1Json.h>
#include "TechnicalRegulation2Def.h"

DZ1_CPPLINK bool_t TechnicalRegulation2Def_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *TechnicalRegulation2Def_genJsonSpec(Dz1Error *err);

#endif // TECHNICAL_REGULATION_2_DEF_JSON_H
