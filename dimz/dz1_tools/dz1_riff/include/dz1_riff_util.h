#ifndef DZ1_RIFF_UTIL_H
#define DZ1_RIFF_UTIL_H

#include <dz1_riff.h>

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Riff_enc(u8_t *dst, size_t size, Dz1Riff *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Riff_dec(Dz1Riff *dst, u8_t *src, size_t size, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Riff_load(Dz1Riff *dst, FILE *fp, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Riff_save(FILE *fp, Dz1Riff *src, Dz1Error *err);

#endif

