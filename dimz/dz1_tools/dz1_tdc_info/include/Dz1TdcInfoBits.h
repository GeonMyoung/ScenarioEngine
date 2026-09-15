#ifndef BITS_INFO_H
#define BITS_INFO_H

#include "dz1_error.h"

typedef struct BitsEntry
{
	str_t name;
	u32_t bit;
} BitsEntry;

DZ1_CPPLINK BitsEntry *BitsEntry_new(str_t name, u32_t bit, Dz1Error *err);
DZ1_CPPLINK void BitsEntry_del(BitsEntry *p);
DZ1_CPPLINK void BitsEntry_dump(BitsEntry *p, int tab);
static __inline__ void BitsEntry_delAndSetNull(void *ptr)
{
	BitsEntry **p = (BitsEntry **)ptr;
	BitsEntry_del(*p); *p = NULL;
}

typedef struct BitsList
{
	void *fifo;
	Dz1Error (*add)(struct BitsList *p, str_t name, u32_t bit);
	Dz1Error (*append)(struct BitsList *p, BitsEntry *node);
	u32_t (*count)(struct BitsList *p);
	Dz1Error (*travel)(struct BitsList *p, Dz1Error (*func)(void *ptr, BitsEntry *p), void *ptr);
} BitsList;

DZ1_CPPLINK BitsList *BitsList_new(Dz1Error *err);
DZ1_CPPLINK void BitsList_del(BitsList *p);
DZ1_CPPLINK void BitsList_dump(BitsList *p, int tab);
static __inline__ void BitsList_delAndSetNull(void *ptr)
{
	BitsList **p = (BitsList **)ptr;
	BitsList_del(*p); *p = NULL;
}


typedef struct BitsInfo
{
	BitsList *bits;
} BitsInfo;

DZ1_CPPLINK BitsInfo *BitsInfo_new(Dz1Error *err);
DZ1_CPPLINK void BitsInfo_del(BitsInfo *p);
DZ1_CPPLINK void BitsInfo_dump(BitsInfo *p, int tab);
static __inline__ void BitsInfo_delAndSetNull(void *ptr)
{
	BitsInfo **p = (BitsInfo **)ptr;
	BitsInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK void *BitsInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t BitsInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t BitsInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
