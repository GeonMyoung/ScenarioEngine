#ifndef DZ1_GDI_UTIL_H
#define DZ1_GDI_UTIL_H

#include <dz1_error.h>
#include <dz1_mfc.h>

DZ1_CPPLINK HBITMAP Dz1MfcGdiUtil_MakeDIBSection(HDC dc, int width, int height, u16_t bpp);
DZ1_CPPLINK HBITMAP Dz1MfcGdiUtil_scaleBitmap(CDC *pDC,
										   u16_t dstWidth, u16_t dstHeight,
										   HBITMAP srcBitmap,
										   u16_t srcWidth, u16_t srcHeight,
										   bool_t keepAspect,
										   Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MfcGdiUtil_scaleBitmap2(CDC *pDC,
											  HBITMAP hScaled, u16_t dstWidth, u16_t dstHeight,
											  HBITMAP srcBitmap, u16_t srcWidth, u16_t srcHeight,
											  bool_t keepAspect, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// TDC Support
DZ1_CPPLINK void HBITMAP_del(HBITMAP hBitmap);
static __inline__ void HBITMAP_delAndSetNull(void *pptr)
{
	HBITMAP *hBitmap = (HBITMAP *)pptr;
	HBITMAP_del( (*hBitmap) ); (*hBitmap) = NULL;
}
// TDC Support
///////////////////////////////////////////////////////////////////////////////

#endif