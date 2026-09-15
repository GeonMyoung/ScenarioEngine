#include <dz1_codec.h>
#include <dz1_codec_bin.h>
#include "Dz1TcpSerialMsgCodec.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1TcpSerialMsgOpen CODEC API
// static void *Dz1TcpSerialMsgOpen_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsgOpen *ret = Dz1TcpSerialMsgOpen_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpSerialMsgOpen_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgOpen *src = (Dz1TcpSerialMsgOpen *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->port, errp, ret);
		DZ1_ENCODE4(cp, size, src->baud, errp, ret);

		DZ1_ENCODE1(cp, size, (u8_t)(src->parity & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->stopBit & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->fullDuplex & 0xFF), errp, ret);

		DZ1_ENCODE1(cp, size, (u8_t)(src->flowRTSCTS & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->flowDSRDTR & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->flowXONXOFF & 0xFF), errp, ret);

		DZ1_ENCODE1(cp, size, (u8_t)(src->useRingInd & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->useCtsChanged & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->useDsrChanged & 0xFF), errp, ret);
	}
	return ret;
}

static ssize_t Dz1TcpSerialMsgOpen_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgOpen *dst = (Dz1TcpSerialMsgOpen *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE4(&dst->port, cp, size, errp, ret);
		DZ1_DECODE4(&dst->baud, cp, size, errp, ret);

		DZ1_DECODE1(&v, cp, size, errp, ret); dst->parity = (Dz1SerialParity)v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->stopBit = (Dz1SerialStopBit)v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->fullDuplex = v ? TRUE : FALSE;

		DZ1_DECODE1(&v, cp, size, errp, ret); dst->flowRTSCTS = (Dz1SerialRTSCTS)v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->flowDSRDTR = (Dz1SerialDSRDTR)v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->flowXONXOFF = (Dz1SerialXONXOFF)v;

		DZ1_DECODE1(&v, cp, size, errp, ret); dst->useRingInd = v ? TRUE : FALSE;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->useCtsChanged  = v ? TRUE : FALSE;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->useDsrChanged = v ? TRUE : FALSE;
	}
	return ret;
}
// Dz1TcpSerialMsgOpen CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TcpSerialMsgReply CODEC API
// static void *Dz1TcpSerialMsgReply_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsgReply *ret = Dz1TcpSerialMsgReply_new(0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpSerialMsgReply_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgReply *src = (Dz1TcpSerialMsgReply *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->port, errp, ret);
		DZ1_ENCODE4(cp, size, src->status, errp, ret);
	}
	return ret;
}

static ssize_t Dz1TcpSerialMsgReply_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgReply *dst = (Dz1TcpSerialMsgReply *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->port, cp, size, errp, ret);
		DZ1_DECODE4(&dst->status, cp, size, errp, ret);
	}
	return ret;
}
// Dz1TcpSerialMsgReply CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// s32_t CODEC API
static ssize_t s32_t_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	s32_t src = *(s32_t *)_src;
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src, errp, ret);
	}
	return ret;
}

static ssize_t s32_t_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	s32_t *dst = (s32_t *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(dst, cp, size, errp, ret);
	}
	return ret;
}
// s32_t CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TcpSerialMsgStream CODEC API
// static void *Dz1TcpSerialMsgStream_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsgStream *ret = Dz1TcpSerialMsgStream_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpSerialMsgStream_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgStream *src = (Dz1TcpSerialMsgStream *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->port, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Binary16_enc(cp, size, src->stream, NULL, errp), errp);
	}
	return ret;
}

static ssize_t Dz1TcpSerialMsgStream_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgStream *dst = (Dz1TcpSerialMsgStream *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(&dst->port, cp, size, errp, ret);
		if ((dst->stream = Dz1Binary_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		DZ1_CODEC_FUNC(cp, size, ret, Dz1Binary16_dec(dst->stream, cp, size, NULL, errp), errp);
	}
	return ret;
}
// Dz1TcpSerialMsgStream CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TcpSerialMsgPin CODEC API
// static void *Dz1TcpSerialMsgPin_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsgPin *ret = Dz1TcpSerialMsgPin_new(0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpSerialMsgPin_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgPin *src = (Dz1TcpSerialMsgPin *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->port, errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->v & 0xFF), errp, ret);
	}
	return ret;
}

static ssize_t Dz1TcpSerialMsgPin_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgPin *dst = (Dz1TcpSerialMsgPin *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE4(&dst->port, cp, size, errp, ret);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->v = (Dz1SerialPinState)v;
	}
	return ret;
}
// Dz1TcpSerialMsgPin CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TcpSerialMsgPinResult CODEC API
// static void *Dz1TcpSerialMsgPinResult_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsgPinResult *ret = Dz1TcpSerialMsgPinResult_new(0, 0, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1TcpSerialMsgPinResult_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgPinResult *src = (Dz1TcpSerialMsgPinResult *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, src->port, errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->v & 0xFF), errp, ret);
		DZ1_ENCODE4(cp, size, src->status, errp, ret);
	}
	return ret;
}

static ssize_t Dz1TcpSerialMsgPinResult_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialMsgPinResult *dst = (Dz1TcpSerialMsgPinResult *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE4(&dst->port, cp, size, errp, ret);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->v = (Dz1SerialPinState)v;
		DZ1_DECODE4(&dst->status, cp, size, errp, ret);
	}
	return ret;
}
// Dz1TcpSerialMsgPinResult CODEC API
///////////////////////////////////////////////////////////////////////////////

/*
typedef struct Dz1CodecApiMap
{
	int present;
	u32_t opcode;
	void *(*gen)(Dz1Error *errp);
	ssize_t (*enc)(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
	ssize_t (*dec)(void *_dst, u8_t *dst, size_t size, void *param, Dz1Error *err);
} Dz1CodecApiMap;
*/

static Dz1CodecApiMap _table[] = {
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0000, Dz1TcpSerialMsgOpen,		openPortReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0001, Dz1TcpSerialMsgReply,		openPortRsp),
	Dz1CodecApi_VAR		(Dz1TcpSerialMsg, 0x0002, s32_t,					closePortReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0003, Dz1TcpSerialMsgReply,		closePortRsp),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0004, Dz1TcpSerialMsgStream,	writePortReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0005, Dz1TcpSerialMsgReply,		writePortRsp),
	Dz1CodecApi_VAR		(Dz1TcpSerialMsg, 0x0006, s32_t,					writeDoneReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0007, Dz1TcpSerialMsgReply,		writeDoneRsp),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0008, Dz1TcpSerialMsgPin,		setRTSReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0009, Dz1TcpSerialMsgReply,		setRTSRsp),
	Dz1CodecApi_VAR		(Dz1TcpSerialMsg, 0x000A, s32_t,					getCTSReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x000B, Dz1TcpSerialMsgPinResult,	getCTSRsp),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x000C, Dz1TcpSerialMsgPin,		setDTRReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x000D, Dz1TcpSerialMsgReply,		setDTRRsp),
	Dz1CodecApi_VAR		(Dz1TcpSerialMsg, 0x000E, s32_t,					getDSRReq),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x000F, Dz1TcpSerialMsgPinResult,	getDSRRsp),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0010, Dz1TcpSerialMsgStream,	received),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0011, Dz1TcpSerialMsgPin,		ringIndicated),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0012, Dz1TcpSerialMsgPin,		ctsChanged),
	Dz1CodecApi_STRUCT	(Dz1TcpSerialMsg, 0x0013, Dz1TcpSerialMsgPin,		dsrChanged),
	Dz1CodecApiMapEntry_last
};

// Dz1TcpSerialMsg *Dz1TcpSerialMsg_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1TcpSerialMsg *ret = Dz1TcpSerialMsg_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

ssize_t Dz1TcpSerialMsg_enc(u8_t *dst, size_t size, Dz1TcpSerialMsg *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_enc(dst, size, (void *)src, param, _table, 2, TRUE, errp), errp);
	}
	return ret;
}

ssize_t Dz1TcpSerialMsg_dec(Dz1TcpSerialMsg *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_dec((void *)dst, src, size, param, _table, 2, TRUE, errp), errp);
	}
	return ret;
}
