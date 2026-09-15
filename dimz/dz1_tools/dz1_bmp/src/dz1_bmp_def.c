////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_bmp_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPBPP
static struct Dz1BMPBPPMapA
{
	str_t str;
	Dz1BMPBPP v;
} Dz1BMPBPPMapA[] =
{
	{ (char *)"bw", Dz1BMPBPP_bw },
	{ (char *)"color16", Dz1BMPBPP_color16 },
	{ (char *)"color256", Dz1BMPBPP_color256 },
	{ (char *)"color64K", Dz1BMPBPP_color64K },
	{ (char *)"colorTrue", Dz1BMPBPP_colorTrue },
	{ (char *)"colorTrue32", Dz1BMPBPP_colorTrue32 },
	{ NULL, Dz1BMPBPP_max }
};

str_t Dz1BMPBPPStrA(Dz1BMPBPP v)
{
	struct Dz1BMPBPPMapA *i = NULL;
	for (i = Dz1BMPBPPMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1BMPBPP Dz1BMPBPPFromStrA(str_t str)
{
	struct Dz1BMPBPPMapA *i = NULL;
	for (i = Dz1BMPBPPMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1BMPBPP_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1BMPBPPMapW
{
	wstr_t str;
	Dz1BMPBPP v;
} Dz1BMPBPPMapW[] =
{
	{ (wchar_t *)L"bw", Dz1BMPBPP_bw },
	{ (wchar_t *)L"color16", Dz1BMPBPP_color16 },
	{ (wchar_t *)L"color256", Dz1BMPBPP_color256 },
	{ (wchar_t *)L"color64K", Dz1BMPBPP_color64K },
	{ (wchar_t *)L"colorTrue", Dz1BMPBPP_colorTrue },
	{ (wchar_t *)L"colorTrue32", Dz1BMPBPP_colorTrue32 },
	{ NULL, Dz1BMPBPP_max }
};

wstr_t Dz1BMPBPPStrW(Dz1BMPBPP v)
{
	struct Dz1BMPBPPMapW *i = NULL;
	for (i = Dz1BMPBPPMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1BMPBPP Dz1BMPBPPFromStrW(wstr_t str)
{
	struct Dz1BMPBPPMapW *i = NULL;
	for (i = Dz1BMPBPPMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1BMPBPP_max;
}
#endif // UNIX_SYSTEM

Dz1BMPBPP *Dz1BMPBPP_new(Dz1BMPBPP *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1BMPBPP *__internal_ret = (Dz1BMPBPP *)Dz1Calloc(sizeof(Dz1BMPBPP), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1BMPBPP
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPComp
static struct Dz1BMPCompMapA
{
	str_t str;
	Dz1BMPComp v;
} Dz1BMPCompMapA[] =
{
	{ (char *)"RGB", Dz1BMPComp_RGB },
	{ (char *)"RLE8", Dz1BMPComp_RLE8 },
	{ (char *)"RLE4", Dz1BMPComp_RLE4 },
	{ (char *)"BITFIELDS", Dz1BMPComp_BITFIELDS },
	{ (char *)"JPEG", Dz1BMPComp_JPEG },
	{ (char *)"PNG", Dz1BMPComp_PNG },
	{ NULL, Dz1BMPComp_max }
};

str_t Dz1BMPCompStrA(Dz1BMPComp v)
{
	struct Dz1BMPCompMapA *i = NULL;
	for (i = Dz1BMPCompMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1BMPComp Dz1BMPCompFromStrA(str_t str)
{
	struct Dz1BMPCompMapA *i = NULL;
	for (i = Dz1BMPCompMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1BMPComp_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1BMPCompMapW
{
	wstr_t str;
	Dz1BMPComp v;
} Dz1BMPCompMapW[] =
{
	{ (wchar_t *)L"RGB", Dz1BMPComp_RGB },
	{ (wchar_t *)L"RLE8", Dz1BMPComp_RLE8 },
	{ (wchar_t *)L"RLE4", Dz1BMPComp_RLE4 },
	{ (wchar_t *)L"BITFIELDS", Dz1BMPComp_BITFIELDS },
	{ (wchar_t *)L"JPEG", Dz1BMPComp_JPEG },
	{ (wchar_t *)L"PNG", Dz1BMPComp_PNG },
	{ NULL, Dz1BMPComp_max }
};

wstr_t Dz1BMPCompStrW(Dz1BMPComp v)
{
	struct Dz1BMPCompMapW *i = NULL;
	for (i = Dz1BMPCompMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1BMPComp Dz1BMPCompFromStrW(wstr_t str)
{
	struct Dz1BMPCompMapW *i = NULL;
	for (i = Dz1BMPCompMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1BMPComp_max;
}
#endif // UNIX_SYSTEM

Dz1BMPComp *Dz1BMPComp_new(Dz1BMPComp *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1BMPComp *__internal_ret = (Dz1BMPComp *)Dz1Calloc(sizeof(Dz1BMPComp), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1BMPComp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMPDIB
Dz1BMPDIB *Dz1BMPDIB_new(u32_t hdr_size, 
						 s32_t width, 
						 s32_t height, 
						 u16_t planes, 
						 u16_t bpp, 
						 u32_t comp, 
						 u32_t decompress_size, 
						 s32_t horizontal_ppm, 
						 s32_t vertical_ppm, 
						 u32_t palette_color, 
						 u32_t important_color, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1BMPDIB *__internal_ret = (Dz1BMPDIB *)Dz1Calloc(sizeof(Dz1BMPDIB), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1BMPDIB_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->hdr_size = hdr_size;
		__internal_ret->width = width;
		__internal_ret->height = height;
		__internal_ret->planes = planes;
		__internal_ret->bpp = bpp;
		__internal_ret->comp = comp;
		__internal_ret->decompress_size = decompress_size;
		__internal_ret->horizontal_ppm = horizontal_ppm;
		__internal_ret->vertical_ppm = vertical_ppm;
		__internal_ret->palette_color = palette_color;
		__internal_ret->important_color = important_color;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1BMPDIB_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1BMPDIB_copy(Dz1BMPDIB *dst, Dz1BMPDIB *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->hdr_size = src->hdr_size;
		dst->width = src->width;
		dst->height = src->height;
		dst->planes = src->planes;
		dst->bpp = src->bpp;
		dst->comp = src->comp;
		dst->decompress_size = src->decompress_size;
		dst->horizontal_ppm = src->horizontal_ppm;
		dst->vertical_ppm = src->vertical_ppm;
		dst->palette_color = src->palette_color;
		dst->important_color = src->important_color;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1BMPDIB *Dz1BMPDIB_clone(Dz1BMPDIB *src, Dz1Error *err)
{
	Dz1BMPDIB *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1BMPDIB *)Dz1Calloc(sizeof(Dz1BMPDIB), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1BMPDIB_delAndSetNull, (void *)&dst);
		if (Dz1BMPDIB_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1BMPDIB_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1BMPDIB_purge(Dz1BMPDIB *p)
{
	if (p == NULL) return;
}

void Dz1BMPDIB_del(Dz1BMPDIB *p)
{
	if (p == NULL) return;
	Dz1BMPDIB_purge(p);
	Dz1Free(p);
}

void Dz1BMPDIB_dump(Dz1BMPDIB *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("hdr_size = ")); Dz1u32_dump(&p->hdr_size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("width = ")); Dz1s32_dump(&p->width, tab); 
		Dz1Thread_tprintf(tab, Dz1T("height = ")); Dz1s32_dump(&p->height, tab); 
		Dz1Thread_tprintf(tab, Dz1T("planes = ")); Dz1u16_dump(&p->planes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bpp = ")); Dz1u16_dump(&p->bpp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("comp = ")); Dz1u32_dump(&p->comp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("decompress_size = ")); Dz1u32_dump(&p->decompress_size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("horizontal_ppm = ")); Dz1s32_dump(&p->horizontal_ppm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("vertical_ppm = ")); Dz1s32_dump(&p->vertical_ppm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("palette_color = ")); Dz1u32_dump(&p->palette_color, tab); 
		Dz1Thread_tprintf(tab, Dz1T("important_color = ")); Dz1u32_dump(&p->important_color, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1BMPDIB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1BMP
Dz1BMP *Dz1BMP_new(Dz1BMPDIB *hdr, u8_t *image, Dz1Binary *chunk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1BMP *__internal_ret = (Dz1BMP *)Dz1Calloc(sizeof(Dz1BMP), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->hdr = hdr;
		__internal_ret->image = image;
		__internal_ret->chunk = chunk;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1BMP_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1BMP_dump(Dz1BMP *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("hdr = ")); Dz1BMPDIB_dump(p->hdr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("image = ")); Dz1u8_dump(p->image, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("chunk = ")); Dz1Binary_dump(p->chunk, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1BMP
////////////////////////////////////////////////////////////////////////////////

