#include <dz1_thread_stdio.h>
#include <dz1_codec.h>
#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_bcd_str.h>
#include <pthread.h>

static ssize_t u8ToBCD_A(str_t dst, u8_t bcd)
{
	u8_t h = (bcd >> 4) & 0xF, l = bcd & 0xF;
	*dst++ = '0' + h;
	*dst++ = '0' + l;
	return 2;
}

static void _mkBCDStrA(str_t dst, u8_t *bcdData, size_t size)
{
	char *cp = dst;
	u8_t *src = bcdData;
	ssize_t status;
	while(size)
	{
		status = u8ToBCD_A(cp, *src++);
		size--;
		cp += status;
	}
}

static Dz1Error _allocAndMakeBCDStrA(Dz1BCDStr *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (dst->size > 0)
	{
		if (dst->str_buf == NULL)
		{
			if ((dst->str_buf = (str_t)Dz1Calloc(sizeof(char), (dst->size << 1) + 1, &err)) == NULL) ERR_OUT(&err);
			else _mkBCDStrA((str_t)dst->str_buf, dst->bcdData, dst->size);
		}
	}
	return err;
}
#ifndef UNIX_SYSTEM
static ssize_t u8ToBCD_W(wstr_t dst, u8_t bcd)
{
	u8_t h = (bcd >> 4) & 0xF, l = bcd & 0xF;
	*dst++ = L'0' + h;
	*dst++ = L'0' + l;
	return 2;
}

static void _mkBCDStrW(wstr_t dst, u8_t *bcdData, size_t size)
{
	wchar_t *cp = dst;
	u8_t *src = bcdData;
	ssize_t status;
	while(size)
	{
		status = u8ToBCD_W(cp, *src++);
		size--;
		cp += status;
	}
}

static Dz1Error _allocAndMakeBCDStrW(Dz1BCDStr *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (dst->size > 0)
	{
		if (dst->str_buf == NULL)
		{
			if ((dst->str_buf = (str_t)Dz1Calloc(sizeof(char), (dst->size << 1) + 1, &err)) == NULL) ERR_OUT(&err);
			else _mkBCDStrW((wstr_t)dst->str_buf, dst->bcdData, dst->size);
		}
	}
	return err;
}
#endif

static bool_t _isBCD(u8_t bcd)
{
	u8_t h = (bcd >> 4) & 0xF, l = bcd & 0xF;
	if (h > 9) return FALSE;
	else if (l > 9) return FALSE;
	else return TRUE;
}

static bool_t _chkAndCopyBCDData(Dz1BCDStr *dst, u8_t *bcdData, size_t size)
{
	u8_t *src = bcdData, *cp = dst->bcdData;
	dst->size = 0;
	while(size)
	{
		if (_isBCD(*src) == FALSE) return FALSE;
		else
		{
			*cp++ = *src++;
			size--;
			dst->size++;
		}
	}
	return TRUE;
}

static Dz1Error _setNibbleSpreadedData(Dz1BCDStr *dst, u8_t *src, size_t len)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u8_t v, *cp = dst->bcdData;
	dst->size = 0;
	while(len && err.code == 0)
	{
		if (_isBCD(*src) == FALSE) Dz1Error_set(&err, EINVAL);
		else
		{
			v = ((*src) & 0xF) << 4; src++; len--;
			v |= (*src) & 0xF; src++; len--;
			*cp++ = v; dst->size++;
		}
	}
	return err;
}

static bool_t _chkBCDData(u8_t *bcdData, size_t size)
{
	u8_t *src = bcdData;
	while(size)
	{
		if (_isBCD(*src) == FALSE) return FALSE;
		else
		{
			src++;
			size--;
		}
	}
	return TRUE;
}

Dz1BCDStr *Dz1BCDStrA_new(u8_t *bcdData, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1BCDStr *ret = (Dz1BCDStr *)Dz1Calloc(sizeof(Dz1BCDStr), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);
		if (size > 0)
		{	// 사이즈가 있으면 Data 할당, AllocSize 설정, Size 설정
			if ((ret->bcdData = (u8_t *)Dz1Calloc(sizeof(u8_t), (ret->allocSize = size), errp)) == NULL) ERR_OUT(errp);
			// Data가 있으면 BCD인지 확인하면서 복사
			else if (bcdData != NULL && _chkAndCopyBCDData(ret, bcdData, size) == FALSE) ERR_SET_OUT(errp, EINVAL);
			// 출력 문자열 할당
			else if ((*errp = _allocAndMakeBCDStrA(ret)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{	// 사이즈가 없으면 Data = NULL, AllocSize = 0, Size = 0, str = NULL
		}
		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _setStringDataA(Dz1BCDStr *dst, str_t src, size_t len)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u8_t *dp = dst->bcdData, *cp = (u8_t *)src, h, l;
	dst->size = 0;
	while(err.code == 0 && len)
	{
		if (*cp < '0' || *cp > '9') ERR_SET_OUT(&err, EINVAL);
		else
		{
			h = *cp++ - '0'; len--;
			if (*cp < '0' || *cp > '9') ERR_SET_OUT(&err, EINVAL);
			else
			{
				l = *cp++ - '0'; len--;
				*dp++ = (h << 4) | l; dst->size++;
			}
		}
	}
	return err;
}

Dz1BCDStr *Dz1BCDStrA_newFromStr(str_t src, Dz1Error *err)
{
	size_t len = 0;
	Dz1BCDStr *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || (len = strlen(src)) == 0 || len & 0x1) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1BCDStrA_new(NULL, len>>1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);

		if ((*errp = _setStringDataA(ret, src, len)).code) ERR_OUT(errp);
		else if ((ret->str_buf = Dz1StrA_clone(src, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1BCDStr *Dz1BCDStrA_newFromNibbleSpread(u8_t *nibbleSpreadBCD, size_t byteLen, Dz1Error *err)
{
	Dz1BCDStr *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (nibbleSpreadBCD == NULL || byteLen == 0 || byteLen & 0x01) Dz1Error_set(errp, EINVAL);
	// 데이터가 있고 길이는 짝수임
	else if ((ret = Dz1BCDStrA_new(NULL, byteLen >> 1, errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);

		if ((*errp = _setNibbleSpreadedData(ret, nibbleSpreadBCD, byteLen)).code) { }
		else if ((*errp = _allocAndMakeBCDStrA(ret)).code) { }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}


Dz1Error Dz1BCDStrA_setData(Dz1BCDStr *dst, u8_t *bcdData, size_t byteSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (bcdData == NULL && byteSize == 0)
		{
			if (dst->bcdData != NULL) Dz1Free(dst->bcdData); 
			dst->bcdData = NULL;

			if (dst->str_buf != NULL) Dz1Free(dst->str_buf); 
			dst->str_buf = NULL;

			dst->allocSize = 0;
			dst->size = 0;
		}
		else if (bcdData != NULL && byteSize > 0)
		{
			if (_chkBCDData(bcdData, byteSize) == FALSE) ERR_SET_OUT(&err, EINVAL);
			else if (dst->allocSize >= byteSize)
			{
				dst->size = byteSize;
				memcpy(dst->bcdData, bcdData, dst->size);
				Dz1Free(dst->str_buf); 
				dst->str_buf = NULL;
				if ((err = _allocAndMakeBCDStrA(dst)).code) ERR_OUT(&err);
			}
			else
			{
				if (dst->bcdData != NULL) { Dz1Free(dst->bcdData); dst->bcdData = NULL; } // modified by gm 20230530

				if ((dst->bcdData = (u8_t *)Dz1Malloc((dst->allocSize = byteSize), &err)) == NULL) ERR_OUT(&err);
				else
				{
					dst->size = byteSize;
					memcpy(dst->bcdData, bcdData, dst->size);

					if (dst->str_buf != NULL) Dz1Free(dst->str_buf);
					dst->str_buf = NULL;

					if ((err = _allocAndMakeBCDStrA(dst)).code) ERR_OUT(&err);
				}
			}
		}
		else ERR_SET_OUT(&err, EINVAL);
	}
	return err;
}
#ifndef UNIX_SYSTEM
Dz1BCDStr *Dz1BCDStrW_new(u8_t *bcdData, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1BCDStr *ret = (Dz1BCDStr *)Dz1Calloc(sizeof(Dz1BCDStr), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);
		if (size > 0)
		{	// 사이즈가 있으면 Data 할당, AllocSize 설정, Size 설정
			if ((ret->bcdData = (u8_t *)Dz1Calloc(sizeof(u8_t), (ret->allocSize = size), errp)) == NULL) ERR_OUT(errp);
			// Data가 있으면 BCD인지 확인하면서 복사
			else if (bcdData != NULL && _chkAndCopyBCDData(ret, bcdData, size) == FALSE) ERR_SET_OUT(errp, EINVAL);
			// 출력 문자열 할당
			else if ((*errp = _allocAndMakeBCDStrW(ret)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{	// 사이즈가 없으면 Data = NULL, AllocSize = 0, Size = 0, str = NULL
		}
		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _setStringDataW(Dz1BCDStr *dst, wstr_t src, size_t len)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u8_t *dp = dst->bcdData, *cp = (u8_t *)src, h, l;
	dst->size = 0;
	while(err.code == 0 && len)
	{
		if (*cp < L'0' || *cp > L'9') ERR_SET_OUT(&err, EINVAL);
		else
		{
			h = *cp++ - L'0'; len--;
			if (*cp < L'0' || *cp > L'9') ERR_SET_OUT(&err, EINVAL);
			else
			{
				l = *cp++ - L'0'; len--;
				*dp++ = (h << 4) | l; dst->size++;
			}
		}
	}
	return err;
}

Dz1BCDStr *Dz1BCDStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	size_t len = 0;
	Dz1BCDStr *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || (len = wcslen(src)) == 0 || len & 0x1) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1BCDStrW_new(NULL, len >> 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);

		if ((*errp = _setStringDataW(ret, src, len)).code) ERR_OUT(errp);
		else if ((ret->str_buf = Dz1StrW_clone(src, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1BCDStr *Dz1BCDStrW_newFromNibbleSpread(u8_t *nibbleSpreadBCD, size_t byteLen, Dz1Error *err)
{
	Dz1BCDStr *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (nibbleSpreadBCD == NULL || byteLen == 0 || byteLen & 0x01) Dz1Error_set(errp, EINVAL);
	// 데이터가 있고 길이는 짝수임
	else if ((ret = Dz1BCDStrW_new(NULL, byteLen >> 1, errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1BCDStr_delAndSetNull, (void *)&ret);

		if ((*errp = _setNibbleSpreadedData(ret, nibbleSpreadBCD, byteLen)).code) { }
		else if ((*errp = _allocAndMakeBCDStrW(ret)).code) { }

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1BCDStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}


Dz1Error Dz1BCDStrW_setData(Dz1BCDStr *dst, u8_t *bcdData, size_t byteSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (bcdData == NULL && byteSize == 0)
		{
			if (dst->bcdData != NULL) Dz1Free(dst->bcdData); 
			dst->bcdData = NULL;

			if (dst->str_buf != NULL) Dz1Free(dst->str_buf); 
			dst->str_buf = NULL;

			dst->allocSize = 0;
			dst->size = 0;
		}
		else if (bcdData != NULL && byteSize > 0)
		{
			if (_chkBCDData(bcdData, byteSize) == FALSE) ERR_SET_OUT(&err, EINVAL);
			else if (dst->allocSize >= byteSize)
			{
				dst->size = byteSize;
				memcpy(dst->bcdData, bcdData, dst->size);
				Dz1Free(dst->str_buf); 
				dst->str_buf = NULL;
				if ((err = _allocAndMakeBCDStrW(dst)).code) ERR_OUT(&err);
			}
			else
			{
				if (dst->bcdData != NULL) Dz1Free(dst->bcdData); 
				dst->bcdData = NULL;

				if ((dst->bcdData = (u8_t *)Dz1Malloc((dst->allocSize = byteSize), &err)) == NULL) ERR_OUT(&err);
				else
				{
					dst->size = byteSize;
					memcpy(dst->bcdData, bcdData, dst->size);

					if (dst->str_buf != NULL) Dz1Free(dst->str_buf);
					dst->str_buf = NULL;

					if ((err = _allocAndMakeBCDStrW(dst)).code) ERR_OUT(&err);
				}
			}
		}
		else ERR_SET_OUT(&err, EINVAL);
	}
	return err;
}
#endif

ssize_t Dz1BCDStr_getNibbleSpread(Dz1BCDStr *src, u8_t *dst, size_t dstSize, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL || dstSize == 0 || dstSize & 0x1) { Dz1Error_set(errp, EINVAL); return -1; }
	else
	{
		u8_t *cp = dst, *dp = src->bcdData;
		while(dstSize)
		{
			*cp++ = ((*dp) >> 4) & 0xF; dstSize--; ret++;
			*cp++ = ((*dp) & 0xF); dstSize--; ret++;
			dp++;
		}
	}
	return ret;
}

void Dz1BCDStr_del(Dz1BCDStr *p)
{
	if (p == NULL) return;
	if (p->bcdData != NULL) { Dz1Free(p->bcdData); p->bcdData = NULL; }
	if (p->str_buf != NULL) Dz1Memory_freeAndSetNull(&p->str_buf);
	Dz1Free(p);
}

str_t Dz1BCDStrA_printable(Dz1BCDStr *p)
{
	if (p == NULL) return NULL;
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrA(p);
		return (str_t)p->str_buf;
	}
}

void Dz1BCDStrA_dump(Dz1BCDStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrA(p);
		Dz1ThreadA_printf("%s\n", p->str_buf);
	}
}

void Dz1BCDStrA_fdump(FILE *fp, Dz1BCDStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp,"NULL\n");
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrA(p);
		Dz1ThreadA_fprintf(fp, "%s\n", p->str_buf);
	}
}
#ifndef UNIX_SYSTEM
wstr_t Dz1BCDStrW_printable(Dz1BCDStr *p)
{
	if (p == NULL) return NULL;
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrW(p);
		return (wstr_t)p->str_buf;
	}
}

void Dz1BCDStrW_dump(Dz1BCDStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrW(p);
		Dz1ThreadW_printf(L"%s\n", p->str_buf);
	}
}

void Dz1BCDStrW_fdump(FILE *fp, Dz1BCDStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		if (p->str_buf == NULL) _allocAndMakeBCDStrW(p);
		Dz1ThreadW_fprintf(fp, L"%s\n", p->str_buf);
	}
}
#endif
int Dz1BCDStr_cmp(Dz1BCDStr *a, Dz1BCDStr *b)
{
	int status;
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if ((status = (int)(a->size - b->size)) != 0) return status;
	else return memcmp(a->bcdData, b->bcdData, a->size);
}

ssize_t Dz1BCDStr_enc(u8_t *dst, size_t size, Dz1BCDStr *src, size_t byteNum, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if (src->size < byteNum)
	{
		DZ1_CODEC_ERRSET_RET(errp, ENOMEM);
	}
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE(cp, size, src->bcdData, byteNum, errp, ret);
	}
	return ret;
}


ssize_t Dz1BCDStr_dec(Dz1BCDStr *dst, size_t byteNum, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if (size < byteNum) DZ1_CODEC_ERRSET_RET(errp, E2BIG);
	else if ((*errp = Dz1BCDStr_setData(dst, src, byteNum)).code) DZ1_CODEC_ERR_RET(errp);
	else ret = (ssize_t)byteNum;
	return ret;
}


