#include <dz1_str.h>
#include <dz1_io_stream.h>
#include <dz1_bmp.h>
#include <dz1_codec_bin.h>
#include "Dz1GifIoStream.h"
#include "Dz1GifUtil.h"
#include "Dz1GifLzw.h"

static size_t _calc_size(Dz1GifDataSubBlock *p)
{
	size_t ret = 0;
	Dz1Binary *bin = NULL;
	while(p != NULL)
	{
		bin = p->bin;
		ret += bin->size;
		p = p->next;
	}
	return ret;
}

static u8_t *Dz1GifDataSubBlock_flatten(Dz1GifDataSubBlock *p, size_t *ret_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *ret = NULL;
	size_t size = _calc_size(p);

	if (ret_size) (*ret_size) = size;

	if (size > 0) 
	{
		if ((ret = (u8_t *)Dz1Malloc(size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t *cp = ret;
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
			while(p != NULL)
			{
				bin = p->bin;
				memcpy(cp, bin->data, bin->size);
				cp += bin->size;
				p = p->next;
			}
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static ssize_t DataSubBlock_write(Dz1Stream *dst, u8_t *src, size_t src_size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL && src_size != 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *sp = src;
		u8_t sz = 0;
		while(src_size)
		{
			sz = src_size > 255 ? 255 : (u8_t)src_size;

			DZ1_STREAM_WRITE1(dst, sz, errp, ret);
			DZ1_STREAM_WRITE(dst, sp, sz, errp, ret);

			src_size -= sz;
			sp += sz;
		}
		DZ1_STREAM_WRITE1(dst, 0, errp, ret);
	}
	return ret;
}

static ssize_t DataSubBlock_read(u8_t **dst, size_t *ret_size, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t buf[256];
		u8_t sz;
		Dz1GifDataSubBlock *p = NULL, **pprev = &p, *ptemp;
		pthread_cleanup_push(Dz1GifDataSubBlock_delAndSetNull, (void *)&p);
		do 
		{
			DZ1_STREAM_READ1(&sz, src, errp, ret);
			if (sz)
			{
				DZ1_STREAM_READ(buf, sz, src, errp, ret);
				if (( (*pprev) = ptemp = Dz1GifDataSubBlock_new(NULL, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
				else if ((ptemp->bin = Dz1Binary_new(buf, sz, errp)) == NULL) ERR_OUT(errp);
				else pprev = &ptemp->next;
			}
		} while (sz != 0 && errp->code == 0);

		if (errp->code == 0)
		{
			if (( (*dst) = Dz1GifDataSubBlock_flatten(p, ret_size, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		}
		pthread_cleanup_pop(1); // (Dz1GifDataSubBlock_delAndSetNull, (void *)&p);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColor CODEC
// static Dz1GifColor *Dz1GifColor_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifColor *ret = Dz1GifColor_new(0, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifColor_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColor *src = (Dz1GifColor *)_src;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		DZ1_STREAM_WRITE1(dst, src->red, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->green, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->blue, errp, ret);
	}
	return ret;
}

static ssize_t Dz1GifColor_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColor *dst = (Dz1GifColor *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		DZ1_STREAM_READ1(&dst->red, src, errp, ret);
		DZ1_STREAM_READ1(&dst->green, src, errp, ret);
		DZ1_STREAM_READ1(&dst->blue, src, errp, ret);
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

static Dz1Error _Dz1GifColorList_write(void *ptr, Dz1GifColor *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = Dz1GifColor_write(arg->stream, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp); else arg->ret += status;
	return err;
}

static ssize_t Dz1GifColorList_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorList *src = (Dz1GifColorList *)_src;
	if (dst == NULL || src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, Dz1IOStreamEndian_big, param };
		if ((*errp = src->travel(src, _Dz1GifColorList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

static ssize_t Dz1GifColorList_read(void *_dst, Dz1Stream *src, u8_t colorTableSizeExp, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorList *dst = (Dz1GifColorList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u16_t cnt = (2 << colorTableSizeExp), i;
		Dz1GifColor *node = NULL;
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1GifColor_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1GifColor_delAndSetNull, (void *)&node);
				node->idx = i;
				if ((status = Dz1GifColor_read(node, src, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					ret += status;
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1GifColor_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1GifColorList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorArray CODEC
// static Dz1GifColorArray *Dz1GifColorArray_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifColorArray *ret = Dz1GifColorArray_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifColorArray_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorArray *src = (Dz1GifColorArray *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1GifColorList_write(dst, src->list, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifColorArray_read(void *_dst, Dz1Stream *src, u8_t colorTableSizeExp, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifColorArray *dst = (Dz1GifColorArray *)_dst;
	if (src == NULL || dst == NULL)
	{
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	}
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1GifColorList_read(dst->list, src, colorTableSizeExp, param, errp), errp);
	}
	return ret;
}
// Dz1GifColorArray CODEC
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Dz1GifHeader CODEC
// static Dz1GifHeader *Dz1GifHeader_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifHeader *ret = Dz1GifHeader_new(NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifHeader_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifHeader *src = (Dz1GifHeader *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if (src->sig == NULL || strlen(src->sig) != 3) ERR_SET_OUT(errp, EINVAL);
	else if (src->ver == NULL || strlen(src->ver) != 3) ERR_SET_OUT(errp, EINVAL);
	else
	{
		DZ1_STREAM_WRITE(dst, (u8_t *)src->sig, 3, errp, ret);
		DZ1_STREAM_WRITE(dst, (u8_t *)src->ver, 3, errp, ret);
	}
	return ret;
}

static ssize_t Dz1GifHeader_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifHeader *dst = (Dz1GifHeader *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		char temp[4] = { 0, };
		DZ1_STREAM_READ((u8_t *)temp, 3, src, errp, ret);
		if ((dst->sig = Dz1Str_dup(temp, errp)) == NULL) ERR_OUT_RET(errp, -1);

		DZ1_STREAM_READ((u8_t *)temp, 3, src, errp, ret);
		if ((dst->ver = Dz1Str_dup(temp, errp)) == NULL) ERR_OUT_RET(errp, -1);
	}
	return ret;
}
// Dz1GifHeader CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDescr CODEC
// static Dz1GifDescr *Dz1GifDescr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDescr *ret = Dz1GifDescr_new(0, 0, FALSE, 0, FALSE, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifDescr_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDescr *src = (Dz1GifDescr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v = 0;
		DZ1_STREAM_WRITE2(dst, src->width, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->height, Dz1IOStreamEndian_little, errp, ret);

		if (src->gctPresent) v |= 0x80;
		v |= (src->color_res & 7) << 4;
		if (src->gctIsSorted) v |= 0x08;
		v |= (src->gctSizeExp & 0x7);
		DZ1_STREAM_WRITE1(dst, v, errp, ret);

		DZ1_STREAM_WRITE1(dst, src->bgcIdx, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->aspect, errp, ret);

		if (src->gctPresent)
			DZ1_IO_STREAM_FUNC(ret, Dz1GifColorArray_write(dst, src->palette, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifDescr_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDescr *dst = (Dz1GifDescr *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		DZ1_STREAM_READ2(&dst->width, src, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_READ2(&dst->height, src, Dz1IOStreamEndian_little, errp, ret);

		DZ1_STREAM_READ1(&v, src, errp, ret);
		dst->gctPresent = (v & 0x80) ? TRUE : FALSE;
		dst->color_res = ((v >> 4) & 7);
		dst->gctIsSorted = (v & 0x08) ? TRUE : FALSE;
		dst->gctSizeExp = (v & 0x7);

		DZ1_STREAM_READ1(&dst->bgcIdx, src, errp, ret);
		DZ1_STREAM_READ1(&dst->aspect, src, errp, ret);

		if (dst->gctPresent)
		{
			if ((dst->palette = Dz1GifColorArray_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, Dz1GifColorArray_read(dst->palette, src, dst->gctSizeExp, param, errp), errp);
		}
	}
	return ret;
}
// Dz1GifDescr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifImgDescr CODEC
// static Dz1GifImgDescr *Dz1GifImgDescr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifImgDescr *ret = Dz1GifImgDescr_new(0, 0, 0, 0, FALSE, FALSE, FALSE, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifImgDescr_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifImgDescr *src = (Dz1GifImgDescr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v = 0;;
		DZ1_STREAM_WRITE1(dst, 0x2C, errp, ret);
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->x & 0xFFFF), Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->y & 0xFFFF), Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->width & 0xFFFF), Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->height & 0xFFFF), Dz1IOStreamEndian_little, errp, ret);

		if (src->lctPresent) v |= 0x80;
		if (src->isInterlaced) v |= 0x40;
		if (src->lctIsSorted) v |= 0x20;
		v |= (src->lctSizeExp & 0x7);
		DZ1_STREAM_WRITE1(dst, v, errp, ret);

		if (src->lctPresent) DZ1_IO_STREAM_FUNC(ret, Dz1GifColorArray_write(dst, src->palette, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifImgDescr_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifImgDescr *dst = (Dz1GifImgDescr *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u16_t v16 = 0;
		u8_t v;
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x2C) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_little, errp, ret); dst->x = (u32_t)v16;
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_little, errp, ret); dst->y = (u32_t)v16;
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_little, errp, ret); dst->width = (u32_t)v16;
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_little, errp, ret); dst->height = (u32_t)v16;

		DZ1_STREAM_READ1(&v, src, errp, ret);
		dst->lctPresent = (v & 0x80) ? TRUE : FALSE;
		dst->isInterlaced = (v & 0x40) ? TRUE : FALSE;
		dst->lctIsSorted = (v & 0x20) ? TRUE : FALSE;
		dst->lctSizeExp = (v & 0x7);

		if (dst->lctPresent)
		{
			if ((dst->palette = Dz1GifColorArray_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, Dz1GifColorArray_read(dst->palette, src, dst->lctSizeExp, param, errp), errp);
		}
	}
	return ret;
}
// Dz1GifImgDescr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderPlainTextExt CODEC
// static Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderPlainTextExt *ret = Dz1GifRenderPlainTextExt_new(0, 0, 0, 0, 0, 0, 0, 0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderPlainTextExt_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderPlainTextExt *src = (Dz1GifRenderPlainTextExt *)_src;
	if (src == NULL || src->text == NULL || strlen(src->text) == 0) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		DZ1_STREAM_WRITE1(dst, 0x21, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x01, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x0C, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->x, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->y, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->width, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->height, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->cellWidth, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->cellHeight, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->fgColorIdx, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->bgColorIdx, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_write(dst, (u8_t *)src->text, strlen(src->text), param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifRenderPlainTextExt_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderPlainTextExt *dst = (Dz1GifRenderPlainTextExt *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x21) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret);
		if (v != 0x01) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x0C) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ2(&dst->x, src, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_READ2(&dst->y, src, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_READ2(&dst->width, src, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_READ2(&dst->height, src, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_READ1(&dst->cellWidth, src, errp, ret);
		DZ1_STREAM_READ1(&dst->cellHeight, src, errp, ret);
		DZ1_STREAM_READ1(&dst->fgColorIdx, src, errp, ret);
		DZ1_STREAM_READ1(&dst->bgColorIdx, src, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_read((u8_t **)(&dst->text), NULL, src, param, errp), errp);
	}
	return ret;
}
// Dz1GifRenderPlainTextExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlExt CODEC
// static Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifGraphicControlExt *ret = Dz1GifGraphicControlExt_new(Dz1GifGraphicControlCmd_noMean, FALSE, FALSE, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifGraphicControlExt_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphicControlExt *src = (Dz1GifGraphicControlExt *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v = 0;
		DZ1_STREAM_WRITE1(dst, 0x21, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0xF9, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x04, errp, ret);

		v = (src->disposal & 0x7) << 2;
		if (src->userInput) v |= 0x2;
		if (src->tpColPresent) v |= 0x01;
		DZ1_STREAM_WRITE1(dst, v, errp, ret);

		DZ1_STREAM_WRITE2(dst, src->delay, Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->tpColorIdx, errp, ret);

		DZ1_STREAM_WRITE1(dst, 0, errp, ret);
	}
	return ret;
}

static ssize_t Dz1GifGraphicControlExt_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphicControlExt *dst = (Dz1GifGraphicControlExt *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x21) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0xF9) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x04) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);

		DZ1_STREAM_READ1(&v, src, errp, ret);
		dst->disposal = (Dz1GifGraphicControlCmd)((v >> 2) & 0x7);
		dst->userInput = (v & 0x2) ? TRUE : FALSE;
		dst->tpColPresent = (v & 0x01) ? TRUE : FALSE;

		DZ1_STREAM_READ2(&dst->delay, src, Dz1IOStreamEndian_little, errp, ret);
		// Dz1Thread_printf("### GIF Frame Delay = %u\n", dst->delay);
		DZ1_STREAM_READ1(&dst->tpColorIdx, src, errp, ret);

		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
	}
	return ret;
}
// Dz1GifGraphicControlExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifCommentExt CODEC
// static Dz1GifCommentExt *Dz1GifCommentExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifCommentExt *ret = Dz1GifCommentExt_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifCommentExt_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifCommentExt *src = (Dz1GifCommentExt *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		DZ1_STREAM_WRITE1(dst, 0x21, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0xFE, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_write(dst, (u8_t *)src->text, strlen(src->text), param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifCommentExt_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifCommentExt *dst = (Dz1GifCommentExt *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x21) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0xFE) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_read((u8_t **)(&dst->text), NULL, src, param, errp), errp);
	}
	return ret;
}
// Dz1GifCommentExt CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifAppExt CODEC
// static Dz1GifAppExt *Dz1GifAppExt_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifAppExt *ret = Dz1GifAppExt_new(NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifAppExt_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifAppExt *src = (Dz1GifAppExt *)_src;
	if (src == NULL || src->app_auth == NULL || src->app_auth->data == NULL || src->app_auth->size != 3) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		Dz1Binary *app_auth = src->app_auth, *app_data = src->app_data;
		char app[9] = { 0, }, ext[4] = { 0, };
		strncpy(app, src->app, 8);
		memcpy(ext, app_auth->data, 3);

		DZ1_STREAM_WRITE1(dst, 0x21, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x0B, errp, ret);
		DZ1_STREAM_WRITE(dst, (u8_t *)app, 8, errp, ret);
		DZ1_STREAM_WRITE(dst, (u8_t *)ext, 3, errp, ret);

		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_write(dst, app_data->data, app_data->size, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifAppExt_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifAppExt *dst = (Dz1GifAppExt *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		Dz1Binary *bin = NULL;
		char app[9] = { 0, }, ext[4] = { 0, };
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x21) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0xFF) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ1(&v, src, errp, ret); if (v != 0x0B) DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		DZ1_STREAM_READ((u8_t *)app, 8, src, errp, ret);
		if ((dst->app = Dz1Str_dup(app, errp)) == NULL) ERR_OUT_RET(errp, -1);

		DZ1_STREAM_READ((u8_t *)ext, 3, src, errp, ret);
		if ((dst->app_auth = Dz1Binary_new((u8_t *)ext, 3, errp)) == NULL) ERR_OUT_RET(errp, -1);

		if ((dst->app_data = bin = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			size_t ret_size = 0;
			ssize_t status = DataSubBlock_read((u8_t **)&(bin->data), &ret_size, src, param, errp);
			if (status < 0) ERR_OUT_RET(errp, -1);
			else
			{
				bin->size = (u32_t)ret_size;
				ret += status;
			}
		}
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

static ssize_t Dz1GifTableBasedImgData_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *src = (Dz1GifTableBasedImgData *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		Dz1Binary *lzw = src->lzw;
		DZ1_STREAM_WRITE1(dst, src->lzwMinimumCodeSize, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, DataSubBlock_write(dst, lzw->data, lzw->size, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifTableBasedImgData_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *dst = (Dz1GifTableBasedImgData *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		Dz1Binary *lzw = NULL;
		DZ1_STREAM_READ1(&dst->lzwMinimumCodeSize, src, errp, ret);
		if ((dst->lzw = lzw = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			size_t ret_size = 0;
			ssize_t status = DataSubBlock_read((u8_t **)&lzw->data, &ret_size, src, param, errp);
			if (status < 0) ERR_OUT_RET(errp, -1);
			else
			{
				lzw->size = (u32_t)ret_size;
				ret += status;
			}
		}
	}
	return ret;
}
// Dz1GifTableBasedImgData CODEC
////////////////////////////////////////////////////////////////////////////////
static ssize_t LzwPixel_write(Dz1Stream *dst, Dz1Binary *src,
							Dz1GifImgDescr *local_descr,
							void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *data = NULL;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((data = Dz1GifTableBasedImgData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		ssize_t status = 0;
		
		pthread_cleanup_push(Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);
		if ((*errp = _convert_pixels2LZW(data, src, local_descr)).code) { ERR_OUT(errp); ret = -1; }
		else if ((status = Dz1GifTableBasedImgData_write(dst, data, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else ret += status;
		pthread_cleanup_pop(1); // (Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);
	}
	return ret;
}

static __inline__ ssize_t LzwPixel_read(Dz1Binary *dst, Dz1Stream *src, Dz1GifImgDescr *local_descr, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifTableBasedImgData *data = NULL;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((data = Dz1GifTableBasedImgData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		ssize_t status = 0;
		
		pthread_cleanup_push(Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);

		if ((status = Dz1GifTableBasedImgData_read(data, src, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else if ((*errp = _convert_LZW2pixels(dst, data, local_descr)).code) { ERR_OUT(errp); ret = -1; }
		else ret += status;

		pthread_cleanup_pop(1); // (Dz1GifTableBasedImgData_delAndSetNull, (void *)&data);
	}
	return ret;
}


////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderTableBasedImg CODEC
// static Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderTableBasedImg *ret = Dz1GifRenderTableBasedImg_new(NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderTableBasedImg_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderTableBasedImg *src = (Dz1GifRenderTableBasedImg *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		DZ1_IO_STREAM_FUNC(ret, Dz1GifImgDescr_write(dst, src->descr, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, LzwPixel_write(dst, src->pixels, src->descr, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1GifRenderTableBasedImg_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderTableBasedImg *dst = (Dz1GifRenderTableBasedImg *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		if ((dst->descr = Dz1GifImgDescr_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, Dz1GifImgDescr_read(dst->descr, src, param, errp), errp);


//		dst->sync = sync;
		if ((dst->pixels = Dz1Binary_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((dst->lzw = Dz1GifTableBasedImgData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, Dz1GifTableBasedImgData_read(dst->lzw, src, param, errp), errp);

//		if ((dst->thid = _lzw_thread_decode(dst, errp)) == -1) ERR_OUT_RET(errp, -1);
	}
	return ret;
}
// Dz1GifRenderTableBasedImg CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingData CODEC
// static Dz1GifRenderingData *Dz1GifRenderingData_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifRenderingData *ret = Dz1GifRenderingData_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifRenderingData_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderingData *src = (Dz1GifRenderingData *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		switch(src->present)
		{
		case Dz1GifRenderingDataPresent_tbi:
			DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderTableBasedImg_write(dst, src->x.tbi, param, errp), errp);
			break;
		case Dz1GifRenderingDataPresent_pte:
			DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderPlainTextExt_write(dst, src->x.pte, param, errp), errp);
			break;
		default:
			DZ1_CODEC_ERRSET_RET(errp, EINVAL);
			break;
		}
	}
	return ret;
}

static ssize_t Dz1GifRenderingData_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifRenderingData *dst = (Dz1GifRenderingData *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v = 0;
		if (Dz1Stream_peek1(src, &v, errp) < 0) ERR_OUT_RET(errp, -1);
		else if (v == 0x2C)
		{
			if ((dst->x.__ptr__ = Dz1GifRenderTableBasedImg_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderTableBasedImg_read(dst->x.tbi, src, param, errp), errp);
				dst->present = Dz1GifRenderingDataPresent_tbi;
			}
		}
		else if (v == 0x21)
		{
			if ((dst->x.__ptr__ = Dz1GifRenderPlainTextExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderPlainTextExt_read(dst->x.pte, src, param, errp), errp);
				dst->present = Dz1GifRenderingDataPresent_pte;
			}
		}
		else
		{
			DZ1_CODEC_ERRSET_RET(errp, EAGAIN);
		}
	}
	return ret;
}
// Dz1GifRenderingData CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphic CODEC
// static Dz1GifGraphic *Dz1GifGraphic_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifGraphic *ret = Dz1GifGraphic_new(NULL, NULL, -1, FALSE, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifGraphic_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphic *src = (Dz1GifGraphic *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		if (src->gce != NULL)
			DZ1_IO_STREAM_FUNC(ret, Dz1GifGraphicControlExt_write(dst, src->gce, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderingData_write(dst, src->data, param, errp), errp);
	}
	return ret;
}

static ssize_t _Dz1GifDataEntry_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{	// Decode Extension only
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataEntry *dst = (Dz1GifDataEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t cp[2];
		if (Dz1Stream_peek(src, cp, 2, errp) < 0) ERR_OUT_RET(errp, -1);
		else if (cp[0] == 0x21 && cp[1] == 0xFF)
		{
			if ((dst->x.app_ext = Dz1GifAppExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifAppExt_read(dst->x.app_ext, src, param, errp), errp);
				dst->present = Dz1GifDataEntryPresent_app_ext;
			}
		}
		else if (cp[0] == 0x21 && cp[1] == 0xFE)
		{
			if ((dst->x.comment = Dz1GifCommentExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifCommentExt_read(dst->x.comment, src, param, errp), errp);
				dst->present = Dz1GifDataEntryPresent_comment;
			}
		}
	}
	return ret;
}

// static Dz1GifDataEntry *Dz1GifDataEntry_gen(Dz1Error *err);
static ssize_t _Dz1GifDataArr_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataArr *dst = (Dz1GifDataArr *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t status;
		bool_t done = FALSE;
		u8_t v;
		Dz1GifDataEntry *node = NULL;

		if (Dz1Stream_peek1(src, &v, errp) < 0) ERR_OUT_RET(errp, -1);
		while(errp->code == 0 && v != 0x3B && done == FALSE)
		{	// find block start
			while(v != 0x3B)
			{
				if (v == 0x21 || v == 0x2C) break;

				if ((status = Dz1Stream_read1(src, &v, errp)) < 0)
					ERR_OUT_RET(errp, -1);
				else if (status == 0) ERR_SETOUT_RET(errp, EPIPE, -1);
				else ret += 1;

				// stream end?
				if (Dz1Stream_peek1(src, &v, errp) < 0) ERR_OUT_RET(errp, -1);
			}

			if (v == 0x3B) break;

			if ((node = Dz1GifDataEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1GifDataEntry_delAndSetNull, (void *)&node);

				if ((status = _Dz1GifDataEntry_read(node, src, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if (status == 0) done = TRUE;
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					ret += status;
					node = NULL;
					Dz1Error_set(errp, 0);
				}

				pthread_cleanup_pop(1); // (Dz1GifDataEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

static ssize_t Dz1GifGraphic_read(void *_dst, Dz1Stream *src, Dz1GifDataArr *arr, Dz1GifDescr *descr, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1GifDecodeOpt *opt = (Dz1GifDecodeOpt *)param;

	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifGraphic *dst = (Dz1GifGraphic *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t cp[2];
		if (Dz1Stream_peek(src, cp, 2, errp) < 0) ERR_OUT_RET(errp, -1);

		if (cp[0] == 0x21 && cp[1] == 0xF9)
		{
			if ((dst->gce = Dz1GifGraphicControlExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, Dz1GifGraphicControlExt_read(dst->gce, src, param, errp), errp);
		}

		DZ1_IO_STREAM_FUNC(ret, _Dz1GifDataArr_read(arr, src, param, errp), errp);

		if ((dst->data = Dz1GifRenderingData_gen(errp)) == NULL) ERR_OUT(errp);
		else 
		{
			DZ1_IO_STREAM_FUNC(ret, Dz1GifRenderingData_read(dst->data, src, param, errp), errp);
			if ((*errp = Dz1GifDecodeOpt_sceneOper(opt, descr, dst)).code) DZ1_CODEC_ERR_RET(errp);
		}
	}
	return ret;
}


// Dz1GifGraphic CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntry CODEC
// static Dz1GifDataEntry *Dz1GifDataEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDataEntry *ret = Dz1GifDataEntry_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1GifDataEntry_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataEntry *src = (Dz1GifDataEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		switch(src->present)
		{
		case Dz1GifDataEntryPresent_graphic:
			DZ1_IO_STREAM_FUNC(ret, Dz1GifGraphic_write(dst, src->x.graphic, param, errp), errp);
			break;
		case Dz1GifDataEntryPresent_app_ext:
			DZ1_IO_STREAM_FUNC(ret, Dz1GifAppExt_write(dst, src->x.app_ext, param, errp), errp);
			break;
		case Dz1GifDataEntryPresent_comment:
			DZ1_IO_STREAM_FUNC(ret, Dz1GifCommentExt_write(dst, src->x.comment, param, errp), errp);
			break;
		default:
			DZ1_CODEC_ERRSET_RET(errp, EINVAL);
			break;
		}
	}
	return ret;
}

static ssize_t Dz1GifDataEntry_read(void *_dst, Dz1Stream *src, Dz1GifDataArr *arr, Dz1GifDescr *descr, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataEntry *dst = (Dz1GifDataEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t cp[2];
		if (Dz1Stream_peek(src, cp, 2, errp) < 0) ERR_OUT_RET(errp, -1);

		if (cp[0] == 0x21 && cp[1] == 0xFF)
		{
			if ((dst->x.app_ext = Dz1GifAppExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifAppExt_read(dst->x.app_ext, src, param, errp), errp);
				dst->present = Dz1GifDataEntryPresent_app_ext;
			}
		}
		else if (cp[0] == 0x21 && cp[1] == 0xFE)
		{
			if ((dst->x.comment = Dz1GifCommentExt_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifCommentExt_read(dst->x.comment, src, param, errp), errp);
				dst->present = Dz1GifDataEntryPresent_comment;
			}
		}
		else
		{
			if ((dst->x.graphic= Dz1GifGraphic_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, Dz1GifGraphic_read(dst->x.graphic, src, arr, descr, param, errp), errp);
				dst->present = Dz1GifDataEntryPresent_graphic;
			}
		}
	}
	return ret;
}
// Dz1GifDataEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataArr CODEC
// static __inline__ Dz1GifDataArr *Dz1GifDataArr_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1GifDataArr *ret = Dz1GifDataArr_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1GifDataArr_write(void *ptr, Dz1GifDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = Dz1GifDataEntry_write(arg->stream, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp); else arg->ret += status;
	return err;
}

static ssize_t Dz1GifDataArr_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataArr *src = (Dz1GifDataArr *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		Dz1ListStreamArg arg = { dst, 0, Dz1IOStreamEndian_big, param };
		if ((*errp = src->travel(src, _Dz1GifDataArr_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret; 
	}
	return ret;
}

static ssize_t Dz1GifDataArr_read(void *_dst, Dz1Stream *src, Dz1GifDescr *descr, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1GifDataArr *dst = (Dz1GifDataArr *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t v;
		Dz1GifDataEntry *node = NULL;
		if (Dz1Stream_peek1(src, &v, errp) < 0) ERR_OUT_RET(errp, -1);

		while(errp->code == 0 && v != 0x3B)
		{
			pthread_testcancel();
			while(v != 0x3B)
			{
				if (v == 0x21 || v == 0x2C) break;
				if ((*errp = Dz1Stream_skip(src, 1)).code) ERR_OUT_RET(errp, -1); else ret += 1;
				pthread_testcancel();
			}

			if (Dz1Stream_peek1(src, &v, errp) < 0) ERR_OUT_RET(errp, -1);
			if (v == 0x3B) break;

			if ((node = Dz1GifDataEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1GifDataEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1GifDataEntry_read(node, src, dst, descr, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					ret += status;
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1GifDataEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1GifDataArr CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Gif CODEC
ssize_t Dz1Gif_write(Dz1Stream *dst, Dz1Gif *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		
		DZ1_IO_STREAM_FUNC(ret, Dz1GifHeader_write(dst, src->hdr, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, Dz1GifDescr_write(dst, src->descr, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, Dz1GifDataArr_write(dst, src->datas, param, errp), errp);
		DZ1_STREAM_WRITE1(dst, 0x3B, errp, ret);
	}
	return ret;
}

typedef struct PostProcArg
{
	Dz1GifDecodeOpt *opt;
	Dz1Gif *dst;
	Dz1Error *ret_status;
} PostProcArg;

static void _Dz1GifDecodeOpt_postProc(void *ptr)
{
	PostProcArg *arg = (PostProcArg *)ptr;
	Dz1GifDecodeOpt *opt = arg->opt;
	Dz1Gif *dst = arg->dst;
	Dz1Error *errp = arg->ret_status;
	if ((*errp = Dz1GifDecodeOpt_postProc(opt, dst->datas)).code) ERR_OUT(errp);
}

static Dz1Error _find_resolution(void *ptr, Dz1GifDataEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->present == Dz1GifDataEntryPresent_graphic)
	{
		Dz1GifGraphic *g = p->x.graphic;
		Dz1GifRenderingData *rd = g->data;
		if (rd->present == Dz1GifRenderingDataPresent_tbi)
		{
			Dz1GifRenderTableBasedImg *tbi = rd->x.tbi;
			Dz1GifImgDescr *descr = tbi->descr;
			u16_t width = descr->x + descr->width;
			u16_t height = descr->y + descr->height;
			Dz1GifDescr *dst = (Dz1GifDescr *)ptr;
			if (dst->width < width) dst->width = width;
			if (dst->height < height) dst->height = height;
		}
	}
	Dz1Error_set(errp, 0);
	return err;
}

/*
static Dz1Error _count_graphic(void *ptr, Dz1GifDataEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->present == Dz1GifDataEntryPresent_graphic)
	{
		Dz1GifGraphic *g = p->x.graphic;
		Dz1GifRenderingData *rd = g->data;
		if (rd->present == Dz1GifRenderingDataPresent_tbi)
		{
			Dz1GifRenderTableBasedImg *tbi = rd->x.tbi;
			Dz1GifImgDescr *descr = tbi->descr;
			u16_t width = descr->x + descr->width;
			u16_t height = descr->y + descr->height;
			u32_t *dst = (u32_t *)ptr;
			(*dst)++;
		}
	}
	return err;
}

static u32_t _count_render_frame(Dz1GifDataArr *list)
{
	u32_t ret = 0;
	list->travel(list, _count_graphic, (void *)&ret);
	return ret;
}
*/

ssize_t Dz1Gif_read(Dz1Gif *dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	Dz1GifDecodeOpt *opt = (Dz1GifDecodeOpt *)param;

	if (src == NULL || dst == NULL || opt == NULL)
	{
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	}
	else
	{
		Dz1GifDescr *descr = NULL;
		Dz1Error post_proc_status = DZ1_ERROR_INITIALIZER;
		PostProcArg arg = { opt, dst, &post_proc_status };
		ssize_t status = 0;
		
		if ((dst->hdr = Dz1GifHeader_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, Dz1GifHeader_read(dst->hdr, src, param, errp), errp);

		if ((dst->descr = descr = Dz1GifDescr_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, Dz1GifDescr_read(dst->descr, src, param, errp), errp);

		pthread_cleanup_push(_Dz1GifDecodeOpt_postProc, (void *)&arg);
		if ((status = Dz1GifDataArr_read(dst->datas, src, dst->descr, param, errp)) < 0)
		{
//			if (_count_render_frame(dst->datas) > 0) Dz1Error_set(errp, 0);
//			else
			{ ERR_OUT(errp); ret = -1;}
		}
		else
		{
			ret += status;
			if (Dz1Stream_eof(src) == FALSE)
			{
				u8_t v = 0;
				if ((status = Dz1Stream_read1(src, &v, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if (v != 0x3B) { ERR_SET_OUT(errp, EPIPE); ret = -1; }
				else ret += status;
			}
		}

		pthread_cleanup_pop(1); // (_Dz1GifDecodeOpt_postProc, (void *)&arg);
		if (post_proc_status.code)
		{
			if (errp->code == 0) memcpy(errp, &post_proc_status, sizeof(Dz1Error));
			ret = -1;
		}

		if (descr->width == 0 || descr->height == 0)
		{
			dst->datas->travel(dst->datas, _find_resolution, (void *)descr);
		}
	}
	return ret;
}

ssize_t Dz1Gif_dec(Dz1Gif *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	ssize_t ret = 0;
	Dz1Stream *ins = Dz1Stream_openStaticBuf(src, size, TRUE, size, errp);
	if (ins == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ins);
		if ((ret = Dz1Gif_read(dst, ins, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&ins);
	}
	return ret;
}
// Dz1Gif CODEC
////////////////////////////////////////////////////////////////////////////////
