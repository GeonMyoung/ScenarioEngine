#ifndef DZ1_GIF_CODEC_H
#define DZ1_GIF_CODEC_H

#include <Dz1GifDef.h>

DZ1_CPPLINK Dz1Gif *Dz1Gif_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Gif_enc(u8_t *dst, size_t size, Dz1Gif *src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Gif_dec(Dz1Gif *dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif