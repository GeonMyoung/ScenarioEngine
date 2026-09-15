#ifndef DZ1_GIF_UTIL_H_LOCAL
#define DZ1_GIF_UTIL_H_LOCAL

#include "Dz1GifDef.h"
#include "Dz1GifStruct.h"
#include <Dz1GifUtil.h>

DZ1_CPPLINK Dz1Error Dz1Gif_waitThreadWork(Dz1GifDataArr *arr, Dz1Sync *sync);	// locked wait
DZ1_CPPLINK Dz1Error _Dz1Gif_waitThreadWork(Dz1GifDataArr *arr, Dz1Sync *sync); // unlocked wait

DZ1_CPPLINK Dz1Error _convert_LZW2pixels(Dz1Binary *dst, Dz1GifTableBasedImgData *src, Dz1GifImgDescr *descr);
DZ1_CPPLINK Dz1Error _convert_pixels2LZW(Dz1GifTableBasedImgData *dst, Dz1Binary *src, Dz1GifImgDescr *descr);

DZ1_CPPLINK Dz1Error Dz1GifDecodeOpt_sceneOper(Dz1GifDecodeOpt *opt, Dz1GifDescr *descr, Dz1GifGraphic *graphic);
DZ1_CPPLINK Dz1Error Dz1GifDecodeOpt_postProc(Dz1GifDecodeOpt *opt, Dz1GifDataArr *datas);

#endif