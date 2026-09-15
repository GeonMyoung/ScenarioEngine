#include <dz1_codec.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include "Dz1TdcInfoPrimitive.h"

PrimitiveInfo *PrimitiveInfo_new(str_t native, NativeStorage storage, str_t prefix, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PrimitiveInfo *ret = (PrimitiveInfo *)Dz1Malloc(sizeof(PrimitiveInfo), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(PrimitiveInfo));
		pthread_cleanup_push(PrimitiveInfo_delAndSetNull, (void *)&ret);

		if (native && (ret->native = Dz1Str_dup(native, errp)) == NULL) { }
		else if (native && (ret->prefix = Dz1Str_dup(prefix ? prefix : native, errp)) == NULL) { }
		else
		{
			ret->storage = storage;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (PrimitiveInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PrimitiveInfo_del(PrimitiveInfo *p)
{
	if (!p) return;
	if (p->native) Dz1Free(p->native);
	if (p->prefix ) Dz1Free(p->prefix);
	Dz1Free(p);
}

void PrimitiveInfo_dump(PrimitiveInfo *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "native type %s %s(function prefix : %s)\n", NativeStorageStr(p->storage), p->native, p->prefix);
}

////////////////////////////////////////////////////////////////////////////////
// PrimitiveInfo CODEC
PrimitiveInfo *PrimitiveInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PrimitiveInfo *ret = PrimitiveInfo_new(NULL, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t PrimitiveInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PrimitiveInfo *src = (PrimitiveInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, src->native ? 1 : 0, errp, ret);
		if (src->native && strlen(src->native) > 0) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->native, errp), errp);

		DZ1_ENCODE4(cp, size, src->storage, errp, ret);

		DZ1_ENCODE1(cp, size, src->prefix ? 1 : 0, errp, ret);
		if (src->prefix && strlen(src->prefix) > 0) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->prefix, errp), errp);
	}
	return ret;
}

ssize_t PrimitiveInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PrimitiveInfo *dst = (PrimitiveInfo *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		u32_t v32;
		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->native, errp), errp);

		DZ1_DECODE4(&v32, cp, size, errp, ret); dst->storage = (NativeStorage)v32;

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->prefix, errp), errp);
	}
	return ret;
}
// PrimitiveInfo CODEC
////////////////////////////////////////////////////////////////////////////////

