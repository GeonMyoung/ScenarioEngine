#ifndef DZ1_BITS_H
#define DZ1_BITS_H

#include <dz1_error.h>

#define DZ1_BITS_UNIT							unsigned int
#define DZ1_BITS_UNIT_SIZE_BYTE					(sizeof(DZ1_BITS_UNIT))
#define DZ1_BITS_UNIT_SIZE_BIT					(DZ1_BITS_UNIT_SIZE_BYTE << 3)
#define DZ1_BITS_UNIT_SIZE_ARRAY(bitsSize)		((bitsSize / DZ1_BITS_UNIT_SIZE_BIT) + (bitsSize % DZ1_BITS_UNIT_SIZE_BIT ? 1 : 0))

///////////////////////////////////////////////////////////////////////////////
// Bits Unit API
///////////////////////////////////////////////////////////////////////////////
static __inline__ bool_t Dz1BitsUnit_isAllClr(DZ1_BITS_UNIT unit)
{
	DZ1_BITS_UNIT mask = ~0;
	return (unit & mask) == 0 ? TRUE : FALSE;
}

static __inline__ bool_t Dz1BitsUnit_isAllSet(DZ1_BITS_UNIT unit)
{
	DZ1_BITS_UNIT mask = ~0;
	return (unit & mask) == mask ? TRUE : FALSE;
}

static __inline__ bool_t Dz1BitsUnit_isSet(DZ1_BITS_UNIT unit, u32_t unitBitIdx)
{
	DZ1_BITS_UNIT mask = 1 << ((DZ1_BITS_UNIT_SIZE_BIT - 1) - (unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT));
	if (unit & mask) return TRUE;
	return FALSE;
}

static __inline__ DZ1_BITS_UNIT Dz1BitsUnit_set(DZ1_BITS_UNIT unit, u32_t unitBitIdx)
{
	DZ1_BITS_UNIT mask = 1 << ((DZ1_BITS_UNIT_SIZE_BIT - 1) - (unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT));
	unit |= mask;
	return unit;
}

static __inline__ DZ1_BITS_UNIT Dz1BitsUnit_clr(DZ1_BITS_UNIT unit, u32_t unitBitIdx)
{
	DZ1_BITS_UNIT mask = 1 << ((DZ1_BITS_UNIT_SIZE_BIT - 1) - (unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT));
	unit &=( ~mask);
	return unit;
}

///////////////////////////////////////////////////////////////////////////////
// Bits Array API
///////////////////////////////////////////////////////////////////////////////
static __inline__ bool_t Dz1Bits_isSet(DZ1_BITS_UNIT *arr, u32_t unitBitIdx)
{
	int idx = unitBitIdx / DZ1_BITS_UNIT_SIZE_BIT;
	int shi = unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT;
	return Dz1BitsUnit_isSet(arr[idx], shi);
}

static __inline__ DZ1_BITS_UNIT Dz1Bits_set(DZ1_BITS_UNIT *arr, u32_t unitBitIdx)
{
	int idx = unitBitIdx / DZ1_BITS_UNIT_SIZE_BIT;
	int shi = unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT;
	return Dz1BitsUnit_set(arr[idx], shi);
}

static __inline__ DZ1_BITS_UNIT Dz1Bits_clr(DZ1_BITS_UNIT *arr, u32_t unitBitIdx)
{
	int idx = unitBitIdx / DZ1_BITS_UNIT_SIZE_BIT;
	int shi = unitBitIdx % DZ1_BITS_UNIT_SIZE_BIT;
	return Dz1BitsUnit_clr(arr[idx], shi);
}

typedef struct Dz1Bits
{
	DZ1_BITS_UNIT	*data;
	__DZ1ALIGN(u32_t, size_bits);
	Dz1Error (*set)(struct Dz1Bits *p, u32_t idx);
	Dz1Error (*clr)(struct Dz1Bits *p, u32_t idx);
	bool_t (*isSet)(struct Dz1Bits *p, u32_t idx);
} Dz1Bits;

DZ1_CPPLINK DZ1_DLLPORT Dz1Bits *Dz1Bits_new(DZ1_BITS_UNIT *data, u32_t size_bits, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Bits_del(Dz1Bits *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Bits_dump(Dz1Bits *p, int tab);
static __inline__ void Dz1Bits_delAndSetNull(void *ptr)
{
	Dz1Bits **p = (Dz1Bits **)ptr;
	Dz1Bits_del(*p); *p = NULL;
}

#endif
