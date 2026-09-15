#include "Dz1GifDef.h"

void Dz1GifDataSubBlock_del(Dz1GifDataSubBlock *p)
{
	Dz1GifDataSubBlock *i = p, *next;
	if (p == NULL) return;

	while(i)
	{
		next = i->next;
		if (i->bin) Dz1Binary_del(i->bin);
		Dz1Free(i);
		i = next;
	}
}

void Dz1GifColor_dump(Dz1GifColor *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%03u (%02X, %02X, %02X)\n", p->idx, p->red, p->green, p->blue);
}

void Dz1GifTableBasedImgData_dump(Dz1GifTableBasedImgData *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		Dz1Binary *lzw = p->lzw;
		if (lzw == NULL)
			Dz1Thread_printf("Code Size(%02x) RAW = NULL\n", p->lzwMinimumCodeSize);
		else
		{
			size_t dump_size = lzw->size > 256 ? 256 : lzw->size;
			Dz1Thread_printf("Code Size(%02x) %u Bytes = {\n", p->lzwMinimumCodeSize, lzw->size); tab++;
			Dz1Thread_tprintb(tab, lzw->data, dump_size, 16, TRUE);
			Dz1Thread_tprintf(--tab, "}\n");
		}
	}
}

void Dz1GifImgDescr_dump(Dz1GifImgDescr *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		Dz1Thread_printf("(%u, %u)~(%u, %u), %s ",
			p->x, p->y, p->width, p->height,
			p->isInterlaced ? "Interlaced" : "Progressive");
		if (p->lctPresent)
		{
			Dz1Thread_printf(", Color Table(%s) = ", p->lctIsSorted ? "Sorted" : "Ruff");
			Dz1GifColorArray_dump(p->palette, tab);
		}
		else Dz1Thread_printf("\n");

	}
}

void Dz1GifRenderTableBasedImg_dump(Dz1GifRenderTableBasedImg *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->descr == NULL) Dz1Thread_tprintf(tab, "descr = NULL\n");
	else { Dz1Thread_tprintf(tab, "descr = "); Dz1GifImgDescr_dump(p->descr, tab); }

	if (p->pixels == NULL) Dz1Thread_tprintf(tab, "pixels = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "pixels = ");
		Dz1Binary_dumpPartial(p->pixels, tab, 256);
	}

	Dz1Thread_tprintf(--tab, "}\n");
}

