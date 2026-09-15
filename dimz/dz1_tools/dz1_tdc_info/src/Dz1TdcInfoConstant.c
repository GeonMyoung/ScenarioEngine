#include <dz1_str.h>
#include <dz1_codec.h>
#include <Dz1TdcInfoConstant.h>

////////////////////////////////////////////////////////////////////////////////
// ConstantInfo API
ConstantInfo *ConstantInfo_new(str_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstantInfo *ret = (ConstantInfo *)Dz1Calloc(sizeof(ConstantInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ConstantInfo_delAndSetNull, (void *)&ret);

		if (0) { }
		else if (value != NULL && (ret->value = Dz1StrA_dup(value, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (ConstantInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

ConstantInfo *ConstantInfo_clone(ConstantInfo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstantInfo *ret = NULL;
	
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ConstantInfo_new(src->value, errp)) == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

void ConstantInfo_del(ConstantInfo *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1StrA_delAndSetNull(&p->value);
	Dz1Free(p);
}

void ConstantInfo_dump(ConstantInfo *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else Dz1Thread_printf("[%s]\n", p->value ? p->value : "(null)");
}
// ConstantInfo API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstantInfo CODEC
ConstantInfo *ConstantInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstantInfo *ret = ConstantInfo_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t ConstantInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstantInfo *src = (ConstantInfo *)_src;
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->value, errp), errp);
	}
	return ret;
}

ssize_t ConstantInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstantInfo *dst = (ConstantInfo *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->value, errp), errp);
	}
	return ret;
}
// ConstantInfo CODEC
////////////////////////////////////////////////////////////////////////////////

