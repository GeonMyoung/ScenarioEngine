#ifndef DZ1_RIFF_WAVE_UTIL_H
#define DZ1_RIFF_WAVE_UTIL_H

#include "dz1_riff_wave.h"

//DZ1_CPPLINK DZ1_DLLPORT void *Dz1RiffWave_gen(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1RiffWave_enc(u8_t *dst, size_t size, Dz1RiffWave *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1RiffWave_dec(Dz1RiffWave *dst, u8_t *src, size_t size, Dz1Error *err);

#endif