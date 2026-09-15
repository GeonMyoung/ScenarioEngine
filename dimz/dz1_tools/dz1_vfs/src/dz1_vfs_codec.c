#include "dz1_codec.h"
#include "dz1_codec_bin.h"
#include "dz1_meta_tag_codec.h"
#include "dz1_vfs_codec.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsFile CODEC
Dz1VfsFile *Dz1VfsFile_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsFile *ret = Dz1VfsFile_new(DZ1_STORAGE_FRAG_IDX_NONE, Dz1MetaTagTargetType_unknown, DZ1_STORAGE_FRAG_IDX_NONE, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t Dz1VfsFile_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsFile *src = (Dz1VfsFile *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE2(cp, size, (u16_t)(src->body_type & 0xFFFF), errp, ret);
		DZ1_ENCODE4(cp, size, src->body_idx, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagData_enc(cp, size, src->tags, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1VfsFile_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsFile *dst = (Dz1VfsFile *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t v16;
		DZ1_DECODE2(&v16, cp, size, errp, ret); dst->body_type = (Dz1MetaTagTargetType)v16;
		DZ1_DECODE4(&dst->body_idx, cp, size, errp, ret);

		if ((dst->tags = Dz1MetaTagData_gen(errp)) == NULL) ERR_OUT(errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagData_dec(dst->tags, cp, size, param, errp), errp);
	}
	return ret;
}
// Dz1VfsFile CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsFile Convert Util
Dz1Binary *Dz1VfsFile_toStream(Dz1VfsFile *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		if ((sz = Dz1VfsFile_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1VfsFile_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1VfsFile *Dz1VfsFile_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1VfsFile *ret = Dz1VfsFile_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1VfsFile_delAndSetNull, (void *)&ret);
		if ((sz = Dz1VfsFile_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1VfsFile_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1VfsFile Convert Util
////////////////////////////////////////////////////////////////////////////////











////////////////////////////////////////////////////////////////////////////////
// Dz1VfsChildNode CODEC
static Dz1VfsChildNode *Dz1VfsChildNode_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildNode *ret = Dz1VfsChildNode_new(NULL, DZ1_STORAGE_FRAG_IDX_NONE, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t Dz1VfsChildNode_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildNode *src = (Dz1VfsChildNode *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_enc(cp, size, src->name, param, errp), errp);
		DZ1_ENCODE4(cp, size, src->idx, errp, ret);
	}
	return ret;
}

static ssize_t Dz1VfsChildNode_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildNode *dst = (Dz1VfsChildNode *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		if ((dst->name = Dz1Asn1UTF8Str_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1Asn1UTF8Str_dec(dst->name, cp, size, param, errp), errp);

		DZ1_DECODE4(&dst->idx, cp, size, errp, ret);
	}
	return ret;
}
// Dz1VfsChildNode CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsChildList CODEC
static Dz1VfsChildList *Dz1VfsChildList_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildList *ret = Dz1VfsChildList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _Dz1VfsChildList_enc(void *ptr, Dz1VfsChildNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = Dz1VfsChildNode_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t Dz1VfsChildList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildList *src = (Dz1VfsChildList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _Dz1VfsChildList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t Dz1VfsChildList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsChildList *dst = (Dz1VfsChildList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		Dz1VfsChildNode *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1VfsChildNode_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1VfsChildNode_delAndSetNull, (void *)&node);
				if ((status = Dz1VfsChildNode_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (Dz1VfsChildNode_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1VfsChildList CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsDir CODEC
Dz1VfsDir *Dz1VfsDir_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsDir *ret = Dz1VfsDir_new(DZ1_STORAGE_FRAG_IDX_NONE, DZ1_STORAGE_FRAG_IDX_NONE, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t Dz1VfsDir_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsDir *src = (Dz1VfsDir *)_src;
	if (src == NULL || src->tags == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->parent_idx, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagData_enc(cp, size, src->tags, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1VfsChildList_enc(cp, size, src->dirs, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1VfsChildList_enc(cp, size, src->files, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1VfsDir_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1VfsDir *dst = (Dz1VfsDir *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->parent_idx, cp, size, errp, ret);

		if ((dst->tags = Dz1MetaTagData_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1MetaTagData_dec(dst->tags, cp, size, param, errp), errp);

		DZ1_CODEC_FUNC(cp, size, ret, Dz1VfsChildList_dec(dst->dirs, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1VfsChildList_dec(dst->files, cp, size, param, errp), err);
	}
	return ret;
}
// Dz1VfsDir CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsDir Convert Util
Dz1Binary *Dz1VfsDir_toStream(Dz1VfsDir *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		if ((sz = Dz1VfsDir_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1VfsDir_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1VfsDir *Dz1VfsDir_toStruct(Dz1Binary *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1VfsDir *ret = Dz1VfsDir_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&ret);
		if ((sz = Dz1VfsDir_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1VfsDir_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1VfsDir Convert Util
////////////////////////////////////////////////////////////////////////////////
