#include "stdafx.h"
#include "Dz1MfcGdiUtil.h"
HBITMAP Dz1MfcGdiUtil_MakeDIBSection(HDC dc, int width, int height, u16_t bpp)
{
	BITMAPINFO bmi;
	LPVOID pBits = NULL;
	HBITMAP hBitmap;
	memset(&bmi.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biBitCount = (u16_t)bpp;
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = (u16_t)bpp;
	hBitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	return hBitmap;
}


static void _clean_cDC(void *ptr)
{
	CDC *memDC = (CDC *)ptr;
	memDC->DeleteDC();
}

void HBITMAP_del(HBITMAP hBitmap)
{
	if (hBitmap != NULL) DeleteObject(hBitmap);
}

bool_t Dz1MfcGdiUtil_scaleBitmap2(CDC *pDC,
								  HBITMAP hScaled, u16_t dstWidth, u16_t dstHeight,
								  HBITMAP srcBitmap, u16_t srcWidth, u16_t srcHeight,
								  bool_t keepAspect, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (keepAspect)
	{
		double factor = (double)dstWidth / (double)srcWidth;
		double tmpHeight = (double)srcHeight * factor;
		if (tmpHeight > dstHeight)
		{
			factor = (double)dstHeight / (double)srcHeight;
			dstWidth = (u16_t)((double)srcWidth * factor);
		}
		else dstHeight = (u16_t)tmpHeight;
	}

	CDC origDC;
	if (origDC.CreateCompatibleDC(pDC) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(_clean_cDC, (void *)&origDC);

		CDC scaleDC;
		if (scaleDC.CreateCompatibleDC(pDC) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(_clean_cDC, (void *)&scaleDC);

			HGDIOBJ originalOld = origDC.SelectObject(srcBitmap);
			HGDIOBJ scaleOld = scaleDC.SelectObject(hScaled);

			scaleDC.SetStretchBltMode(COLORONCOLOR);
			if (scaleDC.StretchBlt(0, 0, dstWidth, dstHeight, &origDC, 0, 0, srcWidth, srcHeight, SRCCOPY) == 0) ERR_SET_OUT(errp, EFAULT);

			scaleDC.SelectObject(scaleOld);
			origDC.SelectObject(originalOld);
			ret = TRUE;

			pthread_cleanup_pop(1); // (_clean_cDC, (void *)&scaleDC);
		}
		pthread_cleanup_pop(1); // (_cleanup_cDC, (void *)&memDC);
	}
	return ret;
}

HBITMAP Dz1MfcGdiUtil_scaleBitmap(CDC *pDC,
							   u16_t dstWidth, u16_t dstHeight,
							   HBITMAP srcBitmap,
							   u16_t srcWidth, u16_t srcHeight,
							   bool_t keepAspect,
							   Dz1Error *err)
{
	HBITMAP hScaled = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (keepAspect)
	{
		double factor = (double)dstWidth / (double)srcWidth;
		double tmpHeight = (double)srcHeight * factor;
		if (tmpHeight > dstHeight)
		{
			factor = (double)dstHeight / (double)srcHeight;
			dstWidth = (u16_t)((double)srcWidth * factor);
		}
		else dstHeight = (u16_t)tmpHeight;
	}

	CDC origDC;
	if (origDC.CreateCompatibleDC(pDC) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(_clean_cDC, (void *)&origDC);

		CDC scaleDC;
		if (scaleDC.CreateCompatibleDC(pDC) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(_clean_cDC, (void *)&scaleDC);

			if ((hScaled = Dz1MfcGdiUtil_MakeDIBSection(pDC->m_hDC, dstWidth, dstHeight, 32)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(HBITMAP_delAndSetNull, (void *)hScaled);

				HGDIOBJ originalOld = origDC.SelectObject(srcBitmap);
				HGDIOBJ scaleOld = scaleDC.SelectObject(hScaled);

				scaleDC.SetStretchBltMode(COLORONCOLOR);
				if (scaleDC.StretchBlt(0, 0, dstWidth, dstHeight, &origDC, 0, 0, srcWidth, srcHeight, SRCCOPY) == 0) ERR_SET_OUT(errp, EFAULT);

				scaleDC.SelectObject(scaleOld);
				origDC.SelectObject(originalOld);

				pthread_cleanup_pop(errp->code); // (_clean_hBitmap, (void *)hScaled);
			}
			pthread_cleanup_pop(1); // (_clean_cDC, (void *)&scaleDC);
		}
		pthread_cleanup_pop(1); // (_cleanup_cDC, (void *)&memDC);
	}
	return hScaled;
}

