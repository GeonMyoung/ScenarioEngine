#include <dz1_base64.h>
#include <dz1_elastic_buf.h>

static const char encodingTableA [64] = {
	'A','B','C','D','E','F','G','H', // 0 ~ 7
	'I','J','K','L','M','N','O','P', // 8 ~ 15
	'Q','R','S','T','U','V','W','X', // 16 ~ 23
	'Y','Z','a','b','c','d','e','f', // 24 ~ 31
	'g','h','i','j','k','l','m','n', // 32 ~ 39
	'o','p','q','r','s','t','u','v', // 40 ~ 47
	'w','x','y','z','0','1','2','3', // 48 ~ 55
	'4','5','6','7','8','9','+','/'	 // 56 ~ 63
};

#ifndef UNIX_SYSTEM
static const wchar_t encodingTableW [64] = {
	L'A',L'B',L'C',L'D',L'E',L'F',L'G',L'H', // 0 ~ 7
	L'I',L'J',L'K',L'L',L'M',L'N',L'O',L'P', // 8 ~ 15
	L'Q',L'R',L'S',L'T',L'U',L'V',L'W',L'X', // 16 ~ 23
	L'Y',L'Z',L'a',L'b',L'c',L'd',L'e',L'f', // 24 ~ 31
	L'g',L'h',L'i',L'j',L'k',L'l',L'm',L'n', // 32 ~ 39
	L'o',L'p',L'q',L'r',L's',L't',L'u',L'v', // 40 ~ 47
	L'w',L'x',L'y',L'z',L'0',L'1',L'2',L'3', // 48 ~ 55
	L'4',L'5',L'6',L'7',L'8',L'9',L'+',L'/'	 // 56 ~ 63
};
#endif

///////////////////////////////////////////////////////////////////////////////
// Single block Encode
ssize_t Dz1Base64_encBlockA(char *dst, size_t dst_sz, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || dst_sz < 4 || src == NULL || size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		size_t cp_size = size > 3 ? 3 : size;
		u8_t temp[3] = { 0, };
		memcpy(temp, src, cp_size);

		dst[0] = encodingTableA[(temp[0] >> 2)];
		dst[1] = encodingTableA[(((temp[0] & 0x03) << 4) | (temp[1] >> 4))];
		if (cp_size > 1)
		{
			dst[2] = encodingTableA[(((temp[1] & 0xF) << 2) |  (temp[2] >> 6))];
			if (cp_size > 2)
				dst[3] = encodingTableA[(temp[2] & 0x3F)];
			else dst[3] = '=';
		}
		else
		{
			dst[2] = '=';
			dst[3] = '=';
		}
		ret = (ssize_t)cp_size;
	}
	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1Base64_encBlockW(wchar_t *dst, size_t dst_sz, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || dst_sz < 4 || src == NULL || size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		size_t cp_size = size > 3 ? 3 : size;
		u8_t temp[3] = { 0, };
		memcpy(temp, src, cp_size);

		dst[0] = encodingTableW[(temp[0] >> 2)];
		dst[1] = encodingTableW[(((temp[0] & 0x03) << 4) | (temp[1] >> 4))];
		if (cp_size > 1)
		{
			dst[2] = encodingTableW[(((temp[1] & 0xF) << 2) |  (temp[2] >> 6))];
			if (cp_size > 2)
				dst[3] = encodingTableW[(temp[2] & 0x3F)];
			else dst[3] = L'=';
		}
		else
		{
			dst[2] = L'=';
			dst[3] = L'=';
		}
		ret = (ssize_t)cp_size;
	}
	return ret;
}
#endif
// Single block Encode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Base64 Encode
str_t Dz1Base64_encA(u8_t *src, ssize_t src_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	Dz1ElasticBuf *elb = NULL;
	if (src == NULL || src_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char dst[5] = { 0, };
		ssize_t sz;
		u32_t blk_cnt = 0;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		while(errp->code == 0 && src_size > 0)
		{
			if ((sz = Dz1Base64_encBlockA(dst, 4, src, src_size, errp)) < 0) ERR_OUT(errp);
			else if (Dz1ElasticBuf_pushStrA(elb, dst, errp) == FALSE) ERR_OUT(errp);
			else
			{
				src += sz;
				src_size -= sz;
				blk_cnt++;
				if (blk_cnt % 19 == 0)
				{
					if (Dz1ElasticBuf_pushStrA(elb, (str_t)"\n", errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					blk_cnt = 0;
				}
			}
		}

		if (errp->code == 0)
		{
			if ((ret = Dz1ElasticBuf_flattenStrAndPurgeA(elb, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1Base64_encW(u8_t *src, ssize_t src_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	Dz1ElasticBuf *elb = NULL;
	if (src == NULL || src_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t dst[5] = { 0, };
		ssize_t sz;
		u32_t blk_cnt = 0;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		while(errp->code == 0 && src_size > 0)
		{
			dst[4] = 0;
			if ((sz = Dz1Base64_encBlockW(dst, 4, src, src_size, errp)) < 0) ERR_OUT(errp);
			else if (Dz1ElasticBuf_pushStrW(elb, dst, errp) == FALSE) ERR_OUT(errp);
			else
			{
				src += sz;
				src_size -= sz;
				blk_cnt++;
				if (blk_cnt % 19 == 0)
				{
					if (Dz1ElasticBuf_pushStrW(elb, (wstr_t)L"\n", errp) == FALSE) ERR_OUT(errp);
					else  Dz1Error_set(errp, 0);
					blk_cnt = 0;
				}
			}
		}

		if (errp->code == 0)
		{
			if ((ret = Dz1ElasticBuf_flattenStrAndPurgeW(elb, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ret;
}
#endif
// Base64 Encode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Base64 Decode Utility
static int _getBase64IdxA(char v)
{
	u32_t ret = -1;
	if (0) { }
	else if (v == '=') ret = -2;
	else if (v == '+') ret = 62;									// 63
	else if (v == '/') ret = 63;									// 64
	if (v >= 'A' && v <= 'Z') ret = (u32_t)(v - 'A');				// 0~25
	else if (v >= 'a' && v <= 'z') ret = (u32_t)((v - 'a') + 26);	// 26~51
	else if (v >= '0' && v <= '9') ret = (u32_t)((v - '0') + 52);	// 62~61
	return ret;
}

#ifndef UNIX_SYSTEM
static int _getBase64IdxW(wchar_t v)
{
	u32_t ret = -1;
	if (0) { }
	else if (v == L'=') ret = -2;
	else if (v == L'+') ret = 62;									// 63
	else if (v == L'/') ret = 63;									// 64
	if (v >= L'A' && v <= L'Z') ret = (u32_t)(v - L'A');			// 0~25
	else if (v >= L'a' && v <= L'z') ret = (u32_t)((v - L'a') + 26);// 26~51
	else if (v >= L'0' && v <= L'9') ret = (u32_t)((v - L'0') + 52);// 62~61
	return ret;
}
#endif

static void _setOutputData(u8_t dst[3], int val, u32_t pos, size_t *out_size)
{
	switch(pos)
	{
	case 0: 
		dst[0] = (val << 2);
		*out_size = 1;
		break;
	case 1:
		dst[0] = dst[0] | ((val >> 4) & 0x3);
		dst[1] = (val & 0xF) << 4;
		*out_size = 1;
		break;
	case 2:
		dst[1] = dst[1] | ((val & 0x3C) >> 2);
		dst[2] = (val & 0x03) << 6;
		*out_size = 2;
		break;
	case 3:
		dst[2] = dst[2] | (val & 0x3F);
		*out_size = 3;
		break;
	}
}
// Base64 Decode Utility
///////////////////////////////////////////////////////////////////////////////

ssize_t Dz1Base64_decBlockA(u8_t *dst, size_t dst_sz, size_t *outsize, char *src, size_t src_size, Dz1Error *errp)
{
	ssize_t ret = -1;

	if (dst == NULL || dst_sz < 3 || src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		ssize_t consume = 0;
		size_t cp_size = 0;
		int val;

		dst[0] = dst[1] = dst[2] = 0;

		while(errp->code == 0 && src_size > 0 && cp_size < 4)
		{
			if ((val = _getBase64IdxA(*src)) == -1) { /* ignore */ }
			else 
			{
				u32_t idx = (u32_t)cp_size++;
				if (val == -2) { }
				else _setOutputData(dst, val, idx, outsize);
			}
			src++;
			src_size--;
			consume++;
		}
		ret = consume;
	}
	return ret;
}

Dz1Binary *Dz1Base64_decA(str_t src, ssize_t src_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBuf *elb = NULL;
		if (src_len < 0) src_len = (ssize_t)strlen(src);

		if (src_len == 0) ERR_SET_OUT(errp, EINVAL);
		else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t dst[3];
			size_t written;
			ssize_t sz;
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
			while(errp->code == 0 && src_len > 0)
			{
				if ((sz = Dz1Base64_decBlockA(dst, 3, &written, src, src_len, errp)) < 0) ERR_OUT(errp);
				else if (_Dz1ElasticBuf_push(elb, dst, written, errp) == FALSE) ERR_OUT(errp);
				else
				{
					src += sz;
					src_len -= sz;
				}
			}

			if (errp->code == 0)
			{
				if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		}
	}
	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1Base64_decBlockW(u8_t *dst, size_t dst_sz, size_t *outsize, wchar_t *src, size_t src_size, Dz1Error *errp /*u8_t dst[3], size_t *outsize, wchar_t *src, size_t src_size, Dz1Error *errp*/)
{
	ssize_t ret = -1;

	if (src == NULL || dst == NULL || dst_sz < 3) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		ssize_t consume = 0;
		size_t cp_size = 0;
		int val;

		dst[0] = dst[1] = dst[2] = 0;

		while(errp->code == 0 && src_size > 0 && cp_size < 4)
		{
			if ((val = _getBase64IdxW(*src)) == -1) { /* ignore */ }
			else 
			{
				u32_t idx = (u32_t)cp_size++;
				if (val == -2) { }
				else _setOutputData(dst, val, idx, outsize);
			}
			src++;
			src_size--;
			consume++;
		}
		ret = consume;
	}
	return ret;
}

Dz1Binary *Dz1Base64_decW(wstr_t src, ssize_t src_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBuf *elb = NULL;
		if (src_len < 0) src_len = (ssize_t)wcslen(src);

		if (src_len == 0) ERR_SET_OUT(errp, EINVAL);
		else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t dst[3];
			size_t written;
			ssize_t sz;
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
			while(errp->code == 0 && src_len > 0)
			{
				if ((sz = Dz1Base64_decBlockW(dst, 3, &written, src, src_len, errp)) < 0) ERR_OUT(errp);
				else if (_Dz1ElasticBuf_push(elb, dst, written, errp) == FALSE) ERR_OUT(errp);
				else
				{
					src += sz;
					src_len -= sz;
				}
			}

			if (errp->code == 0)
			{
				if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		}
	}
	return ret;
}
#endif

ssize_t Dz1Base64_RawToB64(char *b64, size_t b64_sz, u8_t *raw, size_t raw_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	if (raw == NULL || raw_sz == 0 || b64 == NULL || b64_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t sz;
		char *dp = b64;
		u8_t *sp = raw;
		while(errp->code == 0 && b64_sz > 0 && raw_sz > 0)
		{
			if ((sz = Dz1Base64_encBlockA(dp, b64_sz, sp, raw_sz, errp)) < 0) ERR_OUT(errp);
			else
			{
				ret += 4;
				dp += 4;
				b64_sz -= 4;

				sp += sz;
				raw_sz -= sz;
			}
		}

		if (raw_sz > 0) ERR_SET_OUT(errp, E2BIG);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

ssize_t Dz1Base64_B64ToRaw(u8_t *raw, size_t raw_sz, char *b64, size_t b64_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	if (raw == NULL || raw_sz == 0 || b64 == NULL || b64_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t sz;
		size_t dp_consume = 0;
		u8_t *dp = raw;
		char *sp = b64;
		while(errp->code == 0 && b64_sz > 0 && raw_sz > 0)
		{
			if ((sz = Dz1Base64_decBlockA(dp, raw_sz, &dp_consume, sp, b64_sz, errp)) < 0) ERR_OUT(errp);
			else
			{
				ret += (ssize_t)dp_consume;
				dp += dp_consume;
				raw_sz -= dp_consume;

				sp += sz;
				b64_sz -= sz;
			}
		}

		if (b64_sz > 0) ERR_SET_OUT(errp, E2BIG);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

size_t Dz1Base64_getEncSize(size_t raw_size)
{
	size_t ret = 0;
	if (raw_size > 0)
	{
		u32_t blk_cnt = (u32_t)(raw_size / 3);
		u32_t mod_sz = raw_size % 3;
		ret = (blk_cnt + (mod_sz ? 1 : 0)) * 4;
	}
	return ret;
}

// size_t Dz1Codec_Base64DecLen(size_t size)
// {
// 	size_t ret = 0;
// 	if (size > 0)
// 	{
// 		u32_t blk_cnt = (u32_t)(size / 4);
// 		u32_t mod_sz = size % 4;
// 		ret = (blk_cnt + (mod_sz ? 1 : 0)) * 3;
// 	}
// 	return ret;
// }
