#ifndef DZ1_BMP_H
#define DZ1_BMP_H

#include <dz1_io_stream.h>
#include <dz1_bmp_def.h>

//DZ1_CPPLINK ssize_t Dz1BMPDIB_enc(u8_t *dst, size_t size, Dz1BMPDIB *src, Dz1Error *err);
//DZ1_CPPLINK ssize_t Dz1BMPDIB_dec(Dz1BMPDIB *dst, u8_t *src, size_t size, Dz1Error *err);

//DZ1_CPPLINK Dz1BMP *Dz1BMP_gen(Dz1Error *err);
//DZ1_CPPLINK ssize_t Dz1BMP_enc(u8_t *dst, size_t size, Dz1BMP *src, Dz1Error *err);
//DZ1_CPPLINK ssize_t Dz1BMP_dec(Dz1BMP *dst, u8_t *src, size_t size, Dz1Error *err);

DZ1_CPPLINK void		 Dz1BMP_getPixelTrueColor(Dz1BMP *dst, s32_t x, s32_t y, u32_t *r, u32_t *g, u32_t *b);
DZ1_CPPLINK void		 Dz1BMP_setPixelTrueColor(Dz1BMP *dst, s32_t x, s32_t y, u32_t r, u32_t g, u32_t b);

//DZ1_CPPLINK Dz1Error Dz1BMP_getPixelTrueColorAlpha(Dz1BMP *dst, s32_t x, s32_t y, u8_t *r, u8_t *g, u8_t *b, u8_t *alpha);
//DZ1_CPPLINK Dz1Error Dz1BMP_setPixelTrueColorAlpha(Dz1BMP *dst, s32_t x, s32_t y, u8_t r, u8_t g, u8_t b, u8_t alpha);

DZ1_CPPLINK Dz1BMP		*Dz1BMP_create(s32_t width, s32_t height, Dz1BMPBPP bpp, Dz1Error *err);
////////////////////////////////////////////////////////////////////////////////////////
// BMP IO
DZ1_CPPLINK Dz1BMP		*Dz1BMPA_load(str_t fn, Dz1Error *err);
DZ1_CPPLINK Dz1BMP		*Dz1BMPA_load2(str_t path, str_t name, Dz1Error *err);
#ifdef WIN32
DZ1_CPPLINK Dz1BMP		*Dz1BMPW_load(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK Dz1BMP		*Dz1BMPW_load2(wstr_t path, wstr_t name, Dz1Error *err);
#endif
#ifdef UNICODE
#define Dz1BMP_load		 Dz1BMPW_load
#define Dz1BMP_load2	 Dz1BMPW_load2
#else
#define Dz1BMP_load		 Dz1BMPA_load
#define Dz1BMP_load2	 Dz1BMPA_load2
#endif
//DZ1_CPPLINK Dz1BMP		*Dz1BMP_gen(Dz1Error *err);

DZ1_CPPLINK ssize_t		 Dz1BMP_read(Dz1BMP *dst, Dz1Stream *src, Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1BMP_write(Dz1Stream *dst, Dz1BMP *src, Dz1Error *err);

DZ1_CPPLINK ssize_t		 Dz1BMP_enc(u8_t *dst, size_t size, Dz1BMP *src, Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1BMP_dec(Dz1BMP *dst, u8_t *src, size_t size, Dz1Error *err);
// BMP IO
////////////////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK u8_t		*Dz1BMP_getRowStridePtr(Dz1BMP *p, u32_t y, bool_t flipTopBottom, Dz1Error *err);
DZ1_CPPLINK u32_t		 Dz1BMP_getRowSize(Dz1BMP *bmp);

DZ1_CPPLINK Dz1Error	Dz1BMP_fill(Dz1BMP *dst, u8_t red, u8_t green, u8_t blue);
DZ1_CPPLINK Dz1Error	Dz1BMP_copyImage(Dz1BMP *dst, Dz1BMP *src); 
DZ1_CPPLINK Dz1Error	Dz1BMP_setImagedata(Dz1BMP *dst, Dz1Binary *bits);




















#ifdef WIN32
#include <WinGDI.h>
static __inline__ HBITMAP MakeDIBSection(HDC dc, int width, int height, Dz1BMPBPP bpp)
{
	BITMAPINFO bmi;
	LPVOID pBits;
	HBITMAP hBitmap;
	memset(&bmi.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = (u16_t)bpp;
	hBitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	return hBitmap;
}

static __inline__ void delete_HBITMAPAndSetNull(void *ptr)
{
	HBITMAP *p = (HBITMAP *)ptr;
	DeleteObject(*p);
	(*p) = NULL;
}

static HBITMAP __inline__ Dz1BMP_toHBITMAP(HDC dc, Dz1BMP *src, Dz1Error *err)
{
	HBITMAP ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || src->image == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1BMPDIB *hdr = src->hdr;
		if ((ret = MakeDIBSection(dc, hdr->width, hdr->height, (Dz1BMPBPP)hdr->bpp)) == NULL)
			ERR_SET_OUT(errp, EFAULT);
		else
		{
			BITMAPINFO bmi;
//			Dz1Binary *img = src->image;
			u8_t *img = src->image;
			pthread_cleanup_push(delete_HBITMAPAndSetNull, (void *)&ret);

			memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = hdr->width;
			bmi.bmiHeader.biHeight = hdr->height;
			bmi.bmiHeader.biPlanes = hdr->planes;
			bmi.bmiHeader.biBitCount = (u16_t)hdr->bpp;
			bmi.bmiHeader.biCompression = (u32_t)hdr->comp;
			bmi.bmiHeader.biSizeImage = hdr->decompress_size;
			bmi.bmiHeader.biXPelsPerMeter = hdr->horizontal_ppm;
			bmi.bmiHeader.biYPelsPerMeter = hdr->vertical_ppm;
			bmi.bmiHeader.biClrUsed = hdr->palette_color;
			bmi.bmiHeader.biClrImportant = hdr->important_color;
			if (SetDIBits(dc, ret, 0, hdr->height, src->image, &bmi, DIB_RGB_COLORS) == 0)
				ERR_SET_OUT(errp, EFAULT);

			pthread_cleanup_pop(errp->code); // (delete_HBITMAPAndSetNull, (void *)&ret);
		}
	}
	return ret;
}
#endif

DZ1_CPPLINK DZ1_DLLPORT Dz1BMP *Dz1BMP_fromDz1BMP(Dz1BMP *src, int scale, Dz1Error *err);

#endif