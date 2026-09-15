#include <dz1_malloc.h>
#include <dz1_codec_bin.h>

ssize_t Dz1Binary8_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst, _size;
		DZ1_ENCODE1(cp, size, (_size = (u8_t)src->size), errp, ret);
		DZ1_ENCODE(cp, size, src->data, (size_t)_size, errp, ret);
	}
	return ret;
}

ssize_t Dz1Binary16_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		u16_t _size;
		DZ1_ENCODE2(cp, size, (_size = (u16_t)src->size), errp, ret);
		DZ1_ENCODE(cp, size, src->data, (size_t)_size, errp, ret);
	}
	return ret;
}

ssize_t Dz1Binary_enc(u8_t *dst, size_t size, Dz1Binary *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (!src)
	{
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	}
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->size, errp, ret);
		DZ1_ENCODE(cp, size, src->data, src->size, errp, ret);
	}
	return ret;
}

ssize_t Dz1Binary8_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, _size;

		DZ1_DECODE1(&_size, cp, size, errp, ret);
		dst->size = (size_t)_size;

		if (dst->size > 0)
		{
			if ((dst->data = (u8_t *)Dz1Malloc(dst->size, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_DECODE(dst->data, dst->size, cp, size, errp, ret);
		}
	}
	return ret;
}

ssize_t Dz1Binary16_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t _size;

		DZ1_DECODE2(&_size, cp, size, errp, ret);
		dst->size = (size_t)_size;

		if (dst->size > 0)
		{
			if ((dst->data = (u8_t *)Dz1Malloc(dst->size, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_DECODE(dst->data, dst->size, cp, size, errp, ret);
		}
	}
	return ret;
}

ssize_t Dz1Binary_dec(Dz1Binary *dst, u8_t *src, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;

		DZ1_DECODE4(&dst->size, cp, size, errp, ret);

		if (dst->size > 0)
		{
			if ((dst->data = (u8_t *)Dz1Malloc(dst->size, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_DECODE(dst->data, dst->size, cp, size, errp, ret);
		}
	}
	return ret;
}
