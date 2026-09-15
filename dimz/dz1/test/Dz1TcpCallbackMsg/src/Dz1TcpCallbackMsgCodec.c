#include <dz1_codec.h>
#include <dz1_timeval.h>
#include "Dz1TcpCallbackMsgCodec.h"

// static void *Dz1TcpCallbackEcho_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpCallbackEcho *ret = Dz1TcpCallbackEcho_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpCallbackEcho_enc(u8_t *dst, size_t size, void *ptr, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	Dz1TcpCallbackEcho *src = (Dz1TcpCallbackEcho *)ptr;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->echoID, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1TimeVal_enc(cp, size, src->stamp, errp), errp);
	}
	return ret;
}

static ssize_t Dz1TcpCallbackEcho_dec(void *ptr, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	Dz1TcpCallbackEcho *dst = (Dz1TcpCallbackEcho *)ptr;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->echoID, cp, size, errp, ret);
		if ((dst->stamp = Dz1TimeVal_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_FUNC(cp, size, ret, Dz1TimeVal_dec(dst->stamp, cp, size, errp), errp);
	}
	return ret;
}

static Dz1CodecApiMap Dz1TcpCallbackMsgCodec[] =
{
	Dz1CodecApi_STRUCT(Dz1TcpCallbackMsg, 0x01, Dz1TcpCallbackEcho, echo),
	Dz1CodecApiMapEntry_last
};

// Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpCallbackMsg *ret = Dz1TcpCallbackMsg_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

#define MAGIC_NUMBER			0x94C87F4C
ssize_t Dz1TcpCallbackMsg_enc(u8_t *dst, size_t size, Dz1TcpCallbackMsg *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t status = 0, dumb = 0;
		u8_t *cp = dst, *lenPtr = NULL;
		size_t lenSize = sizeof(u32_t);
		DZ1_ENCODE4(cp, size, MAGIC_NUMBER, errp, ret);
		lenPtr = cp; DZ1_CODEC_APPLY(cp, size, sizeof(u32_t), ret);
		if ((status = Dz1UnionCodec_enc(cp, size, src, param, Dz1TcpCallbackMsgCodec, 1, TRUE, errp)) < 0) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, status, ret);
		DZ1_ENCODE4(lenPtr, lenSize, (u32_t)(status & 0xFFFFFFFF), errp, dumb);
	}
	return ret;
}

ssize_t Dz1TcpCallbackMsg_dec(Dz1TcpCallbackMsg *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t magic = 0, len = 0;
		u8_t *cp = src;
		DZ1_DECODE4(&magic, cp, size, errp, ret);
		if (magic != MAGIC_NUMBER) DZ1_CODEC_ERRSET_RET(errp, EFAULT);
		DZ1_DECODE4(&len, cp, size, errp, ret);
		if (size < len) DZ1_CODEC_ERRSET_RET(errp, E2BIG);
		else size = len;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_dec(dst, cp, size, param, Dz1TcpCallbackMsgCodec, 1, TRUE, errp), errp);
	}
	return ret;
}