#ifndef _DZ1_TDC_DZ1_BMP_DEF_H_
#define _DZ1_TDC_DZ1_BMP_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPBPP
typedef enum Dz1BMPBPP
{
	Dz1BMPBPP_bw = 1,
	Dz1BMPBPP_color16 = 4,
	Dz1BMPBPP_color256 = 8,
	Dz1BMPBPP_color64K = 16,
	Dz1BMPBPP_colorTrue = 24,
	Dz1BMPBPP_colorTrue32 = 32,
	Dz1BMPBPP_max
} Dz1BMPBPP;

DZ1_CPPLINK str_t Dz1BMPBPPStrA(Dz1BMPBPP v);
DZ1_CPPLINK Dz1BMPBPP Dz1BMPBPPFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1BMPBPPStrW(Dz1BMPBPP v);
DZ1_CPPLINK Dz1BMPBPP Dz1BMPBPPFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1BMPBPPStr Dz1BMPBPPStrW
#define Dz1BMPBPPFromStr Dz1BMPBPPFromStrW
#else // UNICODE
#define Dz1BMPBPPStr Dz1BMPBPPStrA
#define Dz1BMPBPPFromStr Dz1BMPBPPFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1BMPBPPStr Dz1BMPBPPStrA
#define Dz1BMPBPPFromStr Dz1BMPBPPFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1BMPBPP *Dz1BMPBPP_new(Dz1BMPBPP *src, Dz1Error *err);
static __inline__ Dz1BMPBPP *Dz1BMPBPP_gen(Dz1Error *err) { Dz1BMPBPP v = Dz1BMPBPP_max; return Dz1BMPBPP_new(&v, err); }
static __inline__ void Dz1BMPBPP_del(Dz1BMPBPP *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1BMPBPP_delAndSetNull(void *ptr)
{
	Dz1BMPBPP **p = (Dz1BMPBPP **)ptr;
	if (p != NULL) { Dz1BMPBPP_del(*p); *p = NULL; }
}
// Dz1BMPBPP
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPComp
typedef enum Dz1BMPComp
{
	Dz1BMPComp_RGB,
	Dz1BMPComp_RLE8,
	Dz1BMPComp_RLE4,
	Dz1BMPComp_BITFIELDS,
	Dz1BMPComp_JPEG,
	Dz1BMPComp_PNG,
	Dz1BMPComp_max
} Dz1BMPComp;

DZ1_CPPLINK str_t Dz1BMPCompStrA(Dz1BMPComp v);
DZ1_CPPLINK Dz1BMPComp Dz1BMPCompFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1BMPCompStrW(Dz1BMPComp v);
DZ1_CPPLINK Dz1BMPComp Dz1BMPCompFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1BMPCompStr Dz1BMPCompStrW
#define Dz1BMPCompFromStr Dz1BMPCompFromStrW
#else // UNICODE
#define Dz1BMPCompStr Dz1BMPCompStrA
#define Dz1BMPCompFromStr Dz1BMPCompFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1BMPCompStr Dz1BMPCompStrA
#define Dz1BMPCompFromStr Dz1BMPCompFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1BMPComp *Dz1BMPComp_new(Dz1BMPComp *src, Dz1Error *err);
static __inline__ Dz1BMPComp *Dz1BMPComp_gen(Dz1Error *err) { Dz1BMPComp v = Dz1BMPComp_max; return Dz1BMPComp_new(&v, err); }
static __inline__ void Dz1BMPComp_del(Dz1BMPComp *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1BMPComp_delAndSetNull(void *ptr)
{
	Dz1BMPComp **p = (Dz1BMPComp **)ptr;
	if (p != NULL) { Dz1BMPComp_del(*p); *p = NULL; }
}
// Dz1BMPComp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPDIB
typedef struct Dz1BMPDIB
{
	u32_t		hdr_size;
	s32_t		width;
	s32_t		height;
	u16_t		planes;
	u16_t		bpp;
	u32_t		comp;
	u32_t		decompress_size;
	s32_t		horizontal_ppm;
	s32_t		vertical_ppm;
	u32_t		palette_color;
	u32_t		important_color;
} Dz1BMPDIB;

DZ1_CPPLINK DZ1_DLLPORT Dz1BMPDIB *Dz1BMPDIB_new(u32_t hdr_size, 
												 s32_t width, 
												 s32_t height, 
												 u16_t planes, 
												 u16_t bpp, 
												 u32_t comp, 
												 u32_t decompress_size, 
												 s32_t horizontal_ppm, 
												 s32_t vertical_ppm, 
												 u32_t palette_color, 
												 u32_t important_color, Dz1Error *err);
static __inline__ Dz1BMPDIB *Dz1BMPDIB_gen(Dz1Error *err) { return Dz1BMPDIB_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1BMPDIB_copy(Dz1BMPDIB *dst, Dz1BMPDIB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1BMPDIB *Dz1BMPDIB_clone(Dz1BMPDIB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMPDIB_purge(Dz1BMPDIB *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMPDIB_del(Dz1BMPDIB *p);
static __inline__ void Dz1BMPDIB_delAndSetNull(void *ptr)
{
	Dz1BMPDIB **p = (Dz1BMPDIB **)ptr;
	if (p) { Dz1BMPDIB_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMPDIB_dump(Dz1BMPDIB *p, int tab);
// Dz1BMPDIB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMP
typedef struct Dz1BMP
{
	Dz1BMPDIB		*hdr;
	u8_t			*image;
	Dz1Binary		*chunk;
} Dz1BMP;

DZ1_CPPLINK DZ1_DLLPORT Dz1BMP *Dz1BMP_new(Dz1BMPDIB *hdr, 
										   u8_t *image, 
										   Dz1Binary *chunk, Dz1Error *err);
static __inline__ Dz1BMP *Dz1BMP_gen(Dz1Error *err) { return Dz1BMP_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1BMP_copy(Dz1BMP *dst, Dz1BMP *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT Dz1BMP *Dz1BMP_clone(Dz1BMP *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMP_purge(Dz1BMP *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMP_del(Dz1BMP *p);	// User Customized
static __inline__ void Dz1BMP_delAndSetNull(void *ptr)
{
	Dz1BMP **p = (Dz1BMP **)ptr;
	if (p) { Dz1BMP_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1BMP_dump(Dz1BMP *p, int tab);
// Dz1BMP
////////////////////////////////////////////////////////////////////////////////

#endif
