#include <dz1_bmp.h>

static Dz1Error _Dz1BMP_fixup(Dz1BMP *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *ck = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->hdr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ck = dst->chunk) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (ck->size <= 40) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t *cp = (ck->data + 14);
		size_t size = sizeof(Dz1BMPDIB);
		memcpy(dst->hdr, cp, size); cp += size;
		dst->image = cp;
	}
	return err;
}

static __inline__ Dz1Error _Dz1BMP_fixdown(Dz1BMP *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *ck = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->hdr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ck = dst->chunk) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (ck->size <= 40) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t *cp = (ck->data + 14);
		size_t size = sizeof(Dz1BMPDIB);
		memcpy(cp, dst->hdr, size); cp += size;
	}
	return err;
}

// static Dz1BMPDIB *Dz1BMPDIB_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1BMPDIB *ret = Dz1BMPDIB_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

// Dz1BMP *Dz1BMP_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1BMP *ret = Dz1BMP_new(NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

Dz1BMP *Dz1BMP_clone(Dz1BMP *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = NULL;
	if (src == NULL || src->chunk == NULL || src->image == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1BMP_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&ret);
		if ((ret->chunk = Dz1Binary_clone(src->chunk, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->hdr = Dz1BMPDIB_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _Dz1BMP_fixup(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1BMP_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1BMP_copyImage(Dz1BMP *dst, Dz1BMP *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || dst->chunk == NULL || dst->image == NULL ||
		src == NULL || src->chunk == NULL || src->image == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1Binary *dst_chunk = dst->chunk;
		Dz1Binary *src_chunk = src->chunk;
		if (dst_chunk->size != src_chunk->size)
		{
			Dz1Binary_delAndSetNull(&dst->chunk);
			if ((dst->chunk = Dz1Binary_clone(src->chunk, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = _Dz1BMP_fixup(dst)).code) ERR_OUT(errp);
		}
		else
		{
			memcpy(dst_chunk->data, src_chunk->data, src_chunk->size);
			if ((*errp = _Dz1BMP_fixup(dst)).code) ERR_OUT(errp);
		}
	}
	return err;
}

Dz1Error Dz1BMP_setImagedata(Dz1BMP *dst, Dz1Binary *bits)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || bits == NULL || bits->data == NULL || bits->size == 0) ERR_SET_OUT(errp, EINVAL);
	else memcpy(dst->image, bits->data, bits->size);
	return err;
}

ssize_t Dz1BMP_read(Dz1BMP *dst, Dz1Stream *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u16_t marker;
		u32_t size;
		Dz1Binary *bin = NULL;
		DZ1_STREAM_READ2(&marker, src, Dz1IOStreamEndian_big, errp, ret);
		if (marker != 0x424d) ERR_SETOUT_RET(errp, EPERM, -1);

		DZ1_STREAM_READ4(&size, src, Dz1IOStreamEndian_little, errp, ret);

		if ((dst->chunk = bin = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, size, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			u32_t little_size = Dz1Endian4_host2little(size);
			u8_t *cp = bin->data;
			*cp++ = (u8_t)'B'; size--;
			*cp++ = (u8_t)'M'; size--;
			memcpy(cp, &little_size, sizeof(u32_t)); cp += sizeof(u32_t); size -= sizeof(u32_t);

			DZ1_STREAM_READ(cp, size, src, errp, ret);

			Dz1BMPDIB_delAndSetNull(&dst->hdr);
			if ((dst->hdr = Dz1BMPDIB_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else if ((*errp = _Dz1BMP_fixup(dst)).code) ERR_OUT_RET(errp, -1);
		}
	}
	return ret;
}

ssize_t Dz1BMP_dec(Dz1BMP *dst, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1Stream *ins = NULL;
		if ((ins = Dz1Stream_openStaticBuf(src, size, TRUE, size, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ins);

			if ((ret = Dz1BMP_read(dst, ins, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&ins);
		}		
	}
	return ret;
}

ssize_t Dz1BMP_write(Dz1Stream *dst, Dz1BMP *src, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1Binary *bin = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if ((bin = src->chunk) == NULL || bin->size == 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE(dst, bin->data, bin->size, errp, ret);
	}
	return ret;
}

ssize_t Dz1BMP_enc(u8_t *dst, size_t size, Dz1BMP *src, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1Binary *bin = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if ((bin = src->chunk) == NULL || bin->size == 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_ENCODE(dst, size, bin->data, bin->size, errp, ret);
	}
	return ret;
}

static Dz1BMP *_Dz1BMP_load(Dz1Binary **chunk, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = Dz1BMP_new(NULL, NULL, (*chunk), errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		(*chunk) = NULL;
		pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&ret);

		if ((ret->hdr = Dz1BMPDIB_new(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _Dz1BMP_fixup(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1BMP_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1BMP *Dz1BMPA_load(str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = NULL;
	Dz1Binary *chunk = Dz1BinFileA_load(fn, errp);
	if (chunk == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chunk);

		if ((ret = _Dz1BMP_load(&chunk, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chunk);
	}
	return ret;
}

Dz1BMP *Dz1BMPA_load2(str_t path, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = NULL;
	char fn[4096];
	if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1BMPA_load(fn, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

#ifdef WIN32
Dz1BMP *Dz1BMPW_load(wstr_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = NULL;
	Dz1Binary *chunk = Dz1BinFileW_load(fn, errp);
	if (chunk == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chunk);

		if ((ret = _Dz1BMP_load(&chunk, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chunk);
	}
	return ret;
}

Dz1BMP *Dz1BMPW_load2(wstr_t path, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1BMP *ret = NULL;
	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathName(Dz1ArrParam(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1BMPW_load(fn, errp)) == NULL) ERR_OUT(errp);
	return ret;
}
#endif
