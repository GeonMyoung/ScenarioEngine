#include <dz1_codec.h>

#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include <Dz1TdcInfoModule.h>
#include "Dz1TdcInfoObject.h"
#include "Dz1TdcInfoDefined.h"

DefinedInfo *DefinedInfo_new(int isForwarded, ObjectInfo *origin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	DefinedInfo *ret = (DefinedInfo *)Dz1Calloc(sizeof(DefinedInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->isForwarded = isForwarded;
		ret->origin = origin;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void DefinedInfo_del(DefinedInfo *p)
{
	if (!p) return;
	Dz1Free(p);
}

void DefinedInfo_dump(DefinedInfo *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "defined as %s\n", ObjectInfo_nameOf(p->origin));
}

///////////////////////////////////////////////////////////////////////////////
// DefinedInfo CODEC API
void *DefinedInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	DefinedInfo *ret = DefinedInfo_new(FALSE, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t DefinedInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	DefinedInfo *src = (DefinedInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->isForwarded, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->origin->name, errp), errp);
	}
	return ret;
}

ssize_t DefinedInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	DefinedInfo *dst = (DefinedInfo *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		str_t originName = NULL;
		u8_t *cp = src;
		DZ1_DECODE4((u32_t *)&dst->isForwarded, cp, size, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &originName, errp), errp);
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&originName);
		if ((dst->origin = module->findObject(module, originName)) == NULL)
		{
			if ((dst->origin = module->regUnknownObject(module, originName, errp)) == NULL) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&originName);
		if (errp->code) DZ1_CODEC_ERR_RET(errp);
	}
	return ret;
}
// DefinedInfo CODEC API
///////////////////////////////////////////////////////////////////////////////

