#include <dz1_time.h>
#include "dz1_web_socket_frame.h"

///////////////////////////////////////////////////////////////////////////////
// WebSocket Frame API
static bool_t _build_mask(u8_t dst[4])
{
	int cnt = 4;
	u8_t *dp = dst, temp;
	s32_t mask_int;
	while(cnt > 0)
	{
		if ((temp = (u8_t)((mask_int = rand()) & 0xFF)) > 0)
		{
			*dp++ = temp;
			cnt--;
		}
	}
	return TRUE;
}

static size_t _calc_frame_size(bool_t masking, u64_t data_len)
{
	size_t ret = 1 + 1;							// FIN + OP + MASK + LEN0
	if (0) { }
	else if (data_len >= 0xFFFF)	ret += 8;	// EXT_LEN(8)
	else if (data_len >= 126)		ret += 2;	// EXT_LEN(2)
	if (masking)					ret += 4;	// MASK(4)
	ret += data_len;							// DATA
	return ret;
}

static size_t _encode_mask_length(u8_t *dp, bool_t mask_flag, u64_t data_len)
{
	size_t ret = 0;
	u8_t mask = mask_flag ? 0x80 : 0x00;
	if (0) { }
	else if (data_len >= 0xFFFF)
	{
		*dp++ = mask | 0x7F;					ret++;	// MASK + LEN_TYPE(big)
		*dp++ = (u8_t)((data_len >> 56) & 0xFF);	ret++;	// LEN 0
		*dp++ = (u8_t)((data_len >> 48) & 0xFF);	ret++;	// LEN 1
		*dp++ = (u8_t)((data_len >> 40) & 0xFF);	ret++;	// LEN 2
		*dp++ = (u8_t)((data_len >> 32) & 0xFF);	ret++;	// LEN 3
		*dp++ = (u8_t)((data_len >> 24) & 0xFF);	ret++;	// LEN 4
		*dp++ = (u8_t)((data_len >> 16) & 0xFF);	ret++;	// LEN 5
		*dp++ = (u8_t)((data_len >> 8) & 0xFF);		ret++;	// LEN 6
		*dp++ = (u8_t)((data_len >> 0) & 0xFF);		ret++;	// LEN 7
		// total 9 byte
	}
	else if (data_len >= 126)
	{
		*dp++ = mask | 0x7E;					ret++;	// MASK + LEN_TYPE(small)
		*dp++ = (u8_t)((data_len >> 8) & 0xFF);		ret++;	// LEN 0
		*dp++ = (u8_t)((data_len >> 0) & 0xFF);		ret++;	// LEN 1
		// total 3 byte
	}
	else
	{
		*dp++ = mask | (u8_t)(data_len & 0x7F);		ret++;	// MASK + LEN
		// total 1 byte
	}
	return ret;
}

static bool_t _encode_frame(Dz1Binary *ret, Dz1WebSockOpCode op_code, bool_t masking, u8_t *data, u64_t size, Dz1Error *errp)
{
	u8_t mask[4] = { 0, 0, 0, 0 };
	if (0) { }
	else if (masking && _build_mask(mask) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u32_t log_lv = 0;

		int idx = 0;
		size_t sz = 0;
		u8_t *sp = data;
		u64_t spsz = size;

		u8_t *dp = ret->data;

		u8_t *data_ptr = NULL;

		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);

		*dp++ = (0x80 | (u8_t)(op_code & 0x0F));			// FIN, OPCODE	1
		sz = _encode_mask_length(dp, TRUE, size); dp += sz;	// MASK, LEN	(1 | 5 | 9)

		if (masking)
		{
			*dp++ = mask[0];
			*dp++ = mask[1];
			*dp++ = mask[2];
			*dp++ = mask[3];
		}													// 4

		data_ptr = dp;
		while(spsz)
		{
			*dp++ = *sp++ ^ mask[idx++];
			idx &= 0x3;
			spsz--;
		}
		*dp = 0;

		/*
		if (log_lv & DZ1_THREAD_LOG_DEBUG)
		{
			u8_t *unmasked = Dz1Malloc((u32_t)size, errp);
			if (unmasked == NULL) ERR_OUT(errp);
			else
			{
				u8_t *xp = unmasked, *qp = data_ptr;
				u64_t xpsz = size;
				int _idx = 0;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)unmasked);

				while(xpsz)
				{
					*xp++ = *qp++ ^ mask[_idx++];
					_idx &= 0x3;
					xpsz--;
				}
				_Dz1Thread_log("@@@ Unmasked Data\n");
				Dz1Thread_tprintb(1, unmasked, size, 16, FALSE);

				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)unmasked);
			}
			Dz1Error_set(errp, 0);
		}
		*/
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _is_correct_op(Dz1WebSockOpCode op)
{
	switch(op)
	{
	case Dz1WebSockOpCode_text:
	case Dz1WebSockOpCode_binary:
	case Dz1WebSockOpCode_terminate:
	case Dz1WebSockOpCode_ping:
	case Dz1WebSockOpCode_pong:
		return TRUE;
	default: return FALSE;
	}
}

static Dz1Binary *_mk_frame(Dz1WebSockOpCode op, bool_t masking, u8_t *data, u64_t size, Dz1Error *errp)
{
	size_t frame_size = 0;
	Dz1Binary *ret = NULL;
	if (_is_correct_op(op) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if ((frame_size = _calc_frame_size(masking, size)) == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		ret->size = (u32_t)(frame_size & 0xFFFF);
		if (0) { }
		else if ((ret->data = (u8_t *)Dz1Malloc(frame_size + 1, errp)) == NULL) ERR_OUT(errp);
		else if (_encode_frame(ret, op, masking, data, size, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Binary *Dz1WebSocket_binFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	if ((ret = _mk_frame(Dz1WebSockOpCode_binary, masking, data, size, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1Binary *Dz1WebSocket_textFrame(Dz1Asn1UTF8Str *str, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t *data = NULL;
	u64_t data_len = 0;
	Dz1Binary *ret = NULL;
	if (str != NULL)
	{
		data = str->data;
		data_len = (u64_t)str->size;
	}

	if ((ret = _mk_frame(Dz1WebSockOpCode_text, masking, data, data_len, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

Dz1Binary *Dz1WebSocket_pingFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;

	if ((ret = _mk_frame(Dz1WebSockOpCode_ping, masking, data, (u64_t)size, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

Dz1Binary *Dz1WebSocket_pongFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;

	if ((ret = _mk_frame(Dz1WebSockOpCode_pong, masking, data, (u64_t)size, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1Binary *_generate_close_info(Dz1WebSocketCloseReason reason, Dz1Asn1UTF8Str *opt_debug_info, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;

	size_t sz = 2;
	u16_t code = (u16_t)(reason & 0xFFFF);

	if (opt_debug_info != NULL && opt_debug_info->data != NULL && opt_debug_info->size > 0)
		sz += opt_debug_info->size;
		
	if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)sz, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t *dp = ret->data;
		*dp++ = (u8_t)((code >> 8) & 0xFF);
		*dp++ = (u8_t)((code >> 0) & 0xFF);
		if (sz > 2) memcpy(dp, opt_debug_info->data, opt_debug_info->size);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Binary *Dz1WebSocket_closeFrame(Dz1WebSocketCloseReason reason, Dz1Asn1UTF8Str *opt_debug_info, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	Dz1Binary *payload = _generate_close_info(reason, opt_debug_info, errp);
	if (payload == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&payload);
		if ((ret = _mk_frame(Dz1WebSockOpCode_terminate, masking, payload->data, (u64_t)payload->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&payload);
	}
	return ret;
}
// WebSocket Frame API
///////////////////////////////////////////////////////////////////////////////


