#ifndef DZ1_CODE_GEN_TODEC_STRUCT_H
#define DZ1_CODE_GEN_TODEC_STRUCT_H

#include "Dz1CodeGenTodecPublish.h"

DZ1_CPPLINK Dz1Error ConstructCodecEntry_struct_gen_publish(FILE *fp, ConstructCodecEntry *p, str_t endian);
DZ1_CPPLINK Dz1Error ConstructCodecEntry_struct_rw_publish(FILE *fp, ConstructCodecEntry *p, str_t endian);

#endif