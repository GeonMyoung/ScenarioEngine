#ifndef DZ1_GIF_LOAD_H
#define DZ1_GIF_LOAD_H

#include <dz1_io_stream.h>
#include <Dz1GifDef.h>

DZ1_CPPLINK ssize_t Dz1Gif_write(Dz1Stream *dst, Dz1Gif *src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Gif_read(Dz1Gif *dst, Dz1Stream *src, void *param, Dz1Error *err);

#endif