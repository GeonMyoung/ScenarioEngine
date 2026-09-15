#include <dz1_codec.h>
#include <dz1_bmp.h>

#if 0
ssize_t Dz1BMPDIB_enc(u8_t *dst, size_t size, Dz1BMPDIB *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, *size_ptr = NULL;
		size_t dummy_ret = 0, size_len = 4;

		size_ptr = cp;
		_DZ1_ENCODE4(cp, size, 0, errp, ret);

		_DZ1_ENCODE4(cp, size, src->width, errp, ret);
		_DZ1_ENCODE4(cp, size, src->height, errp, ret);

		_DZ1_ENCODE2(cp, size, src->planes, errp, ret);
		_DZ1_ENCODE2(cp, size, (u16_t)src->bpp, errp, ret);

		_DZ1_ENCODE4(cp, size, (u32_t)src->comp, errp, ret);
		_DZ1_ENCODE4(cp, size, src->decompress_size, errp, ret);

		_DZ1_ENCODE4(cp, size, src->horizontal_ppm, errp, ret);
		_DZ1_ENCODE4(cp, size, src->vertical_ppm, errp, ret);

		_DZ1_ENCODE4(cp, size, src->palette_color, errp, ret);
		_DZ1_ENCODE4(cp, size, src->important_color, errp, ret);

		_DZ1_ENCODE4(size_ptr, size_len, ret, errp, dummy_ret);
	}
	return ret;
}

ssize_t Dz1BMPDIB_dec(Dz1BMPDIB *dst, u8_t *src, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t temp16 = 0;
		u32_t temp32 = 0;

		_DZ1_DECODE4((u32_t *)&dst->hdr_size, cp, size, errp, ret);

		_DZ1_DECODE4((u32_t *)&dst->width, cp, size, errp, ret);
		_DZ1_DECODE4((u32_t *)&dst->height, cp, size, errp, ret);

		_DZ1_DECODE2(&dst->planes, cp, size, errp, ret);
		_DZ1_DECODE2(&temp16, cp, size, errp, ret); dst->bpp = (Dz1BMPBPP)temp16;

		_DZ1_DECODE4(&temp32, cp, size, errp, ret); dst->comp = (Dz1BMPComp)temp32;
		_DZ1_DECODE4(&dst->decompress_size, cp, size, errp, ret);

		_DZ1_DECODE4((u32_t *)&dst->horizontal_ppm, cp, size, errp, ret);
		_DZ1_DECODE4((u32_t *)&dst->vertical_ppm, cp, size, errp, ret);

		_DZ1_DECODE4(&dst->palette_color, cp, size, errp, ret);
		_DZ1_DECODE4(&dst->important_color, cp, size, errp, ret);
	}
	return ret;
}

ssize_t Dz1BMP_enc(u8_t *dst, size_t size, Dz1BMP *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, *size_ptr = NULL, *offset_ptr = NULL;
		size_t dummy_ret = 0, size_len = 4, offset_len = 4;
		u32_t offset = 0;

		DZ1_ENCODE1(cp, size, (u8_t)'B', errp, ret);							// 1
		DZ1_ENCODE1(cp, size, (u8_t)'M', errp, ret);							// 2

		size_ptr = cp;
		_DZ1_ENCODE4(cp, size, 0, errp, ret);	// dummy_size					// 3 4 5 6

		_DZ1_ENCODE2(cp, size, 0, errp, ret);	// reserved 2					// 7
		_DZ1_ENCODE2(cp, size, 0, errp, ret);	// reserved 2					// 8

		// ---------------------------------------------------------------- 8 byte header

		offset_ptr = cp;
		_DZ1_ENCODE4(cp, size, 0, errp, ret);									// 9 10 11 12
		// ---------------------------------------------------------------- 4 byte offset

		DZ1_CODEC_FUNC(cp, size, ret, Dz1BMPDIB_enc(cp, size, src->hdr, errp), errp);	// 13 14 15 16 17 18 19 20 21 22
																						// 23 24 25 26 27 28 29 30 31 32
																						// 33 24 25 26 27 28 29 30 31 32
																						// 43 44 45 46 47 48 49 50 51 52
		offset = (u32_t)(cp - dst);
		_DZ1_ENCODE4(offset_ptr, offset_len, offset, errp, dummy_ret);

		if (src->image != NULL)
		{
//			Dz1Binary *image = src->image;
//			if (image->data != NULL && image->size != 0)
//				DZ1_ENCODE(cp, size, image->data, image->size, errp, ret);
			DZ1_ENCODE(cp, size, src->image, src->hdr->decompress_size, errp, ret);
		}

		_DZ1_ENCODE4(size_ptr, size_len, ret, errp, dummy_ret);
	}
	return ret;
}

#endif

///////////////////////////////////////////////////////////////////////////////
// Misc Pixel Functions
///////////////////////////////////////////////////////////////////////////////
static u32_t Dz1BMP_getIdx(Dz1BMP *src, u32_t x, u32_t y)
{
	Dz1BMPDIB *h = src->hdr;
	u32_t byte_width, byte_mod, byte_x;
	u32_t idx = 0;
	switch(h->bpp)
	{
	case Dz1BMPBPP_bw:			
		byte_x = x >> 3;
		byte_width = (h->width >> 3) + (h->width & 0x7 ? 1 : 0);
		break;
	case Dz1BMPBPP_color16:
		byte_x = x >> 1;
		byte_width = (h->width >> 1) + (h->width & 0x1 ? 1 : 0);
		break;
	case Dz1BMPBPP_color256:
		byte_x = x;
		byte_width = h->width;
		break;
	case Dz1BMPBPP_color64K:
		byte_x = x << 1;
		byte_width = h->width << 1;
		break;
	case Dz1BMPBPP_colorTrue:
		byte_x = (x << 1) + x;
		byte_width = (h->width << 1) + h->width;
		break;
	case Dz1BMPBPP_colorTrue32:
		byte_x = (x << 2);
		byte_width = (h->width << 2);
		break;
	default:
		return -1;
		break;
	}
	byte_mod = byte_width & 0x3;
	byte_width += byte_mod ? (4 - byte_mod) : 0;
	idx = byte_width * y + byte_x;
	return idx;
}

static void _set_bit(u8_t *buf, u32_t idx, u32_t bit) { buf[idx] |= (0x80 >> bit); }
static void _clr_bit(u8_t *buf, u32_t idx, u32_t bit) { buf[idx] &= ~(0x80 >> bit); }
static u8_t _get_bit(u8_t *buf, u32_t idx, u32_t bit)
{
	u8_t mask = 0x80 >> bit;
	if (buf[idx] & mask) return 1;
	else return 0;
}

static void _set_nibble(u8_t *buf, u32_t idx, u32_t nibble, u8_t color_nibble)
{
	if (nibble == 0)
		buf[idx] = (buf[idx] & 0x0F) | ((color_nibble & 0x0F) << 4);
	else
		buf[idx] = (buf[idx] & 0xF0) | (color_nibble & 0x0F);
}

static u8_t _get_nibble(u8_t *buf, u32_t idx, u32_t nibble)
{
	if (nibble == 0)
		return (buf[idx] & 0xF0) >> 4;
	return (buf[idx] & 0x0F);
}

static Dz1Error Dz1BMP_setPixel(Dz1BMP *dst, s32_t x, s32_t y, u8_t r, u8_t g, u8_t b)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1BMPDIB *h = dst->hdr;
//	Dz1Binary *image = dst->image;
	u8_t *img = dst->image;
	u32_t idx = Dz1BMP_getIdx(dst, x, y), shi;
	u8_t *cp = (img + idx);
	switch(h->bpp)
	{
	case Dz1BMPBPP_bw:
		shi = x & 0x7;
		if (r) _set_bit(img, idx, shi);
		else _clr_bit(img, idx, shi);
		break;
	case Dz1BMPBPP_color16:
		shi = x & 0x1;
		_set_nibble(img, idx, shi, r & 0xF);
		break;
	case Dz1BMPBPP_color256:
		img[idx] = r;
		break;
	case Dz1BMPBPP_color64K:
		img[idx] = r;
		img[idx + 1] = g;
		break;
	case Dz1BMPBPP_colorTrue32:
	case Dz1BMPBPP_colorTrue:
		*cp++ = b;
		*cp++ = g;
		*cp++ = r;
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		idx = -1;
		break;
	}
	return err;
}

static Dz1Error Dz1BMP_getPixel(Dz1BMP *dst, s32_t x, s32_t y, u8_t *r, u8_t *g, u8_t *b)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t _r = 0, *rp = r ? r : &_r;
	u8_t _g = 0, *gp = g ? g : &_g;
	u8_t _b = 0, *bp = b ? b : &_b;

	Dz1BMPDIB *h = dst->hdr;
	u8_t *img = dst->image;
	u32_t idx = Dz1BMP_getIdx(dst, x, y), shi;
	u8_t *cp = img + idx;
	switch(h->bpp)
	{
	case Dz1BMPBPP_bw:
		shi = x & 0x7;
		if (r == NULL) ERR_SET_OUT(&err, EINVAL);
		else (*r) = _get_bit(img, idx, shi);
		break;
	case Dz1BMPBPP_color16:
		shi = x & 0x1;
		if (r == NULL) ERR_SET_OUT(&err, EINVAL);
		else (*r) = _get_nibble(img, idx, shi);
		break;
	case Dz1BMPBPP_color256:
		if (r == NULL) ERR_SET_OUT(&err, EINVAL);
		else (*r) = img[idx];
		break;
	case Dz1BMPBPP_color64K:
		if (r == NULL) ERR_SET_OUT(&err, EINVAL);
		else (*r) = img[idx];

		if (g == NULL) ERR_SET_OUT(&err, EINVAL);
		else (*g) = img[idx + 1];
		break;
	case Dz1BMPBPP_colorTrue32:
	case Dz1BMPBPP_colorTrue:
		(*bp) = *cp++;
		(*gp) = *cp++;
		(*rp) = *cp++;
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		idx = -1;
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Pixel Function : Black & White Image
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1BMP_getPixelBW(Dz1BMP *dst, s32_t x, s32_t y, bool_t *c)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (c == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		u8_t w = 0;
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_bw) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_getPixel(dst, x, y, &w, 0, 0)).code) ERR_OUT(&err);
		else (*c) = (bool_t)w;
	}
	return err;
}

Dz1Error Dz1BMP_setPixelBW(Dz1BMP *dst, s32_t x, s32_t y, bool_t c)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_bw) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_setPixel(dst, x, y, c, 0, 0)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Pixel Function : 16 color
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1BMP_getPixel16(Dz1BMP *dst, s32_t x, s32_t y, u8_t *color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color16) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_getPixel(dst, x, y, color, 0, 0)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1BMP_setPixel16(Dz1BMP *dst, s32_t x, s32_t y, u8_t color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color16) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_setPixel(dst, x, y, color, 0, 0)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Pixel Function : 256 color
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1BMP_getPixel256(Dz1BMP *dst, s32_t x, s32_t y, u8_t *color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color256) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_getPixel(dst, x, y, color, 0, 0)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1BMP_setPixel256(Dz1BMP *dst, s32_t x, s32_t y, u8_t color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color256) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_setPixel(dst, x, y, color, 0, 0)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Pixel Function : 64K color
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1BMP_getPixel64K(Dz1BMP *dst, s32_t x, s32_t y, u16_t *color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (color == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		u8_t high = 0, low = 0;
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color64K) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_getPixel(dst, x, y, &high, &low, 0)).code) ERR_OUT(&err);
		else (*color) = (((u16_t)high & 0xFF) << 8) | ((u16_t)low & 0xFF);
	}
	return err;
}

Dz1Error Dz1BMP_setPixel64K(Dz1BMP *dst, s32_t x, s32_t y, u16_t color)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1BMPDIB *h = dst->hdr;
		if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
		else if (h->bpp != Dz1BMPBPP_color64K) ERR_SET_OUT(&err, EINVAL);
		else if ((err = Dz1BMP_setPixel(dst, x, y, (u8_t)((color >> 8) & 0xFF), (u8_t)(color & 0xFF), 0)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Pixel Function : True color
///////////////////////////////////////////////////////////////////////////////
void Dz1BMP_getPixelTrueColor(Dz1BMP *dst, s32_t x, s32_t y, u32_t *r, u32_t *g, u32_t *b)
{
	if (dst == NULL) { }
	else
	{
		// Dz1BMPDIB *h = dst->hdr;
		if (0) { }
//		else if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
//		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
//		else if (h->bpp != Dz1BMPBPP_colorTrue && h->bpp != Dz1BMPBPP_colorTrue32) ERR_SET_OUT(&err, EINVAL);
//		else if ((err = Dz1BMP_getPixel(dst, x, y, r, g, b)).code) ERR_OUT(&err);
		else
		{
			u32_t _r = 0, *rp = r ? r : &_r;
			u32_t _g = 0, *gp = g ? g : &_g;
			u32_t _b = 0, *bp = b ? b : &_b;

			// Dz1BMPDIB *h = dst->hdr;
			u8_t *img = dst->image;
			u32_t idx = Dz1BMP_getIdx(dst, x, y);
			u8_t *cp = img + idx;
			(*bp) = *cp++;
			(*gp) = *cp++;
			(*rp) = *cp++;
		}
	}
}

void Dz1BMP_setPixelTrueColor(Dz1BMP *dst, s32_t x, s32_t y, u32_t r, u32_t g, u32_t b)
{
	if (dst == NULL) { }
	else
	{
		// Dz1BMPDIB *h = dst->hdr;
		if (0) { }
//		else if (h->width <= x) ERR_SET_OUT(&err, EINVAL);
//		else if (h->height <= y) ERR_SET_OUT(&err, EINVAL);
//		else if (h->bpp != Dz1BMPBPP_colorTrue && h->bpp != Dz1BMPBPP_colorTrue32) ERR_SET_OUT(&err, EINVAL);
//		else if ((err = Dz1BMP_setPixel(dst, x, y, r, g, b)).code) ERR_OUT(&err);
		else
		{
			u8_t *img = dst->image;
			u32_t idx = Dz1BMP_getIdx(dst, x, y);
			u8_t *cp = (img + idx);
			*cp++ = b;
			*cp++ = g;
			*cp++ = r;
		}
	}
}

Dz1BMP *Dz1BMP_create(s32_t width, s32_t height, Dz1BMPBPP bpp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1BMP *ret = Dz1BMP_new(NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		u32_t pixel_byte_size = bpp >> 3;

		Dz1Binary *chunk = NULL;

		u32_t byte_size;
		u32_t byte_width = width * pixel_byte_size;
		u32_t byte_mod = byte_width & 0x3;
		u32_t total_size = 10 + 4 + 40;

		byte_width += (byte_mod ? 4 - byte_mod : 0);	// width를 4에 정렬

		byte_size = byte_width * height;
		total_size += byte_size;

		pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&ret);

		if ((ret->hdr = Dz1BMPDIB_new(40, width, height, 1, bpp, Dz1BMPComp_RGB, byte_size, 1084, 1084, 0, 0, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->chunk = chunk = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, total_size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			size_t size = sizeof(Dz1BMPDIB);
			// Dz1BMPDIB *hdp = NULL;
			u32_t offset = 54;
			u8_t *chp = chunk->data;

			*chp++ = 'B';									// 1
			*chp++ = 'M';									// 2
			memcpy(chp, &total_size, 4); chp += 4;			// 3,4,5,6
			*chp++ = 0;										// 7
			*chp++ = 0;										// 8
			*chp++ = 0;										// 9
			*chp++ = 0;										// 10
			memcpy(chp, &offset, 4); chp += 4;				// 11,12,13,14
			memcpy(chp, ret->hdr, size); chp += size;

			ret->image = chp;
		}

		/*
		else if ((ret->image = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, byte_size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		*/

		pthread_cleanup_pop(errp->code); // (Dz1BMP_delAndSetNull, (void *)&ret);
	}
	return ret;
}

#define WIDTHBYTES(bits)      ((((bits) + 31)>>5)<<2)

u32_t Dz1BMP_getRowSize(Dz1BMP *bmp)
{
	Dz1BMPDIB *hdr = bmp->hdr;
	u32_t byte_width = WIDTHBYTES(hdr->width * hdr->planes * hdr->bpp);

//	u32_t color_size = hdr->bpp / 8;
//	u32_t byte_width = hdr->width * color_size;
//	u32_t byte_mod = byte_width & 0x3;
//	byte_width += (byte_mod ? 4 - byte_mod : 0);

	return byte_width;
}

u8_t *Dz1BMP_getRowStridePtr(Dz1BMP *p, u32_t y, bool_t flipTopBottom, Dz1Error *err)
{
	u8_t *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1BMPDIB *hdr = p->hdr;
		u32_t height = hdr->height < 0 ? (u32_t)(-hdr->height) : (u32_t)hdr->height;
		if (y >= height) ERR_SET_OUT(errp, EINVAL);
		else
		{
			u32_t byte_width = Dz1BMP_getRowSize(p);
			u8_t *data = p->image;

			if (flipTopBottom) y = (height - 1) - y;

			ret = (u8_t *)(data + (byte_width * y));
		}
	}
	return ret;
}

Dz1BMP *Dz1BMP_fromDz1BMP(Dz1BMP *src, int scale, Dz1Error *err)
{
	Dz1BMP *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || scale == 0 || scale > 4) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1BMPDIB *hdr = src->hdr;
		if ((ret = Dz1BMP_create(hdr->width * scale, hdr->height * scale, hdr->bpp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t r, g, b;
			int y, x, sy, sx;
			pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&ret);
			for (y = 0; errp->code == 0 && y < hdr->height; y++)
			{
				for (x = 0; errp->code == 0 && x < hdr->width; x++)
				{
					if ((*errp = Dz1BMP_getPixel(src, x, y, &r, &g, &b)).code) ERR_OUT(errp);
					else
					{
						for (sy = 0; errp->code == 0 && sy < scale; sy++)
						{
							for (sx = 0; errp->code == 0 && sx < scale; sx++)
							{
								if ((*errp = Dz1BMP_setPixel(ret, (x * scale) + sx, (y * scale) + sy, r, g, b)).code) ERR_OUT(errp);
							}
						}
					}
				}
			}
			pthread_cleanup_pop(errp->code); // (Dz1BMP_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

Dz1Error Dz1BMP_fill(Dz1BMP *dst, u8_t red, u8_t green, u8_t blue)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u16_t x, y;
		Dz1BMPDIB *hdr = dst->hdr;
		for (y = 0; y < hdr->height; y++)
		{
			for (x = 0; x < hdr->width; x++)
			{
				Dz1BMP_setPixelTrueColor(dst, x, y, red, green, blue);
			}
		}
	}
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Function For WIN32
///////////////////////////////////////////////////////////////////////////////

void Dz1BMP_del(Dz1BMP *p)
{
	if (p == NULL) return;
	if (p->hdr) Dz1BMPDIB_del(p->hdr);
	if (p->chunk) Dz1Binary_del(p->chunk);
	Dz1Free(p);
}

