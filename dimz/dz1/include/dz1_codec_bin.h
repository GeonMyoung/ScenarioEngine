#ifndef DZ1_CODEC_BIN_H
#define DZ1_CODEC_BIN_H

#include <dz1_bin.h>
#include <dz1_codec.h>

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary8_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary16_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary8_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary16_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);

#endif

