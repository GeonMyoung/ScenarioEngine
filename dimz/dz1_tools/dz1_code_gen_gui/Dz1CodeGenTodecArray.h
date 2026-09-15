#ifndef DZ1_CODE_GEN_TODEC_ARRAY_H
#define DZ1_CODE_GEN_TODEC_ARRAY_H

#include "Dz1CodeGenTodecPublish.h"

DZ1_CPPLINK Dz1Error ConstructCodecEntry_array_gen_publish(FILE *fp, ConstructCodecEntry *p, str_t endian);
DZ1_CPPLINK Dz1Error ConstructCodecEntry_array_rw_publish(FILE *fp, ConstructCodecEntry *p, str_t endian);

#endif