#include <dz1_str.h>
#include <dz1_bmp.h>
#include <dz1_codec.h>
#include <dz1_codec_bin.h>
#include "Dz1GifCodec.h"
#include "Dz1GifUtil.h"
#include "Dz1GifLzw.h"

static ssize_t DataSubBlock_enc(u8_t *dst, size_t size, u8_t *src, size_t src_size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL && src_size != 0) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, *sp = src;
		u8_t sz = 0;
		while(src_size)
		{
			sz = src_size > 255 ? 255 : (u8_t)src_size;

			DZ1_ENCODE1(cp, size, sz, errp, ret);
			DZ1_ENCODE(cp, size, sp, sz, errp, ret);

			src_size -= sz;
			sp += sz;
		}
		DZ1_ENCODE1(cp, size, 0, errp, ret);
	}
	return ret;
}
////////////////////////////////////////////////////////////////////////////////
// Dz1GifColor CODEC
// static __inline__ Dz1GifColor *Dz1GifColor_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifColor *ret = Dz1GifColor_new(0, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifColor_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColor *src = (Dz1GifColor *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, src->red, errp, ret);
		DZ1_ENCODE1(cp, size, src->green, errp, ret);
		DZ1_ENCODE1(cp, size, src->blue, errp, ret);
	}
	return ret;
}
// Dz1GifColor CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorList CODEC
// static __inline__ Dz1GifColorList *Dz1GifColorList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifColorList *ret = Dz1GifColorList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1GifColorList_enc(void *ptr, Dz1GifColor *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1GifColor_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1GifColorList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorList *src = (Dz1GifColorList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1GifColorList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}
// Dz1GifColorList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorArray CODEC
// static __inline__ Dz1GifColorArray *Dz1GifColorArray_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifColorArray *ret = Dz1GifColorArray_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifColorArray_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorArray *src = (Dz1GifColorArray *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifColorList_enc(cp, size, src->list, param, errp), errp);
	}
	return ret;
}
// Dz1GifColorArray CODEC
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Dz1GifHeader CODEC
// static __inline__ Dz1GifHeader *Dz1GifHeader_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifHeader *ret = Dz1GifHeader_new(NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifHeader_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifHeader *src = (Dz1GifHeader *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if (src->sig == NULL || strlen(src->sig) != 3) ERR_SET_OUT(errp, EINVAL);
	else if (src->ver == NULL || strlen(src->ver) != 3) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE(cp, size, (u8_t *)src->sig, 3, errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)src->ver, 3, errp, ret);
	}
	return ret;
}
// Dz1GifHeader CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDescr CODEC
// static __inline__ Dz1GifDescr *Dz1GifDescr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDescr *ret = Dz1GifDescr_new(0, 0, FALSE, 0, FALSE, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifDescr_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDescr *src = (Dz1GifDescr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, v = 0;
		_DZ1_ENCODE2(cp, size, src->width, errp, ret);
		_DZ1_ENCODE2(cp, size, src->height, errp, ret);

		if (src->gctPresent) v |= 0x80;
		v |= (src->color_res & 7) << 4;
		if (src->gctIsSorted) v |= 0x08;
		v |= (src->gctSizeExp & 0x7);
		DZ1_ENCODE1(cp, size, v, errp, ret);

		DZ1_ENCODE1(cp, size, src->bgcIdx, errp, ret);
		DZ1_ENCODE1(cp, size, src->aspect, errp, ret);

		if (src->gctPresent)
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifColorArray_enc(cp, size, src->palette, param, errp), errp);
	}
	return ret;
}
// Dz1GifDescr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifImgDescr CODEC
// static __inline__ Dz1GifImgDescr *Dz1GifImgDescr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifImgDescr *ret = Dz1GifImgDescr_new(0, 0, 0, 0, FALSE, FALSE, FALSE, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifImgDescr_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifImgDescr *src = (Dz1GifImgDescr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, v = 0;;
		DZ1_ENCODE1(cp, size, 0x2C, errp, ret);
		_DZ1_ENCODE2(cp, size, (u16_t)(src->x & 0xFFFF), errp, ret);
		_DZ1_ENCODE2(cp, size, (u16_t)(src->y & 0xFFFF), errp, ret);
		_DZ1_ENCODE2(cp, size, (u16_t)(src->width & 0xFFFF), errp, ret);
		_DZ1_ENCODE2(cp, size, (u16_t)(src->height & 0xFFFF), errp, ret);

		if (src->lctPresent) v |= 0x80;
		if (src->isInterlaced) v |= 0x40;
		if (src->lctIsSorted) v |= 0x20;
		v |= (src->lctSizeExp & 0x7);
		DZ1_ENCODE1(cp, size, v, errp, ret);

		if (src->lctPresent) DZ1_CODEC_FUNC(cp, size, ret, Dz1GifColorArray_enc(cp, size, src->palette, param, errp), errp);
	}
	return ret;
}
// Dz1GifImgDescr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderPlainTextExt CODEC
// static __inline__ Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderPlainTextExt *ret = Dz1GifRenderPlainTextExt_new(0, 0, 0, 0, 0, 0, 0, 0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderPlainTextExt_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderPlainTextExt *src = (Dz1GifRenderPlainTextExt *)_src;
	if (src == NULL || src->text == NULL || strlen(src->text) == 0) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, 0x21, errp, ret);
		DZ1_ENCODE1(cp, size, 0x01, errp, ret);
		DZ1_ENCODE1(cp, size, 0x0C, errp, ret);
		_DZ1_ENCODE2(cp, size, src->x, errp, ret);
		_DZ1_ENCODE2(cp, size, src->y, errp, ret);
		_DZ1_ENCODE2(cp, size, src->width, errp, ret);
		_DZ1_ENCODE2(cp, size, src->height, errp, ret);
		DZ1_ENCODE1(cp, size, src->cellWidth, errp, ret);
		DZ1_ENCODE1(cp, size, src->cellHeight, errp, ret);
		DZ1_ENCODE1(cp, size, src->fgColorIdx, errp, ret);
		DZ1_ENCODE1(cp, size, src->bgColorIdx, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, DataSubBlock_enc(cp, size, (u8_t *)src->text, strlen(src->text), param, errp), errp);
	}
	return ret;
}
// Dz1GifRenderPlainTextExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlExt CODEC
// static __inline__ Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifGraphicControlExt *ret = Dz1GifGraphicControlExt_new(Dz1GifGraphicControlCmd_noMean, FALSE, FALSE, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifGraphicControlExt_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphicControlExt *src = (Dz1GifGraphicControlExt *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, v = 0;
		DZ1_ENCODE1(cp, size, 0x21, errp, ret);
		DZ1_ENCODE1(cp, size, 0xF9, errp, ret);
		DZ1_ENCODE1(cp, size, 0x04, errp, ret);

		v = (src->disposal & 0x7) << 2;
		if (src->userInput) v |= 0x2;
		if (src->tpColPresent) v |= 0x01;
		DZ1_ENCODE1(cp, size, v, errp, ret);

		_DZ1_ENCODE2(cp, size, src->delay, errp, ret);
		DZ1_ENCODE1(cp, size, src->tpColorIdx, errp, ret);

		DZ1_ENCODE1(cp, size, 0, errp, ret);
	}
	return ret;
}
// Dz1GifGraphicControlExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifCommentExt CODEC
// static __inline__ Dz1GifCommentExt *Dz1GifCommentExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifCommentExt *ret = Dz1GifCommentExt_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifCommentExt_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifCommentExt *src = (Dz1GifCommentExt *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, 0x21, errp, ret);
		DZ1_ENCODE1(cp, size, 0xFE, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, DataSubBlock_enc(cp, size, (u8_t *)src->text, strlen(src->text), param, errp), errp);
	}
	return ret;
}
// Dz1GifCommentExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifAppExt CODEC
// static __inline__ Dz1GifAppExt *Dz1GifAppExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifAppExt *ret = Dz1GifAppExt_new(NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifAppExt_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifAppExt *src = (Dz1GifAppExt *)_src;
	if (src == NULL || src->app_auth == NULL || src->app_auth->data == NULL || src->app_auth->size != 3) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1Binary *app_auth = src->app_auth, *app_data = src->app_data;
		char app[9] = { 0, }, ext[4] = { 0, };
		strncpy(app, src->app, 8);
		memcpy(ext, app_auth->data, 3);

		DZ1_ENCODE1(cp, size, 0x21, errp, ret);
		DZ1_ENCODE1(cp, size, 0xFF, errp, ret);
		DZ1_ENCODE1(cp, size, 0x0B, errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)app, 8, errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)ext, 3, errp, ret);

		DZ1_CODEC_FUNC(cp, size, ret, DataSubBlock_enc(cp, size, app_data->data, app_data->size, param, errp), errp);
	}
	return ret;
}
// Dz1GifAppExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifTableBasedImgData CODEC
// static Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifTableBasedImgData *ret = Dz1GifTableBasedImgData_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifTableBasedImgData_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *src = (Dz1GifTableBasedImgData *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1Binary *lzw = src->lzw;
		DZ1_ENCODE1(cp, size, src->lzwMinimumCodeSize, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, DataSubBlock_enc(cp, size, lzw->data, lzw->size, param, errp), errp);
	}
	return ret;
}
// Dz1GifTableBasedImgData CODEC
////////////////////////////////////////////////////////////////////////////////
static ssize_t LzwPixel_enc(u8_t *dst, size_t size, Dz1Binary *src,
							Dz1GifImgDescr *local_descr,
							void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *data = NULL;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((data = Dz1GifTableBasedImgData_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
	else
	{
		ssize_t status = 0;
		u8_t *cp = dst;
		pthread_cleanup_push(Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);
		if ((*errp = _convert_pixels2LZW(data, src, local_descr)).code) { ERR_OUT(errp); ret = -1; }
		else if ((status = Dz1GifTableBasedImgData_enc(cp, size, data, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else DZ1_CODEC_APPLY(cp, size, status, ret);
		pthread_cleanup_pop(1); // (Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderTableBasedImg CODEC
// static __inline__ Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderTableBasedImg *ret = Dz1GifRenderTableBasedImg_new(NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderTableBasedImg_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderTableBasedImg *src = (Dz1GifRenderTableBasedImg *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifImgDescr_enc(cp, size, src->descr, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, LzwPixel_enc(cp, size, src->pixels, src->descr, param, errp), errp);
	}
	return ret;
}
// Dz1GifRenderTableBasedImg CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingData CODEC
// static __inline__ Dz1GifRenderingData *Dz1GifRenderingData_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderingData *ret = Dz1GifRenderingData_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderingData_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderingData *src = (Dz1GifRenderingData *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		switch(src->present)
		{
		case Dz1GifRenderingDataPresent_tbi:
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifRenderTableBasedImg_enc(cp, size, src->x.tbi, param, errp), errp);
			break;
		case Dz1GifRenderingDataPresent_pte:
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifRenderPlainTextExt_enc(cp, size, src->x.pte, param, errp), errp);
			break;
		default:
			DZ1_CODEC_ERRSET_RET(errp, EINVAL);
			break;
		}
	}
	return ret;
}
// Dz1GifRenderingData CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphic CODEC
// static __inline__ Dz1GifGraphic *Dz1GifGraphic_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifGraphic *ret = Dz1GifGraphic_new(NULL, NULL, -1, FALSE, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifGraphic_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphic *src = (Dz1GifGraphic *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		if (src->gce != NULL)
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifGraphicControlExt_enc(cp, size, src->gce, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifRenderingData_enc(cp, size, src->data, param, errp), errp);
	}
	return ret;
}
// Dz1GifGraphic CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntry CODEC
// static __inline__ Dz1GifDataEntry *Dz1GifDataEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDataEntry *ret = Dz1GifDataEntry_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifDataEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataEntry *src = (Dz1GifDataEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		switch(src->present)
		{
		case Dz1GifDataEntryPresent_graphic:
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifGraphic_enc(cp, size, src->x.graphic, param, errp), errp);
			break;
		case Dz1GifDataEntryPresent_app_ext:
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifAppExt_enc(cp, size, src->x.app_ext, param, errp), errp);
			break;
		case Dz1GifDataEntryPresent_comment:
			DZ1_CODEC_FUNC(cp, size, ret, Dz1GifCommentExt_enc(cp, size, src->x.comment, param, errp), errp);
			break;
		default:
			DZ1_CODEC_ERRSET_RET(errp, EINVAL);
			break;
		}
	}
	return ret;
}
// Dz1GifDataEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataArr CODEC
typedef struct GifDataArrCodecArg
{
	u8_t *cp;
	size_t size;
	ssize_t ret;
	void *option;
} GifDataArrCodecArg;

// static __inline__ Dz1GifDataArr *Dz1GifDataArr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDataArr *ret = Dz1GifDataArr_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1GifDataArr_enc(void *ptr, Dz1GifDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	GifDataArrCodecArg *arg = (GifDataArrCodecArg *)ptr;
	ssize_t status = Dz1GifDataEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1GifDataArr_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataArr *src = (Dz1GifDataArr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		GifDataArrCodecArg arg = { cp, size, 0, param };
		if ((*errp = src->travel(src, _Dz1GifDataArr_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}
// Dz1GifDataArr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Gif CODEC
// Dz1Gif *Dz1Gif_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1Gif *ret = Dz1Gif_new(NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

ssize_t Dz1Gif_enc(u8_t *dst, size_t size, Dz1Gif *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifHeader_enc(cp, size, src->hdr, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifDescr_enc(cp, size, src->descr, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1GifDataArr_enc(cp, size, src->datas, param, errp), errp);
		DZ1_ENCODE1(cp, size, 0x3B, errp, ret);
	}
	return ret;
}
// Dz1Gif CODEC
////////////////////////////////////////////////////////////////////////////////
