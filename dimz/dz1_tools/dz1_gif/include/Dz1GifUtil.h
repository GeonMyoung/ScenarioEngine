#ifndef DZ1_GIF_UTIL_H
#define DZ1_GIF_UTIL_H

#include <dz1_bmp.h>
#include <Dz1GifDef.h>

DZ1_CPPLINK Dz1GifColor *Dz1GifDefaultBKGColor;

DZ1_CPPLINK Dz1BMP			*Dz1GifUtil_createBKG(u16_t width, u16_t height, Dz1Error *errp);

DZ1_CPPLINK u32_t			 Dz1GifUtil_countGraphic(Dz1Gif *gif);			// Scene 갯수

// 팔레트로부터 컬러 얻어내기
#define						 Dz1GifColorArray_getColor(plp, idx)	_Dz1GifColorArray_getColor((plp), (idx), __FILE__, __LINE__)
DZ1_CPPLINK Dz1GifColor	   *_Dz1GifColorArray_getColor(Dz1GifColorArray *palette, u32_t idx, char *__file__, int __line__);

// 팔레트 점검용
#define						 Dz1GifColorArray_available(plp) _Dz1GifColorArray_available((plp), __FILE__, __LINE__)
DZ1_CPPLINK bool_t			_Dz1GifColorArray_available(Dz1GifColorArray *plette, char *__file, int __line__);

// Indexed Color를 RGB로 바꿔서 work_bmp에 그려주기
DZ1_CPPLINK Dz1Error		 Dz1GifUtil_bitblt(Dz1BMP *work_bmp,
											   Dz1GifDescr *global_descr,
											   Dz1GifImgDescr *local_descr, 
											   Dz1GifGraphicControlExt *ctrl,
											   Dz1GifColorArray *palette,
											   Dz1GifRenderTableBasedImg *img);

// bg 컬러 배경에 이미지 그리기
DZ1_CPPLINK Dz1Error		 Dz1GifUtil_bitbltWithBgColor(Dz1BMP *dst,
														  Dz1GifDescr *global_descr,
														  Dz1GifImgDescr *local_descr,
														  Dz1GifGraphicControlExt *ctrl, 
														  Dz1GifColorArray *palette,
														  Dz1GifRenderTableBasedImg *image,
														  Dz1GifColor *bgColor);

// 이전 BMP 배경에 이미지 그리기
DZ1_CPPLINK Dz1Error		 Dz1GifUtil_bitbltWithPrevious(Dz1BMP *dst,
														   Dz1GifDescr *global_descr,
														   Dz1GifImgDescr *local_descr,
														   Dz1GifGraphicControlExt *ctrl, 
														   Dz1GifColorArray *palette,
														   Dz1GifRenderTableBasedImg *image,
														   Dz1BMP *prev);

DZ1_CPPLINK Dz1Error		 Dz1GifUtil_render2(u16_t width, u16_t height,
												Dz1GifColorArray *palette, Dz1GifColor *bgColor,
												Dz1GifGraphic *src, Dz1BMP *canvas, Dz1BMP *last,
												u32_t *ret_dur_ms);

DZ1_CPPLINK Dz1Error		 Dz1GifUtil_render(Dz1GifDescr *descr, Dz1GifGraphic *src,
											   Dz1BMP *canvas, Dz1BMP *last, 
											   u32_t *ret_dur_ms);

#endif
