#include <dz1_thread_stdio.h>
#include "dz1_asn1.h"

static void _setMaxBit(Dz1Asn1BitStr *p)
{
	size_t i, idx = 0, shf = 0;
	u8_t b = 0;
	for (i = 0; i < p->allocByte; i++)
	{
		if (p->bits[i] != 0)
		{
			b = p->bits[i];
			idx = i;
		}
	}

	if (b != 0)
	{
		u8_t mask = 0x80;
		for (i = 0, mask = 0x80; i < 8; i++, mask >>= 1)
			if (b & mask) shf = i;
	}

	p->maxBit = (idx * 8) + shf;

// 	size_t max_bit = 0;
// 	int i, bitNum = (int)p->allocByte << 3;
// 	for (i = (int)p->allocByte - 1; max_bit == 0 && i >= 0; i--, bitNum -= 8)
// 	{
// 		if (p->bits[i] != 0x00)
// 		{
// 			u8_t mask = 0x01;
// 			u8_t v = p->bits[i], j;
// 			for (j = 0; j < 8; j++)
// 			{
// 				if (v & (mask << j))
// 				{
// 					max_bit = bitNum - j;
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	p->maxBit = max_bit;
}

Dz1Asn1BitStr *_Dz1Asn1BitStr_new(u8_t *bits, size_t allocByte, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1BitStr *ret = (Dz1Asn1BitStr *)_Dz1Calloc(sizeof(Dz1Asn1BitStr), 1, errp, __file, __line);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		if (allocByte && (ret->bits = (u8_t *)Dz1Calloc(sizeof(u8_t), (ret->allocByte = allocByte), errp)) == NULL) ERR_OUT(errp);
		else if (bits != NULL)
		{
			memcpy(ret->bits, bits, ret->allocByte);
			_setMaxBit(ret);
		}
		else ret->maxBit = 0;
	}
	return ret;
}

Dz1Asn1BitStr *_Dz1Asn1BitStr_clone(Dz1Asn1BitStr *src, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1BitStr *ret = _Dz1Asn1BitStr_new(src->bits, src->allocByte, errp, __file, __line);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

void Dz1Asn1BitStr_del(Dz1Asn1BitStr *p)
{
	if (p == NULL) return;
	if (p->bits) Dz1Free(p->bits);
	Dz1Free(p);
}

int Dz1Asn1BitStr_cmp(Dz1Asn1BitStr *a, Dz1Asn1BitStr *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else if (a->allocByte < b->allocByte) return -1;
	else if (a->allocByte > b->allocByte) return -1;
	else if (a->maxBit < b->maxBit) return -1;
	else if (a->maxBit > b->maxBit) return 1;
	else
	{
		int ret = 0;
		u32_t cmp_byte = (u32_t)(a->maxBit >> 3), frag = a->maxBit & 0x7;
		if ((ret = memcmp(a->bits, b->bits, cmp_byte)) != 0) { }
		else if (frag)
		{
			u32_t idx = cmp_byte + 1;
			u8_t mask = ~((0x01 << (8 - frag)) - 1);
			if ((a->bits[idx] & mask) < (b->bits[idx] & mask)) ret = -1;
			else if ((a->bits[idx] & mask) < (b->bits[idx] & mask)) ret = 1;
			else ret = 0;
		}
		return ret;
	}
}

bool_t Dz1Asn1BitStr_setMaxBit(Dz1Asn1BitStr *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || p->bits == NULL)
		ERR_SET_OUT(errp, EINVAL);
	else
	{
		_setMaxBit(p);
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void _printBinaryA(u8_t *cp, size_t size)
{
	size_t printed = 0;
	while(size)
	{
		Dz1ThreadA_printf("%02X", *cp);
		size--; cp++; printed++;

		if (size)
		{
			if ((printed % 2) == 0) Dz1ThreadA_putc(' ', NULL);
			if ((printed % 4) == 0) Dz1ThreadA_putc(' ', NULL);
		}
	}
	Dz1ThreadA_printf("\n");
}

void Dz1Asn1BitStrA_dump(Dz1Asn1BitStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		size_t _lenbyte = 0, lenByte = 0;
		if (p->maxBit == 0) _setMaxBit(p);

		_lenbyte = (p->maxBit >> 3) + (p->maxBit & 0x7 ? 1 : 0);
		lenByte = p->allocByte < _lenbyte ? p->allocByte : _lenbyte;
		if (lenByte == 0) Dz1ThreadA_printf("No Positive Bits\n");
		else if (lenByte > 16)
		{
			ssize_t dumpLen;
			u8_t *cp = p->bits;
			Dz1ThreadA_printf("{ %u %u/%u\n", p->maxBit, (p->maxBit + 7) >> 3, p->allocByte); tab++;
			while(lenByte)
			{
				Dz1ThreadA_tprintf(tab, "%08X : ", (u32_t)(cp - p->bits));
				dumpLen = (ssize_t)(lenByte >= 16 ? 16 : lenByte);
				_printBinaryA(cp, dumpLen);
				cp += dumpLen;
				lenByte -= dumpLen;
			}
			Dz1ThreadA_tprintf(--tab, "}\n");
		}
		else
		{
			Dz1ThreadA_printf("%u %u/%u = ", p->maxBit, ((p->maxBit + 7) >> 3), p->allocByte);
			_printBinaryA(p->bits, lenByte);
		}
	}
}
#ifndef UNIX_SYSTEM
static void _printBinaryW(u8_t *cp, size_t size)
{
	size_t printed = 0;
	while(size)
	{
		Dz1ThreadW_printf(L"%02X", *cp);
		size--; cp++; printed++;

		if (size)
		{
			if ((printed % 2) == 0) Dz1ThreadW_putc(L' ', NULL);
			if ((printed % 4) == 0) Dz1ThreadW_putc(L' ', NULL);
		}
	}
	Dz1ThreadW_printf(L"\n");
}

void Dz1Asn1BitStrW_dump(Dz1Asn1BitStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		size_t _lenbyte = 0, lenByte = 0;
		if (p->maxBit == 0) _setMaxBit(p);

		_lenbyte = (p->maxBit >> 3) + (p->maxBit & 0x7 ? 1 : 0);
		lenByte = p->allocByte < _lenbyte ? p->allocByte : _lenbyte;
		if (lenByte == 0) Dz1ThreadW_printf(L"No Positive Bits\n");
		else if (lenByte > 16)
		{
			ssize_t dumpLen;
			u8_t *cp = p->bits;
			Dz1ThreadW_printf(L"{ %u %u/%u\n", p->maxBit, (p->maxBit + 7) >> 3, p->allocByte); tab++;
			while(lenByte)
			{
				Dz1ThreadW_tprintf(tab, L"%08X : ", (u32_t)(cp - p->bits));
				dumpLen = (ssize_t)(lenByte >= 16 ? 16 : lenByte);
				_printBinaryW(cp, dumpLen);
				cp += dumpLen;
				lenByte -= dumpLen;
			}
			Dz1ThreadW_tprintf(--tab, L"}\n");
		}
		else
		{
			Dz1ThreadW_printf(L"%u %u/%u = ", p->maxBit, ((p->maxBit + 7) >> 3), p->allocByte);
			_printBinaryW(p->bits, lenByte);
		}
	}
}
#endif

static void _fprintBinaryA(FILE *fp, u8_t *cp, size_t size)
{
	size_t printed = 0;
	while(size)
	{
		Dz1ThreadA_fprintf(fp, "%02X", *cp);
		size--; cp++; printed++;

		if (size)
		{
			if ((printed % 2) == 0) Dz1ThreadA_fputc(fp, ' ', NULL);
			if ((printed % 4) == 0) Dz1ThreadA_fputc(fp, ' ', NULL);
		}
	}
	Dz1ThreadA_fprintf(fp, "\n");
}

void Dz1Asn1BitStrA_fdump(FILE *fp, Dz1Asn1BitStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		size_t _lenbyte = 0, lenByte = 0;
		if (p->maxBit == 0) _setMaxBit(p);
		_lenbyte = (p->maxBit >> 3) + (p->maxBit & 0x7 ? 1 : 0);
		lenByte = p->allocByte < _lenbyte ? p->allocByte : _lenbyte;
		if (lenByte == 0) Dz1ThreadA_fprintf(fp, "No Positive Bits\n");
		else if (lenByte > 16)
		{
			ssize_t dumpLen;
			u8_t *cp = p->bits;
			Dz1ThreadA_fprintf(fp, "{ %u %u/%u\n", p->maxBit, (p->maxBit + 7) >> 3, p->allocByte); tab++;
			while(lenByte)
			{
				Dz1ThreadA_ftprintf(fp, tab, "%08X : ", (u32_t)(cp - p->bits));
				dumpLen = (ssize_t)(lenByte >= 16 ? 16 : lenByte);
				_fprintBinaryA(fp, cp, dumpLen);
				cp += dumpLen;
				lenByte -= dumpLen;
			}
			Dz1ThreadA_ftprintf(fp, --tab, "}\n");
		}
		else
		{
			Dz1ThreadA_fprintf(fp, "%u %u/%u = ", p->maxBit, ((p->maxBit + 7) >> 3), p->allocByte);
			_fprintBinaryA(fp, p->bits, lenByte);
		}
	}
}
#ifndef UNIX_SYSTEM
static void _fprintBinaryW(FILE *fp, u8_t *cp, size_t size)
{
	size_t printed = 0;
	while(size)
	{
		Dz1ThreadW_fprintf(fp, L"%02X", *cp);
		size--; cp++; printed++;

		if (size)
		{
			if ((printed % 2) == 0) Dz1ThreadW_fputc(fp, L' ', NULL);
			if ((printed % 4) == 0) Dz1ThreadW_fputc(fp, L' ', NULL);
		}
	}
	Dz1ThreadW_fprintf(fp, L"\n");
}

void Dz1Asn1BitStrW_fdump(FILE *fp, Dz1Asn1BitStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		size_t _lenbyte = 0, lenByte = 0;
		if (p->maxBit == 0) _setMaxBit(p);
		_lenbyte = (p->maxBit >> 3) + (p->maxBit & 0x7 ? 1 : 0);
		lenByte = p->allocByte < _lenbyte ? p->allocByte : _lenbyte;
		if (lenByte == 0) Dz1ThreadW_fprintf(fp, L"No Positive Bits\n");
		else if (lenByte > 16)
		{
			ssize_t dumpLen;
			u8_t *cp = p->bits;
			Dz1ThreadW_fprintf(fp, L"{ %u %u/%u\n", p->maxBit, (p->maxBit + 7) >> 3, p->allocByte); tab++;
			while(lenByte)
			{
				Dz1ThreadW_ftprintf(fp, tab, L"%08X : ", (u32_t)(cp - p->bits));
				dumpLen = (ssize_t)(lenByte >= 16 ? 16 : lenByte);
				_fprintBinaryW(fp, cp, dumpLen);
				cp += dumpLen;
				lenByte -= dumpLen;
			}
			Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
		}
		else
		{
			Dz1ThreadW_fprintf(fp, L"%u %u/%u = ", p->maxBit, ((p->maxBit + 7) >> 3), p->allocByte);
			_fprintBinaryW(fp, p->bits, lenByte);
		}
	}
}
#endif

static bool_t _Dz1Asn1BitStr_reallocate(Dz1Asn1BitStr *dst, size_t tgt_bit, Dz1Error *errp)
{
	if (dst == NULL || tgt_bit >= 0x800000) ERR_SET_OUT(errp, EINVAL);					// 8MB maximum
	else
	{
		size_t toAllocByte = (tgt_bit >> 3) + (tgt_bit & 0x7 ? 1 : 0);					// new alloc byte
		u8_t *backup = dst->bits;
		size_t backup_sz = dst->allocByte;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&backup);

		if ((dst->bits = (u8_t *)Dz1Calloc(sizeof(u8_t), toAllocByte, errp)) == NULL)	// re-allocate with new size
		{
			ERR_OUT(errp);
			dst->bits = backup;
			backup = NULL;
		}
		else
		{
			Dz1Error_set(errp, 0);
			if (backup != NULL && backup_sz > 0) memcpy(dst->bits, backup, backup_sz);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&backup);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Bit Set
static void _bits_set(u8_t *bits, size_t bitNum)
{
	size_t idx = bitNum >> 3;
	size_t shift_cnt = bitNum & 0x7;
	u8_t msb = 0x80, mask = msb >> shift_cnt;
	bits[idx] = bits[idx] | mask;
}

bool_t _Dz1Asn1BitStr_set(Dz1Asn1BitStr *dst, size_t bitNum, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bitNum >= 0x800000) ERR_SET_OUT(errp, EINVAL);									// 8MB maximum
	else
	{
		u32_t curAllocBits = (u32_t)(dst->allocByte << 3);
		if (bitNum > curAllocBits)
		{
			if (_Dz1Asn1BitStr_reallocate(dst, bitNum, errp) == FALSE) ERR_OUT(errp);
			else
			{
				_bits_set(dst->bits, bitNum);
				if (bitNum > dst->maxBit) dst->maxBit = bitNum;

				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			_bits_set(dst->bits, bitNum);
			if (bitNum > dst->maxBit) dst->maxBit = bitNum;

			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1Asn1BitStr_set(Dz1Asn1BitStr *dst, size_t bitNum)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1Asn1BitStr_set(dst, bitNum, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Bit Set
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Bit Clear
static void _bits_clr(u8_t *bits, size_t bitNum)
{
	size_t idx = bitNum >> 3;
	size_t shift_cnt = bitNum & 0x7;
	u8_t msb = 0x80, mask = ~(msb >> shift_cnt);
	bits[idx] = bits[idx] & mask;
}

bool_t _Dz1Asn1BitStr_clr(Dz1Asn1BitStr *dst, size_t bitNum, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bitNum >= 0x800000) ERR_SET_OUT(errp, EINVAL);									// 8MB maximum
	else
	{
		u32_t curAllocBits = (u32_t)(dst->allocByte << 3);
		if (bitNum > curAllocBits)
		{
			if (_Dz1Asn1BitStr_reallocate(dst, bitNum, errp) == FALSE) ERR_OUT(errp);
			else
			{
				_bits_clr(dst->bits, bitNum);
				if (bitNum == dst->maxBit) _setMaxBit(dst);

				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			_bits_clr(dst->bits, bitNum);
			if (bitNum == dst->maxBit) _setMaxBit(dst);

			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1Asn1BitStr_clr(Dz1Asn1BitStr *dst, size_t bitNum)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1Asn1BitStr_clr(dst, bitNum, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Bit Clear
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Bit Get
static bool_t _bits_get(u8_t *bits, size_t bitNum)
{
	bool_t ret = FALSE;

	size_t idx = bitNum >> 3;
	size_t shift_cnt = bitNum & 0x7;
	u8_t msb = 0x80, mask = (msb >> shift_cnt);
	ret = (bits[idx] & mask) ? TRUE : FALSE;

	return ret;
}

bool_t Dz1Asn1BitStr_get(Dz1Asn1BitStr *src, size_t bitNum, Dz1Error *err)
{
	bool_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bitNum >= (src->allocByte << 3)) Dz1Error_set(errp, EINVAL);
	else
	{
		ret = _bits_get(src->bits, bitNum);
	}
	return ret;
}
// Bit Get
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1Asn1BitStr_assign(Dz1Asn1BitStr *dst, u8_t *src, size_t bitSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->bits != NULL)
		{
			Dz1Free(dst->bits);
			dst->bits = NULL;
			dst->maxBit = 0;
			dst->allocByte = 0;
		}

		if (src == NULL || bitSize == 0) { }
		else
		{
			dst->allocByte = (bitSize >> 3) + ((bitSize & 0x7) ? 1 : 0);
			if ((dst->bits = (u8_t *)Dz1Calloc(sizeof(u8_t), dst->allocByte, errp)) == NULL)
			{
				ERR_OUT(errp);
				dst->allocByte = 0;
			}
			else
			{
				dst->maxBit = bitSize;
				memcpy(dst->bits, src, dst->allocByte);
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}
