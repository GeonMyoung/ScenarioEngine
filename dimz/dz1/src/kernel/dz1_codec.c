#include <dz1_malloc.h>
#include <dz1_codec.h>
#include <ctype.h>
//#include <dz1_elastic_buf.h>
#include <dz1_base64.h>

#ifdef __BORLANDC__
#pragma warn -8070
#endif

ssize_t _get1Byte(u8_t *cp, size_t cpSize, u8_t *c, Dz1Error *errp)
{
	Dz1Error_set(errp, 0);
	if (cpSize < 1)
	{
		Dz1Error_set(errp, E2BIG);
		return -1;
	}

	*c = *cp;
	return 1;
}

ssize_t _put1Byte(u8_t *cp, size_t cpSize, u8_t c, Dz1Error *errp)
{
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 1;
	else if (cpSize < 1) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp = c;
	return 1;
}

ssize_t _get2Byte(u8_t *cp, size_t cpSize, u16_t *c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 2)
	{
		Dz1Error_set(errp, E2BIG);
		return -1;
	}
	*c = (((u16_t)(*cp++)) << 8);
	*c |= ((u16_t)(*cp++) & 0xFF);
	return 2;
}

ssize_t __get2Byte(u8_t *cp, size_t cpSize, u16_t *c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 2) { Dz1Error_set(errp, E2BIG); return -1; }
	*c = ((u16_t)(*cp++) & 0xFF);
	*c |= (((u16_t)(*cp++)) << 8);
	return 2;
}

ssize_t _put2Byte(u8_t *cp, size_t cpSize, u16_t c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 2;
	else if (cpSize < 2) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & 0xFF00) >> 8);
	*cp = (u8_t)((c & 0xFF));
	return 2;
}

ssize_t __put2Byte(u8_t *cp, size_t cpSize, u16_t c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 2;
	else if (cpSize < 2) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & 0xFF));
	*cp = (u8_t)((c & 0xFF00) >> 8);
	return 2;
}

ssize_t _get4Byte(u8_t *cp, size_t cpSize, u32_t *c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 4)
	{
		Dz1Error_set(errp, E2BIG);
		return -1;
	}

	*c = ((u32_t)(*cp++) << 24);
	*c |= ((u32_t)(*cp++) << 16);
	*c |= ((u32_t)(*cp++) << 8);
	*c |= ((u32_t)(*cp++));

	return 4;
}

ssize_t __get4Byte(u8_t *cp, size_t cpSize, u32_t *c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 4)
	{
		Dz1Error_set(errp, E2BIG);
		return -1;
	}

	*c = ((u32_t)(*cp++ & 0xFF));
	*c |= ((u32_t)(*cp++ & 0xFF) << 8);
	*c |= ((u32_t)(*cp++ & 0xFF) << 16);
	*c |= ((u32_t)(*cp++ & 0xFF) << 24);
	return 4;
}

ssize_t _put4Byte(u8_t *cp, size_t cpSize, u32_t c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 4;
	else if (cpSize < 4) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & 0xFF000000) >> 24);
	*cp++ = (u8_t)((c & 0xFF0000) >> 16);
	*cp++ = (u8_t)((c & 0xFF00) >> 8);
	*cp++ = (u8_t)((c & 0xFF));
	return 4;
}

ssize_t __put4Byte(u8_t *cp, size_t cpSize, u32_t c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 4;
	else if (cpSize < 4) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & 0xFF));
	*cp++ = (u8_t)((c & 0xFF00) >> 8);
	*cp++ = (u8_t)((c & 0xFF0000) >> 16);
	*cp++ = (u8_t)((c & 0xFF000000) >> 24);
	return 4;
}

ssize_t _get8Byte(u8_t *cp, size_t cpSize, u64_t *c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 8)
	{
		Dz1Error_set(errp, E2BIG);
		return -1;
	}

	*c = ((u64_t)(*cp++) << 56);
	*c |= ((u64_t)(*cp++) << 48);
	*c |= ((u64_t)(*cp++) << 40);
	*c |= ((u64_t)(*cp++) << 32);
	*c |= ((u64_t)(*cp++) << 24);
	*c |= ((u64_t)(*cp++) << 16);
	*c |= ((u64_t)(*cp++) << 8);
	*c |= ((u64_t)(*cp++));

	return 8;
}

ssize_t __get8Byte(u8_t *cp, size_t cpSize, u64_t *c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cpSize < 8) { Dz1Error_set(errp, E2BIG); return -1; }

	*c = ((u64_t)(*cp++ & 0xFF));
	*c |= ((u64_t)(*cp++ & 0xFF) << 8);
	*c |= ((u64_t)(*cp++ & 0xFF) << 16);
	*c |= ((u64_t)(*cp++ & 0xFF) << 24);
	*c |= ((u64_t)(*cp++ & 0xFF) << 32);
	*c |= ((u64_t)(*cp++ & 0xFF) << 40);
	*c |= ((u64_t)(*cp++ & 0xFF) << 48);
	*c |= ((u64_t)(*cp++ & 0xFF) << 56);
	return 8;
}

ssize_t _put8Byte(u8_t *cp, size_t cpSize, u64_t c, Dz1Error *errp)
{	// BigEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 8;
	else if (cpSize < 8) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00000000000000)) >> 56);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF000000000000)) >> 48);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF0000000000)) >> 40);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00000000)) >> 32);

	*cp++ = (u8_t)((c & DZ1UINT64(0xFF000000)) >> 24);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF0000)) >> 16);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00)) >> 8);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF)));
	return 8;
}

ssize_t __put8Byte(u8_t *cp, size_t cpSize, u64_t c, Dz1Error *errp)
{	// LittleEndian
	Dz1Error_set(errp, 0);
	if (cp == NULL) return 8;
	else if (cpSize < 8) { Dz1Error_set(errp, E2BIG); return -1; }
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF)));
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00)) >> 8);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF0000)) >> 16);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF000000)) >> 24);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00000000)) >> 32);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF0000000000)) >> 40);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF000000000000)) >> 48);
	*cp++ = (u8_t)((c & DZ1UINT64(0xFF00000000000000)) >> 56);
	return 8;
}

ssize_t _getByte(u8_t *cp, size_t cpSize, u8_t *dst, size_t dstSize, Dz1Error *errp)
{
	Dz1Error_set(errp, 0);
	if (cpSize < dstSize) { Dz1Error_set(errp, E2BIG); return -1; }
	memcpy(dst, cp, dstSize);
	return (ssize_t)dstSize;
}

ssize_t _putByte(u8_t *cp, size_t cpSize, u8_t *src, size_t srcSize, Dz1Error *errp)
{
	Dz1Error_set(errp, 0);
	if (cp == NULL) return (ssize_t)srcSize;
	else if (cpSize < srcSize) { Dz1Error_set(errp, E2BIG); return -1; }
	memcpy(cp, src, srcSize);
	return (ssize_t)srcSize;
}

ssize_t _get8str(u8_t *cp, size_t size, str_t *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!cp || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u8_t len = 0;

		DZ1_DECODE1(&len, cp, size, errp, ret);

		if (len == 0) (*dst) = NULL;
		else
		{
			if (((*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			DZ1_DECODE((u8_t *)(*dst), (size_t)len, cp, size, errp, ret);
		}
		return ret;
	}
}

ssize_t _get16str(u8_t *cp, size_t size, str_t *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!cp || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u16_t len = 0;

		DZ1_DECODE2(&len, cp, size, errp, ret);

		if (len == 0) (*dst) = NULL;
		else
		{
			if (((*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			DZ1_DECODE((u8_t *)(*dst), (size_t)len, cp, size, errp, ret);
		}
		return ret;
	}
}

ssize_t __get16str(u8_t *cp, size_t size, str_t *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!cp || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u16_t len = 0;

		_DZ1_DECODE2(&len, cp, size, errp, ret);

		if (len == 0) (*dst) = NULL;
		else
		{
			if (((*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			DZ1_DECODE((u8_t *)(*dst), (size_t)len, cp, size, errp, ret);
		}
		return ret;
	}
}

ssize_t _put8str(u8_t *cp, size_t size, str_t src, Dz1Error *err)
{
	ssize_t ret = 0;
	size_t len = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src || (len = strlen(src)) == 0)
	{
		DZ1_ENCODE1(cp, size, 0, errp, ret);
	}
	else
	{
		DZ1_ENCODE1(cp, size, (u8_t)len, errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)src, len, errp, ret);
	}
	return ret;
}

ssize_t _put16str(u8_t *cp, size_t size, str_t src, Dz1Error *err)
{
	ssize_t ret = 0;
	size_t len = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src || (len = strlen(src)) == 0)
	{
		DZ1_ENCODE2(cp, size, 0, errp, ret);
	}
	else
	{
		DZ1_ENCODE2(cp, size, (u16_t)len, errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)src, len, errp, ret);
	}
	return ret;
}

ssize_t __put16str(u8_t *cp, size_t size, str_t src, Dz1Error *err)
{
	ssize_t ret = 0;
	size_t len = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src || (len = strlen(src)) == 0)
	{
		_DZ1_ENCODE2(cp, size, 0, errp, ret);
	}
	else
	{
		_DZ1_ENCODE2(cp, size, (u16_t)(len & 0xFFFF), errp, ret);
		DZ1_ENCODE(cp, size, (u8_t *)src, len, errp, ret);
	}
	return ret;
}

static int _ascii2int(char c)
{
	int ret = 0;
	if (c >= '0' && c <= '9') ret = c - '0';
	return ret;
}

ssize_t  _getDigit(u8_t *cp, size_t size, u32_t *dst, size_t len, Dz1Error *errp)
{
	ssize_t ret = (ssize_t)len;
	char c;
	if (size < len) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		*dst = 0;
		while(len--)
		{
			c = (char)*cp;
			cp++;
			if (!isdigit(((int)c & 0xFF)))
			{
				if (c >= 0 && c <= 9) (*dst) = (*dst) * 10 + c;
				else
				{
					ERR_SET_OUT(errp, EINVAL);
					return -1;
				}
			}
			else (*dst) = (*dst) * 10 + _ascii2int(c);
		}
	}
	return ret;
}

static bool_t isHexDigit(u8_t c)
{
	if (c >= 'a' && c <= 'f') return TRUE;
	if (c >= 'A' && c <= 'F') return TRUE;
	if (c >= '0' && c <= '9') return TRUE;
	return FALSE;
}

static u8_t _toHexValue(u8_t c)
{
	if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
	if (c >= '0' && c <= '9') return (c - '0');
	return 0;
}

static ssize_t _getHex0(u8_t *cp, size_t size, u8_t *dst, Dz1Error *errp)
{
	if (size < 1) { Dz1Error_set(errp, E2BIG); return -1; }

	if (isHexDigit(*cp) == FALSE)
	{
		ERR_SET_OUT(errp, EFAULT);
		return -1;
	}
	else
	{
		if (dst != NULL) (*dst) = _toHexValue(*cp);
		return 1;
	}
}

ssize_t _getHexDigit(u8_t *cp, size_t size, u8_t *dst, Dz1Error *errp)
{
	u8_t v0, v1;
	ssize_t ret = 0, status;
	while(size > 0 && isspace(((int)*cp) & 0xFF)) { cp++; ret++; size--; }
	if ((status = _getHex0(cp, size, &v0, errp)) < 0) DZ1_CODEC_ERR_RET(errp); else DZ1_CODEC_APPLY(cp, size, status, ret);
	if ((status = _getHex0(cp, size, &v1, errp)) < 0) DZ1_CODEC_ERR_RET(errp); else DZ1_CODEC_APPLY(cp, size, status, ret);
	if (dst != NULL) (*dst) = v0 << 4 | v1;
	return ret;
}

static Dz1Error _parseBCD(u32_t *v, u8_t bcd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u32_t h = (u32_t)((bcd & 0xF0) >> 4);
	u32_t l = (u32_t)(bcd & 0x0F);

	if (h > 9) ERR_SET_OUT(&err, EINVAL);
	else if (l > 9) ERR_SET_OUT(&err, EINVAL);
	else (*v) = (*v) * 100 + h * 10 + l;

	return err;
}

ssize_t _getBCD(u8_t *cp, size_t size, u32_t *dst, size_t len, Dz1Error *errp)
{
	ssize_t ret = (ssize_t)len;
	u8_t c;
	if (cp == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if (size < len) DZ1_CODEC_ERRSET_RET(errp, E2BIG);
	else
	{
		*dst = 0;
		while(len--)
		{
			c = *cp++;
			if ((*errp = _parseBCD(dst, c)).code) DZ1_CODEC_ERR_RET(errp);
		}
	}
	return ret;
}

Dz1CodecApiMap *Dz1CodecApiMap_findByPresent(Dz1CodecApiMap *table, int present)
{
	Dz1CodecApiMap *i;
	for (i = table; i->present != -1; i++)
		if (i->present == present) return i;
	return NULL;
}

Dz1CodecApiMap *Dz1CodecApiMap_findByOpCode(Dz1CodecApiMap *table, u32_t opcode)
{
	Dz1CodecApiMap *i;
	for (i = table; i->present != -1; i++)
		if (i->opcode == opcode) return i;
	return NULL;
}

ssize_t _u8_hex_enc(u8_t *dst, size_t size, u8_t *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, *src, errp, ret);
	}
	return ret;
}

ssize_t _u8_hex_dec(u8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE1(dst, cp, size, errp, ret);
	}
	return ret;
}

ssize_t _u8_bcd_enc(u8_t *dst, size_t size, u8_t *_src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, src = *_src;
		u8_t v = (((src / 10) & 0xF) << 4) | ((src % 10) & 0xF);
		DZ1_ENCODE1(cp, size, v, errp, ret);
	}
	return ret;
}

ssize_t _u8_bcd_dec(u8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE1(&v, cp, size, errp, ret);
		(*dst) = (((v >> 4) & 0xF) * 10) + (v & 0xF);
	}
	return ret;
}

ssize_t _u16_bcd_enc(u8_t *dst, size_t size, u16_t *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (_src == NULL)
	{
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	}
	else
	{
		u8_t *cp = dst;
		u16_t src = *_src;
		u8_t h = src / 100, l = src % 100;
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &h, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &l, param, errp), errp);
	}
	return ret;
}

ssize_t _u16_bcd_dec(u16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, h, l;
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&h, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&l, cp, size, param, errp), errp);
		(*dst) = ((u16_t)h * 100) + l;
	}
	return ret;
}

ssize_t _u16_hex_enc(u8_t *dst, size_t size, u16_t *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE2(cp, size, *src, errp, ret);
	}
	return ret;
}

ssize_t _u16_hex_dec(u16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE2(dst, cp, size, errp, ret);
	}
	return ret;
}

ssize_t _time_hex_enc(u8_t *dst, size_t size, time_t src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	struct tm *tm_p = localtime(&src);
	if (tm_p == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		struct tm tSrc = *tm_p;
		u16_t Y = (u16_t)((tSrc.tm_year + 1900) & 0xFFFF);
		u8_t M = (u8_t)((tSrc.tm_mon + 1) & 0xFF);
		u8_t D = (u8_t)(tSrc.tm_mday & 0xFF);
		u8_t h = (u8_t)(tSrc.tm_hour & 0xFF);
		u8_t m = (u8_t)(tSrc.tm_min & 0xFF);
		u8_t s = (u8_t)(tSrc.tm_sec & 0xFF);
		u8_t *cp = dst;
		DZ1_ENCODE2(cp, size, Y, errp, ret);
		DZ1_ENCODE1(cp, size, M, errp, ret);
		DZ1_ENCODE1(cp, size, D, errp, ret);
		DZ1_ENCODE1(cp, size, h, errp, ret);
		DZ1_ENCODE1(cp, size, m, errp, ret);
		DZ1_ENCODE1(cp, size, s, errp, ret);
	}
	return ret;
}

ssize_t _time_hex_dec(time_t *dst, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		struct tm tSrc;
		u16_t Y;
		u8_t M, D, h, m, s;
		u8_t *cp = src;
		DZ1_DECODE2(&Y, cp, size, errp, ret);
		DZ1_DECODE1(&M, cp, size, errp, ret);
		DZ1_DECODE1(&D, cp, size, errp, ret);
		DZ1_DECODE1(&h, cp, size, errp, ret);
		DZ1_DECODE1(&m, cp, size, errp, ret);
		DZ1_DECODE1(&s, cp, size, errp, ret);
		tSrc.tm_year = Y - 1900;
		tSrc.tm_mon = M - 1;
		tSrc.tm_mday = D;
		tSrc.tm_hour = h;
		tSrc.tm_min = m;
		tSrc.tm_sec = s;
		(*dst) = mktime(&tSrc);
	}
	return ret;
}

ssize_t _time_bcd_enc(u8_t *dst, size_t size, time_t *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		time_t src = *_src;
		struct tm *tm_p = NULL;
		if (src == 0)
		{
			u8_t temp[7] = { 0, };
			DZ1_ENCODE(cp, size, temp, 7, errp, ret);
		}
		else if ((tm_p = localtime(&src)) == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		else
		{
			struct tm tmSrc = *tm_p;
			u16_t y = tmSrc.tm_year + 1900;
			u8_t m = tmSrc.tm_mon + 1;
			u8_t d = tmSrc.tm_mday;
			u8_t h = tmSrc.tm_hour;
			u8_t mi = tmSrc.tm_min;
			u8_t s = tmSrc.tm_sec;
			DZ1_CODEC_FUNC(cp, size, ret, _u16_bcd_enc(cp, size, &y, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &m, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &d, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &h, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &mi, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &s, param, errp), errp);
		}
	}
	return ret;
}

ssize_t _time_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u16_t y;
		u8_t *cp = src, m,d,h,mi,s;
		DZ1_CODEC_FUNC(cp, size, ret, _u16_bcd_dec(&y, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&m, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&d, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&h, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&mi, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&s, cp, size, param, errp), errp);
		if (y == 0 && m == 0 && d == 0 && h == 0 && mi == 0 && s == 0)
		{
			(*dst) = 0;
		}
		else
		{
			struct tm tmTmp;
			tmTmp.tm_year = y - 1900;
			tmTmp.tm_mon = m - 1;
			tmTmp.tm_mday = d;
			tmTmp.tm_hour = h;
			tmTmp.tm_min = mi;
			tmTmp.tm_sec = s;
			(*dst) = mktime(&tmTmp);
		}
	}
	return ret;
}

ssize_t _date_bcd_enc(u8_t *dst, size_t size, time_t *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		time_t src = *_src;
		struct tm *tm_p = NULL;
		if (src == 0)
		{
			u8_t temp[4] = { 0, };
			DZ1_ENCODE(cp, size, temp, 4, errp, ret);
		}
		else if ((tm_p = localtime(&src)) == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		else
		{
			struct tm tmSrc = *tm_p;
			u16_t y = tmSrc.tm_year + 1900;
			u8_t m = tmSrc.tm_mon + 1;
			u8_t d = tmSrc.tm_mday;
			DZ1_CODEC_FUNC(cp, size, ret, _u16_bcd_enc(cp, size, &y, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &m, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &d, param, errp), errp);
		}
	}
	return ret;
}

ssize_t _date_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u16_t y;
		u8_t *cp = src, m,d;
		DZ1_CODEC_FUNC(cp, size, ret, _u16_bcd_dec(&y, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&m, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&d, cp, size, param, errp), errp);
		if (y == 0 && m == 0 && d == 0)
		{
			(*dst) = 0;
		}
		else
		{
			struct tm tmTmp;
			tmTmp.tm_year = y - 1900;
			tmTmp.tm_mon = m - 1;
			tmTmp.tm_mday = d;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			(*dst) = mktime(&tmTmp);
		}
	}
	return ret;
}

ssize_t _clock_bcd_enc(u8_t *dst, size_t size, time_t *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		time_t src = *_src;
		struct tm *tm_p = NULL;
		if (src == 0)
		{
			u8_t temp[3] = { 0, };
			DZ1_ENCODE(cp, size, temp, 3, errp, ret);
		}
		else if ((tm_p = localtime(&src)) == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		else
		{
			struct tm tmSrc = *tm_p;
			u8_t h = tmSrc.tm_hour;
			u8_t mi = tmSrc.tm_min;
			u8_t s = tmSrc.tm_sec;
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &h, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &mi, param, errp), errp);
			DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_enc(cp, size, &s, param, errp), errp);
		}
	}
	return ret;
}

ssize_t _clock_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, h = 0, mi = 0, s = 0;
		time_t tNow = *dst == 0 ? time(NULL) : (*dst);
		struct tm *tm_p = localtime(&tNow), tmTmp;
		if (tm_p == NULL)
		{
			tNow = time(NULL);
			tm_p = localtime(&tNow);
		}
		tmTmp = *tm_p;

		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&h, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&mi, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _u8_bcd_dec(&s, cp, size, param, errp), errp);
		tmTmp.tm_hour = h;
		tmTmp.tm_min = mi;
		tmTmp.tm_sec = s;
		(*dst) = mktime(&tmTmp);
	}
	return ret;
}

static ssize_t _encode_big_opcode(u8_t *dst, size_t size, u32_t opcode, size_t codeLen, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = dst;
	switch(codeLen)
	{
	case 1:
		DZ1_ENCODE1(cp, size, (u8_t)(opcode & 0xFF), errp, ret);
		break;
	case 2:
		DZ1_ENCODE2(cp, size, (u16_t)(opcode & 0xFFFF), errp, ret);
		break;
	case 4:
		DZ1_ENCODE4(cp, size, opcode, errp, ret);
		break;
	default:
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		break;
	}
	return ret;
}

static ssize_t _encode_little_opcode(u8_t *dst, size_t size, u32_t opcode, size_t codeLen, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = dst;
	switch(codeLen)
	{
	case 1:
		_DZ1_ENCODE1(cp, size, (u8_t)(opcode & 0xFF), errp, ret);
		break;
	case 2:
		_DZ1_ENCODE2(cp, size, (u16_t)(opcode & 0xFFFF), errp, ret);
		break;
	case 4:
		_DZ1_ENCODE4(cp, size, opcode, errp, ret);
		break;
	default:
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		break;
	}
	return ret;
}

static ssize_t _encode_opcode(u8_t *dst, size_t size, u32_t opcode, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *errp)
{
	if (codeIsBigEndian) return _encode_big_opcode(dst, size, opcode, codeLen, errp);
	else return _encode_little_opcode(dst, size, opcode, codeLen, errp);
}

static ssize_t _decode_big_opcode(u32_t *dst, size_t codeLen, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = src, v8;
	u16_t v16;
	switch(codeLen)
	{
	case 1:
		DZ1_DECODE1(&v8, cp, size, errp, ret);
		*dst = ((u32_t)v8) & 0xFF;
		break;
	case 2:
		DZ1_DECODE2(&v16, cp, size, errp, ret);
		*dst = ((u32_t)v16) & 0xFFFF;
		break;
	case 4:
		DZ1_DECODE4(dst, cp, size, errp, ret);
		break;
	default:
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		break;
	}
	return ret;
}

static ssize_t _decode_little_opcode(u32_t *dst, size_t codeLen, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = src, v8;
	u16_t v16;
	switch(codeLen)
	{
	case 1:
		_DZ1_DECODE1(&v8, cp, size, errp, ret);
		*dst = ((u32_t)v8) & 0xFF;
		break;
	case 2:
		_DZ1_DECODE2(&v16, cp, size, errp, ret);
		*dst = ((u32_t)v16) & 0xFFFF;
		break;
	case 4:
		_DZ1_DECODE4(dst, cp, size, errp, ret);
		break;
	default:
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
		break;
	}
	return ret;
}

static ssize_t _decode_opcode(u32_t *dst, size_t codeLen, u8_t *src, size_t size, bool_t isBitEndian, Dz1Error *errp)
{
	if (isBitEndian) return _decode_big_opcode(dst, codeLen, src, size, errp);
	else return _decode_little_opcode(dst, codeLen, src, size, errp);
}

typedef enum Dz1UnionCodecPresent
{
	unknown
} Dz1UnionCodecPresent;

typedef struct Dz1UnionCodecMask
{
	Dz1UnionCodecPresent	present;
	union {
		void				*__ptr__;
		u8_t				varAddr[0];
	} x;
} Dz1UnionCodecMask;

static ssize_t _Dz1UnionCodec_enc(u8_t *dst, size_t size, Dz1UnionCodecMask *src, void *param, Dz1CodecApiMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;

	u8_t *cp = dst;
	if (api->gen == NULL)
	{	// static variable type
		if (api->enc) DZ1_CODEC_FUNC(cp, size, ret, api->enc(cp, size, (void *)src->x.varAddr, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->enc) DZ1_CODEC_FUNC(cp, size, ret, api->enc(cp, size, src->x.__ptr__, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1CodecApiMap *api = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask *src = (Dz1UnionCodecMask *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((api = Dz1CodecApiMap_findByPresent(table, (int)src->present)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _encode_opcode(cp, size, api->opcode, codeLen, codeIsBigEndian, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec_enc(cp, size, src, param, api, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec_encByPresent(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1CodecApiMap *api = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask *src = (Dz1UnionCodecMask *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((api = Dz1CodecApiMap_findByPresent(table, (int)src->present)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec_enc(cp, size, src, param, api, errp), errp);
	}
	return ret;
}

static ssize_t _Dz1UnionCodec_dec(Dz1UnionCodecMask *dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = src;
	if (api->gen == NULL)
	{	// static variable type
		if (api->dec) DZ1_CODEC_FUNC(cp, size, ret, api->dec(dst->x.varAddr, cp, size, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->gen != NULL && (dst->x.__ptr__ = api->gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else if (api->dec) DZ1_CODEC_FUNC(cp, size, ret, api->dec(dst->x.__ptr__, cp, size, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask *dst = (Dz1UnionCodecMask *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t opcode;
		u8_t *cp = src;
		Dz1CodecApiMap *api = NULL;
		DZ1_CODEC_FUNC(cp, size, ret, _decode_opcode(&opcode, codeLen, cp, size, codeIsBigEndian, errp), errp);
		if ((api = Dz1CodecApiMap_findByOpCode(table, opcode)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
		else
		{
			dst->present = (Dz1UnionCodecPresent)api->present;
			DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec_dec(dst, cp, size, param, api, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1UnionCodec_decByPresent(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask *dst = (Dz1UnionCodecMask *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		Dz1CodecApiMap *api = NULL;
		if ((api = Dz1CodecApiMap_findByPresent(table, dst->present)) == NULL)
		{
			DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
		}
		else DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec_dec(dst, cp, size, param, api, errp), errp);
	}
	return ret;
}



























typedef struct Dz1UnionCodecMask64
{
	Dz1UnionCodecPresent	present;
	union {
		void			*__ptr__;
		unsigned char	 b1[1];
		unsigned char	 b2[2];
		unsigned char	 b4[4];
		unsigned char	 b8[8];
		u8_t			 varAddr[0];  
		u64_t			 val64;
	} x;
} Dz1UnionCodecMask64;

static ssize_t _Dz1UnionCodec64_enc(u8_t *dst, size_t size, Dz1UnionCodecMask64 *src, void *param, Dz1CodecApiMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;

	u8_t *cp = dst;
	if (api->gen == NULL)
	{	// static variable type
		if (api->enc) DZ1_CODEC_FUNC(cp, size, ret, api->enc(cp, size, (void *)src->x.varAddr, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->enc) DZ1_CODEC_FUNC(cp, size, ret, api->enc(cp, size, src->x.__ptr__, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec64_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1CodecApiMap *api = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask64 *src = (Dz1UnionCodecMask64 *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((api = Dz1CodecApiMap_findByPresent(table, (int)src->present)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _encode_opcode(cp, size, api->opcode, codeLen, codeIsBigEndian, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec64_enc(cp, size, src, param, api, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec64_encByPresent(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1CodecApiMap *api = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask64 *src = (Dz1UnionCodecMask64 *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((api = Dz1CodecApiMap_findByPresent(table, (int)src->present)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec64_enc(cp, size, src, param, api, errp), errp);
	}
	return ret;
}

static ssize_t _Dz1UnionCodec64_dec(Dz1UnionCodecMask64 *dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *cp = src;
	if (api->gen == NULL)
	{	// static variable type
		if (api->dec) DZ1_CODEC_FUNC(cp, size, ret, api->dec(dst->x.varAddr, cp, size, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->gen != NULL && (dst->x.__ptr__ = api->gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else if (api->dec) DZ1_CODEC_FUNC(cp, size, ret, api->dec(dst->x.__ptr__, cp, size, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1UnionCodec64_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask64 *dst = (Dz1UnionCodecMask64 *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t opcode;
		u8_t *cp = src;
		Dz1CodecApiMap *api = NULL;
		DZ1_CODEC_FUNC(cp, size, ret, _decode_opcode(&opcode, codeLen, cp, size, codeIsBigEndian, errp), errp);
		if ((api = Dz1CodecApiMap_findByOpCode(table, opcode)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
		else
		{
			dst->present = (Dz1UnionCodecPresent)api->present;
			DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec64_dec(dst, cp, size, param, api, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1UnionCodec64_decByPresent(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionCodecMask64 *dst = (Dz1UnionCodecMask64 *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		Dz1CodecApiMap *api = NULL;
		if ((api = Dz1CodecApiMap_findByPresent(table, dst->present)) == NULL)
		{
			DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
		}
		else DZ1_CODEC_FUNC(cp, size, ret, _Dz1UnionCodec64_dec(dst, cp, size, param, api, errp), errp);
	}
	return ret;
}





























Dz1TimeVal *Dz1TimeVal_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TimeVal *ret = (Dz1TimeVal *)Dz1Calloc(sizeof(Dz1TimeVal), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t Dz1TimeVal_enc(u8_t *dst, size_t size, Dz1TimeVal *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		time_t t = (time_t)src->tv_sec;
		DZ1_CODEC_FUNC(cp, size, ret, _time_hex_enc(cp, size, t, errp), errp);
		DZ1_ENCODE4(cp, size, src->tv_usec, errp, ret);
	}
	return ret;
}

ssize_t Dz1TimeVal_dec(Dz1TimeVal *dst, u8_t *src, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		time_t t = 0;
		DZ1_CODEC_FUNC(cp, size, ret, _time_hex_dec(&t, cp, size, errp), errp);
		dst->tv_sec = (long)t;
		DZ1_DECODE4((u32_t *)&dst->tv_usec, cp, size, errp, ret);
	}
	return ret;
}











///////////////////////////////////////////////////////////////////////////////
// Base64 Encode

/*
static size_t _copy3byte(u8_t *dst, u8_t *src, size_t src_size)
{
	size_t copy_size = src_size >= 3 ? 3 : src_size;
	if (copy_size > 0)
	{
		size_t i;
		u8_t *cp = dst;
		memcpy(cp, src, copy_size);
		for (i = copy_size; i < 3; i++) *cp++ = 0;
	}
	return copy_size;
}

size_t Dz1Codec_Base64EncLen(size_t size)
{
	size_t ret = 0;
	if (size > 0)
	{
		u32_t blk_cnt = (u32_t)(size / 3);
		u32_t mod_sz = size % 3;
		ret = (blk_cnt + (mod_sz ? 1 : 0)) * 4;
	}
	return ret;
}

size_t Dz1Codec_Base64DecLen(size_t size)
{
	size_t ret = 0;
	if (size > 0)
	{
		u32_t blk_cnt = (u32_t)(size / 4);
		u32_t mod_sz = size % 4;
		ret = (blk_cnt + (mod_sz ? 1 : 0)) * 3;
	}
	return ret;
}
*/
// Base64 Encode
///////////////////////////////////////////////////////////////////////////////

ssize_t _getBase64(u8_t *dst, size_t dst_size, u8_t *src, size_t src_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL || src_size == 0) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t status = 0;

		char *cp = (char *)src;
		u8_t *dp = dst;

		u8_t temp[3];
		size_t temp_out = 0;
		do 
		{
			if ((status = Dz1Base64_decBlockA(temp, 3, &temp_out, cp, src_size, errp)) == -1)	// Base64 data on Stream is always ASCII
				DZ1_CODEC_ERR_RET(errp);
			else if (status == 0) break;
			else
			{
				DZ1_CODEC_APPLY(cp, src_size, status, ret);
				if (dst_size < temp_out) DZ1_CODEC_ERRSET_RET(errp, ENOMEM);
				else
				{
					memcpy(dp, temp, temp_out);
					dp += temp_out;
					dst_size -= temp_out;
				}
			}
		} while (status == 4);
		if (dst_size > 0) *dp = '\0'; // pseudo string termination
	}
	return ret;
}

ssize_t _putBase64(u8_t *dst, size_t size, u8_t *src, size_t src_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	char *dp = (char *)dst;
	if (src == NULL || src_size == 0) { /* NOP */ }
	else
	{
		ssize_t sz;
		u8_t *sp = src;
		while(errp->code == 0 && size > 0 && src_size > 0)
		{
			if ((sz = Dz1Base64_encBlockA(dp, size, sp, src_size, errp)) < 0)
				ERR_OUT(errp);
			else
			{
				dp += 4;
				size -= 4;

				sp += sz;
				src_size -= sz;
			}
		}
	}

	if (dst != NULL && size > 0) *dp = '\0';	// pseudo string termination

	return ret;
}

ssize_t _putBase64StrA(u8_t *dst, size_t size, str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;

	u8_t *cp = dst;

	if (src == NULL) //DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	{
		DZ1_CODEC_FUNC(cp, size, ret, _putBase64(dst, size, NULL, 0, errp), errp);
	}
	else
	{
		size_t len = strlen(src);
		DZ1_CODEC_FUNC(cp, size, ret, _putBase64(dst, size, (u8_t *)src, len, errp), errp);
	}
	return ret;
}

ssize_t _putBase64StrW(u8_t *dst, size_t size, wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;

	u8_t *cp = dst;

	if (src == NULL) //DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	{
		DZ1_CODEC_FUNC(cp, size, ret, _putBase64(dst, size, NULL, 0, errp), errp);
	}
	else
	{
		size_t byte_len = wcslen(src) * sizeof(TCHAR);
		DZ1_CODEC_FUNC(cp, size, ret, _putBase64(dst, size, (u8_t *)src, byte_len, errp), errp);
	}
	return ret;
}
