#include <dz1_stdio.h>
#include <dz1_malloc.h>
#include "dz1_asn1_codec_stream.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Stream API
Dz1Asn1Stream *Dz1Asn1Stream_new(u32_t frag_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Stream *ret = NULL;
	
	if (frag_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1Stream *)Dz1Calloc(sizeof(Dz1Asn1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Stream_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else if ((ret->elb = Dz1ElasticBuf_new(frag_size, FALSE, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1Stream_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1Stream_del(Dz1Asn1Stream *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1ElasticBuf_delAndSetNull(&p->elb);
	Dz1Free(p);
}
// Dz1Asn1Stream API
////////////////////////////////////////////////////////////////////////////////

#define QUEUE_OCTET_SIZE	sizeof(DZ1_ASN1_STREAM_QUEUE_TYPE)
#define QUEUE_BITS_SIZE		(QUEUE_OCTET_SIZE << 3)

#define OCTET_BYTE_SIZE		sizeof(u8_t)
#define OCTET_BITS_SIZE		(OCTET_BYTE_SIZE << 3)

static ssize_t _get_octet(DZ1_ASN1_STREAM_QUEUE_TYPE *dst, u8_t *bits, s32_t cur_pos, s32_t take_len, s32_t bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (bits_len <= (cur_pos + take_len)) take_len = bits_len - cur_pos;

		if (take_len == 0) Dz1Error_set(errp, EAGAIN);	// 작업할께 없다.
		else
		{
			ssize_t sz = 0;
			DZ1_ASN1_STREAM_QUEUE_TYPE mask;
			s32_t idx, shf, avl_len, work_len;

			(*dst) = 0;
			while(take_len)
			{
				idx = cur_pos / OCTET_BITS_SIZE;
				avl_len = cur_pos % OCTET_BITS_SIZE;							// 0 ~ 7,	avl_len = 3, rest = 5

				work_len = avl_len < take_len ? avl_len : take_len;				//			work_len = 3
				shf = OCTET_BITS_SIZE - work_len;								// 7 ~ 0	shf = 5

				mask = (0x1 << work_len) - 1; // 작업 bits 수만큼만 마스킹		0x01 << 5 = 0x20, 0x20 - 1 = 0x1F
					
				(*dst) = ((*dst) << work_len) | ((DZ1_ASN1_STREAM_QUEUE_TYPE)(bits[idx] >> shf) & mask);	// 작업 bits 수 만큼 밀고 작업 bits 만큼만 붙인다
					
				ret += work_len;
				cur_pos += work_len;
				take_len -= work_len;
			}
		}
	}
	return errp->code == 0 ? ret : -1;
}

static bool_t _is_ingress_queue_flushable(Dz1Asn1Stream *p)
{
	bool_t ret = FALSE;
	if ((p->ingress_bits& 0x7) == 0) ret = TRUE;
	return ret;
}

static bool_t _ingress_queue_flush(Dz1Asn1Stream *dst, Dz1Error *err)
{	// 옥텟 정렬된 입력비트큐를 옥텟큐로 밀어넣는다.
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t v8;
	u16_t v16;
	switch(dst->ingress_bits)
	{
	case 0:
		Dz1Error_set(errp, 0);
		break;
	case 8:
		v8 = (u8_t)((dst->ingress >> 24) & 0xFF);
		if (_Dz1ElasticBuf_push(dst->elb, (u8_t *)&v8, 1, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case 16:
		v16 = Dz1Endian2_host2big((u16_t)((dst->ingress >> 16) & 0xFFFF));
		if (_Dz1ElasticBuf_push(dst->elb, (u8_t *)&v16, 2, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case 24:
		v16 = Dz1Endian2_host2big((u16_t)((dst->ingress >> 16) & 0xFFFF));
		v8 = (u8_t)((dst->ingress >> 8) & 0xFF);
		if (_Dz1ElasticBuf_push(dst->elb, (u8_t *)&v16, 2, errp) == FALSE) ERR_OUT(errp);
		else if (_Dz1ElasticBuf_push(dst->elb, (u8_t *)&v8, 1, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case 32:
		dst->ingress = Dz1Endian4_host2big(dst->ingress);
		if (_Dz1ElasticBuf_push(dst->elb, (u8_t *)&dst->ingress, QUEUE_OCTET_SIZE, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
	}

	if (errp->code == 0)
	{
		dst->ingress = 0;
		dst->ingress_bits = 0;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_pushBits(Dz1Asn1Stream *dst, u8_t *bits, s32_t bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || bits == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bits_len == 0) Dz1Error_set(errp, 0);
	else if (_is_ingress_queue_flushable(dst) && bits_len >= OCTET_BITS_SIZE)
	{	// 입력비트큐가 정렬되어있고 삽입 데이터 길이가 옥텟 비트수 보다 같거나 크다.
		u8_t *cp = bits;
		s32_t bits_octet_len = bits_len >> 3;													// 사용자버퍼의 옥텟 길이계산
		_ingress_queue_flush(dst, NULL);														// 큐를 버퍼로 밀어넣는다.
		if (_Dz1ElasticBuf_push(dst->elb, cp, bits_octet_len, errp) == FALSE) ERR_OUT(errp);	// 옥텟길이만큼 옥텟큐로 바로 삽입
		else
		{
			cp += bits_octet_len;																// 사용자버퍼 위치조정
			bits_len -= (bits_octet_len << 3);													// 사용자버퍼 비트길이 조정

			if (bits_len > 0)
			{																					// 잔여 비트가 있다.(8 미만)
				s32_t shf = QUEUE_BITS_SIZE - bits_len;
				dst->ingress = ((DZ1_ASN1_STREAM_QUEUE_TYPE)(*cp) & 0xFF) << shf;				// 입력비트큐의 맨 앞에 놓는다.
				dst->ingress_bits = bits_len;													// 입력비트큐 크기조정
			}
			Dz1Error_set(errp, 0);
		}
	}
	else
	{	// 입력비트큐가 옥텟정렬되어 있지 않거나, 삽입 데이터 길이가 옥텟 비트수 미만이다.
		ssize_t sz;
		s32_t remain_bits, cur_pos = 0;
		DZ1_ASN1_STREAM_QUEUE_TYPE temp;

		Dz1Error_set(errp, 0);

		while(errp->code == 0 && cur_pos < bits_len)
		{
			remain_bits = QUEUE_BITS_SIZE - dst->ingress_bits;

			if ((sz = _get_octet(&temp, bits, cur_pos, remain_bits, bits_len, errp)) < 0) ERR_OUT(errp);	// 입력비트큐를 채울만큼 가져온다 (LSB Aligned)
			else if (sz < remain_bits)
			{																								// 일부만 채웠다
				dst->ingress |= (temp <<= remain_bits - sz);												// 입력비트큐에 붙인다
				dst->ingress_bits += sz;																	// 입력비트큐 크기조정
			}
			else
			{																								// 완전히 채웠다
				dst->ingress |= (temp >>= dst->ingress_bits);												// 입력비트큐에 붙인다.
				dst->ingress_bits = QUEUE_BITS_SIZE;														// 입력비트큐 길이는 만땅이다.

				sz -= remain_bits;																			// 비트버퍼 크기조정
				if (_ingress_queue_flush(dst, errp) == FALSE) ERR_OUT(errp);								// 입력비트큐를 옥텟큐에 넣는다.
				else if (sz > 0)
				{																							// 비트버퍼가 남았다.
					dst->ingress = temp << (QUEUE_BITS_SIZE - sz);											// 입력비트큐에 붙인다.
					dst->ingress_bits = sz;																	// 입력비트큐 크기조정
				}
			}
			cur_pos += sz;																					// 사용자버퍼 위치조정
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_pushBitsI64(Dz1Asn1Stream *dst, u64_t src, s32_t bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bits_len == 0) Dz1Error_set(errp, 0);
	else
	{
		u8_t v = 0;
		int cnt = sizeof(src) << 3;
		src <<= (cnt - bits_len);
		while(errp->code == 0 && bits_len)
		{
			v = (u8_t)((src >> (cnt - 8)) & 0xFF);
			if (bits_len >= 8)
			{
				if (Dz1Asn1Stream_pushOctet(dst, v, errp) == FALSE) ERR_OUT(errp);
				else
				{
					src <<= 8;
					bits_len -= 8;
					Dz1Error_set(errp, 0);
				}
			}
			else if (Dz1Asn1Stream_pushBits(dst, &v, bits_len, errp) == FALSE) ERR_OUT(errp);
			else
			{
				bits_len = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1Asn1Stream_pushBitsI32(Dz1Asn1Stream *dst, u32_t src, s32_t bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bits_len == 0) Dz1Error_set(errp, 0);
	else
	{
		u8_t v = 0;
		int cnt = sizeof(src) << 3;
		src <<= (cnt - bits_len);
		while(errp->code == 0 && bits_len)
		{
			v = (u8_t)((src >> (cnt - 8)) & 0xFF);
			if (bits_len >= 8)
			{
				if (Dz1Asn1Stream_pushOctet(dst, v, errp) == FALSE) ERR_OUT(errp);
				else
				{
					src <<= 8;
					bits_len -= 8;
					Dz1Error_set(errp, 0);
				}
			}
			else if (Dz1Asn1Stream_pushBits(dst, &v, bits_len, errp) == FALSE) ERR_OUT(errp);
			else
			{
				bits_len = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1Asn1Stream_pushBitsI16(Dz1Asn1Stream *dst, u16_t src, s32_t bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bits_len == 0) Dz1Error_set(errp, 0);
	else
	{
		u8_t v = 0;
		int cnt = sizeof(src) << 3;
		src <<= (cnt - bits_len);
		while(errp->code == 0 && bits_len)
		{
			v = (u8_t)((src >> (cnt - 8)) & 0xFF);
			if (bits_len >= 8)
			{
				if (Dz1Asn1Stream_pushOctet(dst, v, errp) == FALSE) ERR_OUT(errp);
				else
				{
					src <<= 8;
					bits_len -= 8;
					Dz1Error_set(errp, 0);
				}
			}
			else if (Dz1Asn1Stream_pushBits(dst, &v, bits_len, errp) == FALSE) ERR_OUT(errp);
			else
			{
				bits_len = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1Asn1Stream_pushBit1(Dz1Asn1Stream *dst, bool_t bit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t v = bit ? 0x80 : 0x00;
	if (Dz1Asn1Stream_pushBits(dst, &v, 1, errp) == FALSE) ERR_OUT(errp);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_pushAlign(Dz1Asn1Stream *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	s32_t temp = 0;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = dst->ingress_bits % OCTET_BITS_SIZE) == 0) Dz1Error_set(errp, 0);
	else if ((dst->ingress_bits += temp) == QUEUE_BITS_SIZE)
	{
		if (_ingress_queue_flush(dst, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_pushOctet(Dz1Asn1Stream *dst, u8_t octet, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Asn1Stream_pushBits(dst, &octet, OCTET_BITS_SIZE, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_pushOctets(Dz1Asn1Stream *dst, u8_t *octets, u32_t octets_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Asn1Stream_pushBits(dst, octets, octets_len << 3, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}









static ssize_t _put_bits(u8_t *dst_bits, s32_t cur_pos, s32_t dst_bits_len, DZ1_ASN1_STREAM_QUEUE_TYPE src, s32_t src_bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst_bits == NULL || src_bits_len == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{	// src_bits_len = 2
		s32_t idx, dst_filled, needs_bits, work_sz;
		u8_t src_mask, dst_mask;
		
		while(src_bits_len > 0 && cur_pos < dst_bits_len)
		{
			idx			= cur_pos / OCTET_BITS_SIZE;
			dst_filled	= cur_pos % OCTET_BITS_SIZE;

			needs_bits = OCTET_BITS_SIZE - dst_filled;							// needs_bits = 5
			dst_mask = ~((1 << needs_bits) - 1);								// 0x01 << 5 = 0x20, 0x20 - 1 = 0x1F, ~0x1F = 0xD0

			work_sz = src_bits_len < needs_bits ? src_bits_len : needs_bits;	// src 에서 따올 비트수(항상 8보다 작다), work_sz = 2
			src_mask = ((0x01 << work_sz) - 1) << (needs_bits - work_sz);		// 0x01 << 2 = 0x04, 0x04 - 1 = 0x03, 0x03 << 3(shf_up = 5 - 2 = 3) = 0x18

			// src MSB 부터 work_bits 만큼을 dst_bits[idx]의 LSB에 붙인다.
			dst_bits[idx] = (dst_bits[idx] & dst_mask) | (u8_t)((src >> (24 + dst_filled)) & src_mask);

			src <<= work_sz;
			src_bits_len -= work_sz;

			cur_pos += work_sz;
			ret += work_sz;
		}
	}
	return ret;
}

static bool_t _is_egress_queue_aligned(Dz1Asn1Stream *src)
{
	bool_t ret = FALSE;
	if ((src->egress_bits & 0x7) == 0) ret = TRUE;
	return ret;
}

static ssize_t _egress_queue_pop_octet(Dz1Asn1Stream *src, u8_t *dst_octets, s32_t dst_octet_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	u8_t v8 = 0;

	s32_t src_octet_size = src->egress_bits >> 3;
	s32_t work_size = src_octet_size < dst_octet_size ? src_octet_size : dst_octet_size;

	while(src->egress_bits >= 8 && work_size > 0)
	{
		*dst_octets++ = (u8_t)((src->egress >> 24) & 0xFF);
		dst_octet_size--;

		work_size--;

		src->egress <<= 8;
		src->egress_bits -= 8;

		ret += 8;
	}
	return errp->code == 0 ? ret : -1;
}

ssize_t Dz1Asn1Stream_popOctets(Dz1Asn1Stream *src, u8_t *buf, u32_t buf_octet_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0, bits_sz;
	if (src == NULL || buf == NULL || buf_octet_len == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((bits_sz = Dz1Asn1Stream_popBits(src, buf, buf_octet_len << 3, errp)) < 0) ERR_OUT(errp);
	else
	{
		ret = bits_sz / OCTET_BITS_SIZE + ((bits_sz % OCTET_BITS_SIZE) ? 1 : 0);
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? ret : -1;
}

ssize_t Dz1Asn1Stream_popOctet(Dz1Asn1Stream *src, u8_t *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = Dz1Asn1Stream_popOctets(src, buf, 1, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? ret : -1;
}

static ssize_t _egress_queue_load(Dz1Asn1Stream *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t buf[QUEUE_OCTET_SIZE];
	ssize_t ret = 0, sz;
	if ((sz = Dz1ElasticBuf_pop(src->elb, buf, QUEUE_OCTET_SIZE, errp)) < 0) ERR_OUT(errp);
	else if (sz == 0)
	{													// 옥텟큐가 비어있다.
		if (src->ingress_bits == 0)
		{												// 입력 비트큐도 비어있다.
			Dz1Error_set(errp, EAGAIN);					// 나중에 다시 시도
			return 0;									// 에러는 내지않음
		}
		else 
		{
			src->egress = src->ingress;					// 입력 비트큐를 출력 비트큐로 이동
			ret = src->egress_bits = src->ingress_bits;	// 입력 비트큐를 출력 비트큐로 이동

			src->ingress = 0;							// 입력 비트큐 리셋
			src->ingress_bits = 0;						// 입력 비트큐 리셋

			Dz1Error_set(errp, 0);
		}
	}
	else if (sz == QUEUE_OCTET_SIZE)
	{	// 출력 비트큐의 옥텟 크기만큼 읽은 경우
		src->egress = *(DZ1_ASN1_STREAM_QUEUE_TYPE *)buf;	
		src->egress = Dz1Endian4_big2host(src->egress);
		src->egress_bits = QUEUE_BITS_SIZE;

		ret = src->egress_bits;
		Dz1Error_set(errp, 0);
	}
	else
	{	// 출력 비트큐의 옥텟 크기보다 적게 읽은 경우
		ssize_t i;
		src->egress_bits = 0;
		for (i = 0; i < sz; i++)
		{
			src->egress <<= 8;
			src->egress |= ((DZ1_ASN1_STREAM_QUEUE_TYPE)buf[i] & 0xFF);
			src->egress_bits += 8;
		}

		for ( ;i < QUEUE_OCTET_SIZE; i++) src->egress <<= 8;

		ret = src->egress_bits;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Stream_popAlign(Dz1Asn1Stream *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	s32_t temp = 0;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = src->egress_bits % OCTET_BITS_SIZE) == 0) Dz1Error_set(errp, 0);
	else 
	{
		src->egress <<= temp;
		src->egress_bits -= temp;
		if (src->egress_bits == 0)
		{
			if (_egress_queue_load(src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Stream_popBit1(Dz1Asn1Stream *src, bool_t *bit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	u8_t v = 0;
	if (src == NULL || bit == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Asn1Stream_popBits(src, &v, 1, errp)) < 0) ERR_OUT(errp);
	else if (ret == 0) Dz1Error_set(errp, EAGAIN);
	else
	{
		(*bit) = v ? TRUE : FALSE;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? ret : -1;
}

#define POP_OPER_NO_DATA(len, ep, success_v) \
do {\
	if (len == 0)\
	{								/* 한번도 뽑은적이 없다. */\
		Dz1Error_set(errp, EAGAIN);	/* 나중에 다시 시도 */\
		return success_v;			/* 에러는 내지 않음 */\
	}\
	else Dz1Error_set(ep, 0);		/* 뭐라도 읽었으니 성공으로 본다 */\
} while(0)

ssize_t Dz1Asn1Stream_popBits(Dz1Asn1Stream *src, u8_t *bits_buf, s32_t buf_bits_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0, bits_sz;
	if (src == NULL || bits_buf == NULL || buf_bits_len == 0) ERR_SET_OUT(errp, EINVAL);
	else if (_is_egress_queue_aligned(src) && buf_bits_len >= OCTET_BITS_SIZE)							// 비트큐가 비어있을 수 있다.
	{	// 출력 비트큐가 옥텟 정렬되어 있고, 옥텟 비트길이 이상을 뽑기 원하는 경우
		u8_t *cp = bits_buf;
		s32_t buf_octet_len = buf_bits_len >> 3;
		if ((bits_sz = _egress_queue_pop_octet(src, cp, buf_octet_len, errp)) < 0) ERR_OUT(errp);		// 비트큐의 내용을 버퍼로 옮긴다(항상 8의 배수)
		else
		{
			ssize_t octet_sz = bits_sz >> 3;

			cp += octet_sz;																				// 사용자버퍼 위치 이동
			buf_octet_len -= octet_sz;																	// 사용자버퍼 옷텟 크기 조정
			buf_bits_len -= bits_sz;																	// 사용자버퍼 비트 크기 조정

			ret += bits_sz;																				// 리턴값 계산

			if (buf_octet_len > 0 &&																	// 뽑을 길이가 남았으면
				(octet_sz = Dz1ElasticBuf_pop(src->elb, cp, buf_octet_len, errp)) < 0) ERR_OUT(errp);	// 옥텟길이만큼 옥텟큐에서 바로 뽑
			else if (octet_sz == 0)																		// 옥텟큐가 비어있다.
				POP_OPER_NO_DATA(ret, errp, 0);															// 읽은적이 없으면 에러코드만 설정, 항상 성공을 리턴
			else 
			{
				bits_sz = (octet_sz << 3);																// 뽑읜 옥텟의 비트 길이 계산

				cp += octet_sz;																			// 사용자버퍼 위치 이동
				buf_octet_len -= octet_sz;																// 사용자버퍼 옥텟크기 조정
				buf_bits_len -= bits_sz;																// 사용자버퍼 비트크기 조정

				ret += bits_sz;																			// 리턴값 계산

				if (buf_octet_len > 0)																	// 옥텟 길이 이상 더 뽑아야 한다. 하지만 옥텟큐는 비었다.
					Dz1Error_set(errp, 0);																// 뭐라도 읽었으니 성공으로 본다
				else if (buf_bits_len > 0)																// 8비트 미만의 잔여 비트를 뽑아야 한다.
				{																						// 옥텟큐는 비어있지 않을 수 있다.
					if ((bits_sz = _egress_queue_load(src, errp)) < 0) ERR_OUT(errp);					// 비트큐 로딩
					else if (bits_sz == 0)																// 옥텟큐가 비어있다
						Dz1Error_set(errp, 0);															// 뭐라도 읽었으니 성공으로 본다
					else if ((bits_sz = _put_bits(cp, 0, buf_bits_len, src->egress, src->egress_bits, errp)) < 0) ERR_OUT(errp);
					else if (bits_sz == 0)																// 비트를 옮긴게 하나도 없다.(don't care)
						Dz1Error_set(errp, 0);															// 뭐라도 읽었으니 성공으로 본다
					else
					{
						src->egress <<= bits_sz;														// 비트큐 조정
						src->egress_bits -= bits_sz;													// 비트큐 길이조정

						buf_bits_len -= bits_sz;														// 사용자버퍼의 비트 크기 조정

						ret += bits_sz;																	// 리턴값 계산

						Dz1Error_set(errp, 0);															// 끝
					}
				}
				else Dz1Error_set(errp, 0);																// 잔여 비트가 없으면 끝
			}
		}
	}
	// 옥텟 정렬 되지 않은 비트큐 또는 옥텟 길이 미만을 뽑기 원하는 경우
	else if ((bits_sz = src->egress_bits) == 0 && (bits_sz = _egress_queue_load(src, errp)) < 0) ERR_OUT(errp);	// 비트큐 로딩(필요시)
	else if (bits_sz == 0)
	{	// 출력비트큐, 옥텟큐, 입력비트큐 모두 비어있다.
		Dz1Error_set(errp, EAGAIN);
		return 0;
	}
	else
	{
		ssize_t cur_pos = 0;
		DZ1_ASN1_STREAM_QUEUE_TYPE temp = 0;

		while(errp->code == 0 && cur_pos < buf_bits_len)
		{
			if ((bits_sz = _put_bits(bits_buf, cur_pos, buf_bits_len, src->egress, src->egress_bits, errp)) < 0) ERR_OUT(errp);
			else if (bits_sz == 0)
			{										// 뽑은 비트가 하나도 없다.
				POP_OPER_NO_DATA(ret, errp, 0);		// 읽은적이 없으면 에러코드만 설정, 항상 성공을 리턴
				break;								// 루프 종료
			}
			else
			{										// 비트를 뽑아냄
				src->egress <<= bits_sz;			// 비트큐 조정
				src->egress_bits -= bits_sz;		// 비트큐 크기 조정

				cur_pos += bits_sz;					// 사용자버퍼 비트위치 조정
				ret += bits_sz;						// 리턴값 계산

				if ((bits_sz = src->egress_bits) == 0 && (bits_sz = _egress_queue_load(src, errp)) < 0) ERR_OUT(errp);	// 비트큐 로딩(필요시)
				else if (bits_sz == 0)
				{									// 옥텟큐, 입력비트큐가 비어있다.
					POP_OPER_NO_DATA(ret, errp, 0);	// 읽은적이 없으면 에러코드만 설정, 항상 성공을 리턴
					break;							// 루프 종료
				}
			}
		}
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

