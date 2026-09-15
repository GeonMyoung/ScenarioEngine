#include <dz1_malloc.h>
#include "dz1_io_stream.h"
#include "dz1_io_stream_bin.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary CODEC
static ssize_t _Dz1Binary_write(Dz1Stream *dst, Dz1Binary *src, size_t len_size, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src->size > 0 && src->data == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1IoStream_isPossibleSize(len_size) == FALSE || len_size == 8) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		switch(len_size)
		{
		case 1:
			DZ1_STREAM_WRITE1(dst, (u8_t)(src->size & 0xFF), errp, ret);
			break;
		case 2:
			DZ1_STREAM_WRITE2(dst, (u16_t)(src->size & 0xFFFF), ed, errp, ret);
			break;
		case 4:
			DZ1_STREAM_WRITE4(dst, (u32_t)(src->size & 0xFFFFFFFF), ed, errp, ret);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}

		if (src->size > 0) DZ1_STREAM_WRITE(dst, src->data, src->size, errp, ret);
	}
	return ret;
}

static ssize_t _Dz1Binary_read(Dz1Binary *dst, size_t len_size, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL || (dst->size != 0 && dst->data != NULL))
	{
		ERR_SET_OUT_RET(errp, EINVAL, -1);
	}
	else if (Dz1IoStream_isPossibleSize(len_size) == FALSE) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t t8;
		u16_t t16;
		switch(len_size)
		{
		case 1:
			DZ1_STREAM_READ1(&t8, src, errp, ret); dst->size = (u32_t)t8;
			break;
		case 2:
			DZ1_STREAM_READ2(&t16, src, ed, errp, ret); dst->size = (u32_t)t16;
			break;
		case 4:
			DZ1_STREAM_READ4(&dst->size, src, ed, errp, ret);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
		if (dst->size)
		{
			if ((dst->data = (u8_t *)Dz1Malloc(dst->size, errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_STREAM_READ(dst->data, dst->size, src, errp, ret);
		}
	}
	return ret;
}
// Dz1Binary CODEC
////////////////////////////////////////////////////////////////////////////////


ssize_t Dz1Binary8_write(Dz1Stream *st, void *Dz1BinaryPtr, void *param, Dz1Error *err)
{
	return _Dz1Binary_write(st, (Dz1Binary *)Dz1BinaryPtr, 1, Dz1IOStreamEndian_big, err);
}
ssize_t Dz1Binary8_read(void *Dz1BinaryPtr, Dz1Stream *st, void *param, Dz1Error *err)
{
	return _Dz1Binary_read((Dz1Binary *)Dz1BinaryPtr, 1, st, Dz1IOStreamEndian_big, err);
}


ssize_t Dz1Binary16_write(Dz1Stream *st, void *Dz1BinaryPtr, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	return _Dz1Binary_write(st, (Dz1Binary *)Dz1BinaryPtr, 2, ed, err);
}
ssize_t Dz1Binary16_read(void *Dz1BinaryPtr, Dz1Stream *st, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	return _Dz1Binary_read((Dz1Binary *)Dz1BinaryPtr, 2, st, ed, err);
}


ssize_t Dz1Binary32_write(Dz1Stream *st, void *Dz1BinaryPtr, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	return _Dz1Binary_write(st, (Dz1Binary *)Dz1BinaryPtr, 4, ed, err);
}
ssize_t Dz1Binary32_read(void *Dz1BinaryPtr, Dz1Stream *st, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	return _Dz1Binary_read((Dz1Binary *)Dz1BinaryPtr, 4, st, ed, err);
}


