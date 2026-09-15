#include <dz1_codec.h>
#include <dz1_codec_bin.h>
#include "dz1_meta_tag_codec.h"
#include "dz1_meta_tag_util.h"

#define DZ1_META_TAG_SYSTEM_TARGET_MAX			0xFFFF
////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeEntry CODEC
// static Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTargetTypeEntry *ret = Dz1MetaTargetTypeEntry_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTargetTypeEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTargetTypeEntry *src = (Dz1MetaTargetTypeEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->type, errp, ret);

		if (src->name)
		{
			DZ1_ENCODE1(cp, size, 1, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_enc(cp, size, src->name, param, errp), errp);
		}
		else DZ1_ENCODE1(cp, size, 0, errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTargetTypeEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTargetTypeEntry *dst = (Dz1MetaTargetTypeEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE4(&dst->type, cp, size, errp, ret);

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v)
		{
			if ((dst->name = Dz1Asn1UTF8Str_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_dec(dst->name, cp, size, param, errp), errp);
		}
	}
	return ret;
}
// Dz1MetaTargetTypeEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeList CODEC
// static Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTargetTypeList *ret = Dz1MetaTargetTypeList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MetaTargetTypeList_enc(void *ptr, Dz1MetaTargetTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1MetaTargetTypeEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1MetaTargetTypeList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTargetTypeList *src = (Dz1MetaTargetTypeList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1MetaTargetTypeList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTargetTypeList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTargetTypeList *dst = (Dz1MetaTargetTypeList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1MetaTargetTypeEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MetaTargetTypeEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1MetaTargetTypeEntry_dec(node, cp, size, param, errp)) < 0)
				{
					ERR_OUT(errp); ret = -1;
				}
				else
				{
					if (node->type <= DZ1_META_TAG_SYSTEM_TARGET_MAX) dst->remove(dst, node);

					if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
					else
					{
						node = NULL;
						Dz1Error_set(errp, 0);
						DZ1_CODEC_APPLY(cp, size, status, ret);
					}
				}
				pthread_cleanup_pop(1); // (Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MetaTargetTypeList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValue CODEC
// Dz1MetaTagValue *Dz1MetaTagValue_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagValue *ret = Dz1MetaTagValue_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

// Union Member API Map ---------------------
static Dz1CodecApiMap Dz1MetaTagValueCodecMap[] = {
	Dz1CodecApi_VAR(Dz1MetaTagValue, Dz1MetaTagValuePresent_data8,  _dz1_u8,  data8),
	Dz1CodecApi_VAR(Dz1MetaTagValue, Dz1MetaTagValuePresent_data16, _dz1_u16, data16),
	Dz1CodecApi_VAR(Dz1MetaTagValue, Dz1MetaTagValuePresent_data32, _dz1_u32, data32),
	Dz1CodecApi_VAR(Dz1MetaTagValue, Dz1MetaTagValuePresent_data64, _dz1_u64, data64),
	Dz1CodecApi_STRUCT(Dz1MetaTagValue, Dz1MetaTagValuePresent_binary, Dz1Binary, binary),

//	Dz1CodecApi_VOID(Dz1MetaTagValue, __opcode__, __member_name__),
	Dz1CodecApiMapEntry_last
};

static ssize_t Dz1MetaTagValue_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagValue *src = (Dz1MetaTagValue *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec64_enc(cp, size, src, param, Dz1MetaTagValueCodecMap, 1, TRUE, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagValue_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagValue *dst = (Dz1MetaTagValue *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec64_dec(dst, cp, size, param, Dz1MetaTagValueCodecMap, 1, TRUE, errp), errp);
	}
	return ret;
}
// Dz1MetaTagValue CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValueList CODEC
// static Dz1MetaTagValueList *Dz1MetaTagValueList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagValueList *ret = Dz1MetaTagValueList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MetaTagValueList_enc(void *ptr, Dz1MetaTagValue *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1MetaTagValue_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1MetaTagValueList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagValueList *src = (Dz1MetaTagValueList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1MetaTagValueList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagValueList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagValueList *dst = (Dz1MetaTagValueList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1MetaTagValue *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MetaTagValue_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
				if ((status = Dz1MetaTagValue_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MetaTagValueList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataEntry CODEC
// static Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDataEntry *ret = Dz1MetaTagDataEntry_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDataEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDataEntry *src = (Dz1MetaTagDataEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->id, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagValueList_enc(cp, size, src->values, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDataEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDataEntry *dst = (Dz1MetaTagDataEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->id, cp, size, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagValueList_dec(dst->values, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1MetaTagDataEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataList CODEC
// Dz1MetaTagDataList *Dz1MetaTagDataList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDataList *ret = Dz1MetaTagDataList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MetaTagDataList_enc(void *ptr, Dz1MetaTagDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1MetaTagDataEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

ssize_t Dz1MetaTagDataList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDataList *src = (Dz1MetaTagDataList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1MetaTagDataList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

ssize_t Dz1MetaTagDataList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDataList *dst = (Dz1MetaTagDataList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1MetaTagDataEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MetaTagDataEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MetaTagDataEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1MetaTagDataEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (Dz1MetaTagDataEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MetaTagDataList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData CODEC
// Dz1MetaTagData *Dz1MetaTagData_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagData *ret = Dz1MetaTagData_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

ssize_t Dz1MetaTagData_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagData *src = (Dz1MetaTagData *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->target_type, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDataList_enc(cp, size, src->tags, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1MetaTagData_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagData *dst = (Dz1MetaTagData *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->target_type, cp, size, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDataList_dec(dst->tags, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1MetaTagData CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData Convert Utility
Dz1Binary *Dz1MetaTagData_toStream(Dz1MetaTagData *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagData_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = (u32_t)sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1MetaTagData_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MetaTagData *Dz1MetaTagData_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagData *ret = Dz1MetaTagData_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagData_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagData_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1MetaTagData Convert Utility
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaSingleTagEntry CODEC
// static Dz1MetaSingleTagEntry *Dz1MetaSingleTagEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagEntry *ret = Dz1MetaSingleTagEntry_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }
// 
// static ssize_t Dz1MetaSingleTagEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
// {
// 	ssize_t ret = 0;
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagEntry *src = (Dz1MetaSingleTagEntry *)_src;
// 	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
// 	else
// 	{
// 		u8_t *cp = dst;
// 		DZ1_ENCODE4(cp, size, src->id, errp, ret);
// 		if (src->value != NULL)
// 		{
// 			DZ1_ENCODE1(cp, size, 1, errp, ret);
// 			DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagValue_enc(cp, size, src->value, param, errp), errp);
// 		}
// 		else DZ1_ENCODE1(cp, size, 0, errp, ret);
// 	}
// 	return ret;
// }
// 
// static ssize_t Dz1MetaSingleTagEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
// {
// 	ssize_t ret = 0;
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagEntry *dst = (Dz1MetaSingleTagEntry *)_dst;
// 	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
// 	else
// 	{
// 		u8_t *cp = src, v;
// 
// 		DZ1_DECODE4(&dst->id, cp, size, errp, ret);
// 
// 		DZ1_DECODE1(&v, cp, size, errp, ret);
// 		if (v)
// 		{
// 			if ((dst->value = Dz1MetaTagValue_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
// 			else DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagValue_dec(dst->value, cp, size, param, errp), errp);
// 		}
// 	}
// 	return ret;
// }
// Dz1MetaSingleTagEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaSingleTagList CODEC
// static Dz1MetaSingleTagList *Dz1MetaSingleTagList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagList *ret = Dz1MetaSingleTagList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }
// 
// static Dz1Error _Dz1MetaSingleTagList_enc(void *ptr, Dz1MetaSingleTagEntry *p)
// {
// 	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
// 	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
// 	ssize_t status = Dz1MetaSingleTagEntry_enc(arg->cp, arg->size, p, arg->option, errp);
// 	if (status < 0) ERR_OUT(errp);
// 	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
// 	return err;
// }
// 
// ssize_t Dz1MetaSingleTagList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
// {
// 	ssize_t ret = 0;
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagList *src = (Dz1MetaSingleTagList *)_src;
// 	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
// 	else
// 	{
// 		u8_t *cp = dst;
// 		Dz1ListCodecArg arg;
// 		u16_t cnt = src->count(src);
// 		DZ1_ENCODE2(cp, size, cnt, errp, ret);
// 		Dz1ListCodecArg_init(&arg, cp, size, NULL);
// 		if ((*errp = src->travel(src, _Dz1MetaSingleTagList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
// 		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
// 	}
// 	return ret;
// }
// 
// ssize_t Dz1MetaSingleTagList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
// {
// 	ssize_t ret = 0;
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaSingleTagList *dst = (Dz1MetaSingleTagList *)_dst;
// 	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
// 	else
// 	{
// 		u8_t *cp = src;
// 		u16_t cnt, i;
// 		Dz1MetaSingleTagEntry *node = NULL;
// 		DZ1_DECODE2(&cnt, cp, size, errp, ret);
// 		for (i = 0; errp->code == 0 && i < cnt; i++)
// 		{
// 			if ((node = Dz1MetaSingleTagEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
// 			else
// 			{
// 				ssize_t status = 0;
// 				pthread_cleanup_push(Dz1MetaSingleTagEntry_delAndSetNull, (void *)&node);
// 				if ((status = Dz1MetaSingleTagEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
// 				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
// 				else
// 				{
// 					node = NULL;
// 					Dz1Error_set(errp, 0);
// 					DZ1_CODEC_APPLY(cp, size, status, ret);
// 				}
// 				pthread_cleanup_pop(1); // (Dz1MetaSingleTagEntry_delAndSetNull, (void *)&node);
// 			}
// 		}
// 	}
// 	return ret;
// }
// Dz1MetaSingleTagList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaSingleTagList Convert Util
// Dz1Binary *Dz1MetaSingleTagList_toStream(Dz1MetaSingleTagList *src, void *param, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		ssize_t sz = 0;
// 		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
// 		if ((sz = Dz1MetaSingleTagList_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
// 		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
// 		else if ((sz = Dz1MetaSingleTagList_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
// 		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }
// 
// Dz1MetaSingleTagList *Dz1MetaSingleTagList_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1MetaSingleTagList *ret = Dz1MetaSingleTagList_gen(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		ssize_t sz = 0;
// 		pthread_cleanup_push(Dz1MetaSingleTagList_delAndSetNull, (void *)&ret);
// 		if ((sz = Dz1MetaSingleTagList_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
// 		else
// 		{
// 			Dz1Error_set(errp, 0);
// 		}
// 		pthread_cleanup_pop(errp->code); // (Dz1MetaSingleTagList_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }
// Dz1MetaSingleTagList Convert Util
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrNumber CODEC
// static Dz1MetaTagDescrNumber *Dz1MetaTagDescrNumber_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrNumber *ret = Dz1MetaTagDescrNumber_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrNumber_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrNumber *src = (Dz1MetaTagDescrNumber *)_src;
	if (src == NULL)
	{
		DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	}
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, (u8_t)(src->type & 0xFF), errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrNumber_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrNumber *dst = (Dz1MetaTagDescrNumber *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->type = (Dz1MetaTagDescrNum)v;
	}
	return ret;
}
// Dz1MetaTagDescrNumber CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrFloat CODEC
// static Dz1MetaTagDescrFloat *Dz1MetaTagDescrFloat_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrFloat *ret = Dz1MetaTagDescrFloat_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrFloat_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrFloat *src = (Dz1MetaTagDescrFloat *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, (u32_t)src->precision, errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrFloat_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrFloat *dst = (Dz1MetaTagDescrFloat *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4((u32_t *)&dst->precision, cp, size, errp, ret);
	}
	return ret;
}
// Dz1MetaTagDescrFloat CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrGrade CODEC
// static Dz1MetaTagDescrGrade *Dz1MetaTagDescrGrade_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrGrade *ret = Dz1MetaTagDescrGrade_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrGrade_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrGrade *src = (Dz1MetaTagDescrGrade *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->max_grade, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_enc(cp, size, src->grade_unit, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrGrade_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrGrade *dst = (Dz1MetaTagDescrGrade *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->max_grade, cp, size, errp, ret);
		if ((dst->grade_unit = Dz1Asn1UTF8Str_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_dec(dst->grade_unit, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1MetaTagDescrGrade CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrString CODEC
// static Dz1MetaTagDescrString *Dz1MetaTagDescrString_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrString *ret = Dz1MetaTagDescrString_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrString_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrString *src = (Dz1MetaTagDescrString *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->charset, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrString_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrString *dst = (Dz1MetaTagDescrString *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->charset, errp), errp);
	}
	return ret;
}
// Dz1MetaTagDescrString CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumEntry CODEC
// static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrEnumEntry *ret = Dz1MetaTagDescrEnumEntry_new(-1, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrEnumEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnumEntry *src = (Dz1MetaTagDescrEnumEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->value, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_enc(cp, size, src->string, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrEnumEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnumEntry *dst = (Dz1MetaTagDescrEnumEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->value, cp, size, errp, ret);
		if ((dst->string = Dz1Asn1UTF8Str_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_dec(dst->string, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1MetaTagDescrEnumEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumList CODEC
// static Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrEnumList *ret = Dz1MetaTagDescrEnumList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MetaTagDescrEnumList_enc(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1MetaTagDescrEnumEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1MetaTagDescrEnumList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnumList *src = (Dz1MetaTagDescrEnumList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1MetaTagDescrEnumList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrEnumList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnumList *dst = (Dz1MetaTagDescrEnumList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1MetaTagDescrEnumEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MetaTagDescrEnumEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1MetaTagDescrEnumEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MetaTagDescrEnumList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnums CODEC
// static Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrEnums *ret = Dz1MetaTagDescrEnums_create(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrEnums_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnums *src = (Dz1MetaTagDescrEnums *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescrEnumList_enc(cp, size, src->values, param, errp), errp);
	}
	return ret;
}

static Dz1Error _enums_index_build(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEnumTable *dst = (Dz1MetaTagDescrEnumTable *)ptr;
	if ((*errp = dst->add(dst, (Dz1MetaTagDescrEnumIndex *)p)).code) ERR_OUT(errp);
	return err;
}

static ssize_t Dz1MetaTagDescrEnums_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEnums *dst = (Dz1MetaTagDescrEnums *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescrEnumList_dec(dst->values, cp, size, param, errp), errp);
		if ((*errp = dst->values->travel(dst->values, _enums_index_build, (void *)dst->strings)).code) DZ1_CODEC_ERR_RET(errp);
	}
	return ret;
}
// Dz1MetaTagDescrEnums CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrDate CODEC
// static Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrDate *ret = Dz1MetaTagDescrDate_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrDate_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrDate *src = (Dz1MetaTagDescrDate *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, (u8_t)(src->date8 & 0xFF), errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrDate_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrDate *dst = (Dz1MetaTagDescrDate *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->date8 = (Dz1MetaTagDescrDate8Mode)v;
	}
	return ret;
}
// Dz1MetaTagDescrDate CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrAlias CODEC
// static Dz1MetaTagDescrAlias *Dz1MetaTagDescrAlias_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrAlias *ret = Dz1MetaTagDescrAlias_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrAlias_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrAlias *src = (Dz1MetaTagDescrAlias *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->origin_descr_id, errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrAlias_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrAlias *dst = (Dz1MetaTagDescrAlias *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->origin_descr_id, cp, size, errp, ret);
	}
	return ret;
}
// Dz1MetaTagDescrAlias CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptorUser CODEC
// static Dz1MetaTagDescriptorUser *Dz1MetaTagDescriptorUser_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescriptorUser *ret = Dz1MetaTagDescriptorUser_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescriptorUser_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescriptorUser *src = (Dz1MetaTagDescriptorUser *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->userHandlingType, errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescriptorUser_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescriptorUser *dst = (Dz1MetaTagDescriptorUser *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->userHandlingType, cp, size, errp, ret);
	}
	return ret;
}
// Dz1MetaTagDescriptorUser CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptor CODEC
// static Dz1MetaTagDescriptor *Dz1MetaTagDescriptor_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescriptor *ret = Dz1MetaTagDescriptor_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

// Union Member API Map ---------------------
static Dz1CodecApiMap Dz1MetaTagDescriptorCodecMap[] = {
	Dz1CodecApi_VOID	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_no_data,									 no_data),
	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_number,		 Dz1MetaTagDescrNumber,		 number),
	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_floating,	 Dz1MetaTagDescrNumber,		 floating),

	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_grade,		 Dz1MetaTagDescrGrade,		 grade),
	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_enumerate,	 Dz1MetaTagDescrEnums,		 enumerate),

	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_string,		 Dz1MetaTagDescrString,		 string),
	Dz1CodecApi_VOID	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_web_url,									 web_url),

	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_date,		 Dz1MetaTagDescrDate,		 date),
	Dz1CodecApi_VOID	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_tim,										 tim),
	Dz1CodecApi_VOID	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_date_time,								 date_time),

	Dz1CodecApi_VOID	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_binary,									 binary),
	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_user,		 Dz1MetaTagDescriptorUser,	 user),

	Dz1CodecApi_STRUCT	(Dz1MetaTagDescriptor, Dz1MetaTagDescriptorPresent_alias,		 Dz1MetaTagDescrAlias, alias),

	Dz1CodecApiMapEntry_last
};

static ssize_t Dz1MetaTagDescriptor_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescriptor *src = (Dz1MetaTagDescriptor *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_enc(cp, size, src, param, Dz1MetaTagDescriptorCodecMap, 1, TRUE, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescriptor_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescriptor *dst = (Dz1MetaTagDescriptor *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_dec(dst, cp, size, param, Dz1MetaTagDescriptorCodecMap, 1, TRUE, errp), errp);
	}
	return ret;
}
// Dz1MetaTagDescriptor CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagRestrict CODEC
// static Dz1MetaTagRestrict *Dz1MetaTagRestrict_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagRestrict *ret = Dz1MetaTagRestrict_new(0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagRestrict_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagRestrict *src = (Dz1MetaTagRestrict *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, (u8_t)(src->mode& 0xFF), errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTargetTypeList_enc(cp, size, src->list, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagRestrict_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagRestrict *dst = (Dz1MetaTagRestrict *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->mode = (Dz1MetaTagRestrictMode)v;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTargetTypeList_dec(dst->list, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1MetaTagRestrict CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry CODEC
// static Dz1MetaTagDescrEntry *Dz1MetaTagDescrEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrEntry *ret = Dz1MetaTagDescrEntry_new(0, NULL, NULL, FALSE, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDescrEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEntry *src = (Dz1MetaTagDescrEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->id, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_enc(cp, size, src->name, param, errp), errp);

		if (src->status != NULL)
		{
			DZ1_ENCODE1(cp, size, 1, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagRestrict_enc(cp, size, src->status, param, errp), errp);
		}
		else DZ1_ENCODE1(cp, size, 0, errp, ret);

		if (src->descr != NULL)
		{
			DZ1_ENCODE1(cp, size, 1, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescriptor_enc(cp, size, src->descr, param, errp), errp);
		}
		else DZ1_ENCODE1(cp, size, 0, errp, ret);

		DZ1_ENCODE1(cp, size, (u8_t)(src->mode & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, src->mandatory ? 1 : 0, errp, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDescrEntry *dst = (Dz1MetaTagDescrEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;

		DZ1_DECODE4(&dst->id, cp, size, errp, ret);

		if ((dst->name = Dz1Asn1UTF8Str_new(NULL, 0, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_dec(dst->name, cp, size, param, errp), errp);

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v)
		{
			if ((dst->status = Dz1MetaTagRestrict_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagRestrict_dec(dst->status, cp, size, param, errp), errp);
		}
		
		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v)
		{
			if ((dst->descr = Dz1MetaTagDescriptor_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescriptor_dec(dst->descr, cp, size, param, errp), errp);
		}

		DZ1_DECODE1(&v, cp, size, errp, ret); dst->mode = (Dz1MetaTagDataMode)v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->mandatory = v ? TRUE : FALSE;
	}
	return ret;
}
// Dz1MetaTagDescrEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList CODEC
#define DZ1_META_TAG_SYSTEM_DESCR_MAX			0xFFFF
// static Dz1MetaTagDescrList *Dz1MetaTagDescrList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDescrList *ret = Dz1MetaTagDescrList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MetaTagDescrList_enc(void *ptr, Dz1MetaTagDescrEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1MetaTagDescrEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1MetaTagDescrList_enc(u8_t *dst, size_t size, Dz1MetaTagDescrList *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1MetaTagDescrList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t Dz1MetaTagDescrList_dec(Dz1MetaTagDescrList *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1MetaTagDescrEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MetaTagDescrEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1MetaTagDescrEntry_dec(node, cp, size, param, errp)) < 0)
				{
					ERR_OUT(errp); ret = -1;
				}
				else
				{
					if (node->id <= DZ1_META_TAG_SYSTEM_DESCR_MAX) dst->remove(dst, node);

					if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
					else
					{
						node = NULL;
						Dz1Error_set(errp, 0);
						DZ1_CODEC_APPLY(cp, size, status, ret);
					}
				}
				pthread_cleanup_pop(1); // (Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MetaTagDescrList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList Convert Util
Dz1Binary *Dz1MetaTagDescrList_toStream(Dz1MetaTagDescrList *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagDescrList_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = (u32_t)sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1MetaTagDescrList_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MetaTagDescrList *Dz1MetaTagDescrList_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDescrList *ret = Dz1MetaTagDescrList_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1MetaTagDescrList_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagDescrList_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescrList_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1MetaTagDescrList Convert Util
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB CODEC
// static Dz1MetaTagDB *Dz1MetaTagDB_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MetaTagDB *ret = Dz1MetaTagDB_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MetaTagDB_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDB *src = (Dz1MetaTagDB *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTargetTypeList_enc(cp, size, src->types, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescrList_enc(cp, size, src->table, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MetaTagDB_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MetaTagDB *dst = (Dz1MetaTagDB *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		Dz1MetaTargetTypeEntry *chk = NULL;
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTargetTypeList_dec(dst->types, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagDescrList_dec(dst->table, cp, size, param, errp), errp);

		if ((chk = Dz1MetaTagDB_getTargetType(dst, 0)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
		else if ((*errp = Dz1MetaTargetTypeEntry_mkNameW(chk)).code) ERR_OUT_RET(errp, -1);
		else if (wcscmp(chk->name_w, L"Unknown") != 0) ERR_SET_OUT_RET(errp, EFAULT, -1);
	}
	return ret;
}
// Dz1MetaTagDB CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB Convert Utility
Dz1Binary *Dz1MetaTagDB_toStream(Dz1MetaTagDB *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagDB_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = (u32_t)sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1MetaTagDB_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MetaTagDB *Dz1MetaTagDB_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDB *ret = Dz1MetaTagDB_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MetaTagDB_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1MetaTagDB Convert Utility
////////////////////////////////////////////////////////////////////////////////

