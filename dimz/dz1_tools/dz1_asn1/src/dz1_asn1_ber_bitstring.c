#include "dz1_asn1_codec_ber.h"

/*
* X.680 ASN.1
22.2		The first bit in a bit string is called the leading bit. The final bit in a bit string is called the trailing bit.
			비트 문자열의 첫 비트를 "leading bit"라고합니다. 비트 문자열의 최종 비트를 "trailing bit"라고합니다.
			NOTE -	This terminology is used in specifying the value notation and in defining encoding rules.
					이 용어는 값 표기법을 지정하고 인코딩 규칙을 정의하는 데 사용됩니다.

22.7		When a "NamedBitList" is used in defining a bitstring type ASN.1 encoding rules are free to add (or remove) 
			arbitrarily any trailing 0 bits to (or from) values that are being encoded or decoded. 
			"NamedBitList"가 비트열 유형을 정의하는 데 사용되는 경우 ASN.1 인코딩 규칙은 인코딩 또는 디코딩되는 값에(또는 해당 값에서) 
			후행 0비트를 임의로 추가(또는 제거)할 수 있습니다.
			Application designers should therefore ensure that different semantics are not associated with such values 
			which differ only in the number of trailing 0 bits.
			따라서 응용 프로그램 설계자는 다른 의미론이 0 비트의 후행 수에서만 다른 값과 관련이 없도록해야합니다.
*/

/*
* X.690 BER,CER,DER
8.6			Encoding of a bitstring value

8.6.1		The encoding of a bitstring value shall be either primitive or constructed at the option of the sender.
			NOTE -	Where it is necessary to transfer part of a bit string before the entire bitstring is available, the constructed encoding is used.

8.6.2		The contents octets for the primitive encoding shall contain an initial octet followed by zero, one or more subsequent octets.
			컨텐츠 옥텟은 초기 옥텟을 인코딩 하여야 하며, 후행 옥텟은 0개 이상이 인코딩 된다.

8.6.2.1		The bits in the bitstring value, commencing with the leading bit and proceeding to the trailing bit, shall be placed in bits 8 to 1 of the first subsequent octet,
			followed by bits 8 to 1 of the second subsequent octet, followed by bits 8 to 1 of each octet in turn, followed by as many bits as are needed of the final subsequent octet, 
			commencing with bit 8. 
			비트스트링 값의 비트는 leading bit부터 trailing bit까지를 초기 옥텟 다음에 오는 옥텟의 Bit 8에서부터 배치한다.
			NOTE -	The terms "leading bit" and "trailing bit" are defined in Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.2.
			"leading bit" 와 "trailing bit" 는 Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.2에 정의되어 있다.

8.6.2.2		The initial octet shall encode, as an unsigned binary integer with bit 1 as the least significant bit, the number of unused bits in the final subsequent octet.
			초기 옥텟은 Bit 8을 LSB로 하는 부호 없는 정수 값으로, 마지막 옥텟에 사용하지 않는 비트의 개수를 저장한다.
			The number shall be in the range zero to seven. 
			이 값은 0부터 7까지이다.

8.6.2.3		If the bitstring is empty, there shall be no subsequent octets, and the initial octet shall be zero.
			비트스트링 값이 비어있다면, 후행 옥텟은 없으며, 초기 옥텟은 0이어야 한다.

8.6.2.4		Where Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.7, applies a BER encoder/decoder can add or remove trailing 0 bits from the value.
			Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.7에는 BER 인코더/디코더는 비트스트링 값의 후행에 0비트를 추가하거나 제거할 수 있어야 한다.
			NOTE -	If a bitstring value has no 1 bits, then an encoder (as a sender's option) may encode the value with a length of 1 and with an initial octet set 
					to 0 or may encode it as a bit string with one or more 0 bits following the initial octet.
					비트스트링 값에 1인 비트가 없다면, 인코더는 (전송측의 선택에 따라) Length는 1로, 초기 옥텟은 0으로 인코딩 하거나,
					전체 크기를 Length로(>= 1) 설정, 초기 옥텟 및 후행 옥텟을 0으로 채워 인코딩할 수 있다.

8.6.3		The contents octets for the constructed encoding shall consist of zero, one, or more nested encodings.
			구조형 인코딩의 내용 옥셋은 다수의 중첩된 인코팅으로 구성할 수 있다.(길이에 따라 중첩 인코딩은 생략될 수 있다.)
			NOTE -	Each such encoding includes identifier, length, and contents octets, and may include end-of-contents octets if it is constructed.
					이 인코딩을 적용한 경우 각각의 인코딩은 Identifier, Length, Contents 를 포함하며, End-of-Contents 를 포함할 수 있다.

8.6.4		To encode a bitstring value in this way, it is segmented. Each segment shall consist of a series of consecutive bits of the value, 
			and with the possible exception of the last, shall contain a number of bits which is a multiple of eight. 
			이 인코딩 방법으로 비트스트링을 인코드 하려면, 세그먼트화 해야한다. 각 세그먼트는 일련의 연속 비트 값이고, 마지막 세그먼트에 이외의
			세그먼트는 8 bit의 배수의 길이만큼 비트값을 저장하여야 한다.

			Each bit in the overall value shall be in precisely one segment, but there shall be no significance placed on the segment boundaries. 
			각 비트의 최종 값은 정확히 하나의 세그먼트에 존재하여야 하지만, 세그먼트의 경계는 중요하지 않다.(모든 세그먼트를 연이어 붙이면 각 비트의
			값은 원래 값과 동일하게 된다.)
			NOTE -	A segment may be of size zero, i.e. contain no bits.
					비트스트링이 비어있는 경우, 세그먼트는 길이가 0이 될 수 있다.

8.6.4.1		Each encoding in the contents octets shall represent a segment of the overall bitstring, the encoding arising from a recursive application of this subclause. 
			콘텐츠 옥텟의 각 인코딩은 전체 비트열의 세그먼트를 나타내야 하며, 인코딩은 이 하위 절의 재귀적 적용에서 발생합니다.
			In this recursive application, each segment is treated as if it were a bitstring value. 
			이 재귀 응용에서 각 세그먼트는 비트 문자열 값인 것처럼 처리됩니다.
			The encodings of the segments shall appear in the contents octets in the order in which their bits appear in the overall value.
			세그먼트 인코딩은 비트스트링 전체값의 순서대로 나타나야 한다.

			NOTE 1 -	As a consequence of this recursion, each encoding in the contents octets may itself be primitive or constructed.
						이 재귀의 결과로 콘텐츠 옥텟의 각 인코딩은 자체적으로 Primitive 인코딩 또는 Constructed 인코딩 일 수 있습니다.
						However, such encodings will usually be primitive. 
						그러나 이러한 인코딩은 일반적으로 Primitive 인코딩 입니다.
						
			NOTE 2 -	In particular, the tags in the contents octets are always universal class, number 3.
						특히 콘텐츠 옥텟의 태그는 항상 "UNIVERSAL 3"입니다.

9			Canonical encoding rules
9.2			String encoding forms
			Bitstring, octetstring, and restricted character string values shall be encoded with a primitive encoding if they would require no more than 1000 contents octets, 
			and as a constructed encoding otherwise. 
			비트스트링, 옥텟스트링 및 제한된 문자열 값은 1000개 이하의 콘텐츠 옥텟이 필요한 경우 "PRIMITIVE"로 인코딩되고 그렇지 않은 경우 "CONSTRUCTED"로 인코딩됩니다.

			The string fragments contained in the constructed encoding shall be encoded with a primitive encoding. 
			구성된 인코딩에 포함된 문자열 조각은 "PRIMITIVE"로 인코딩되어야 합니다.

			The encoding of each fragment, except possibly the last, shall have 1000 contents octets. (Contrast with 8.23.6.)  
			마지막을 제외한 각 조각의 인코딩은 1000 개의 목차 옥텟을 가져야합니다. (8.23.6과 대조)

			The last fragment shall have at least one, and no more than 1000, contents octets.
			마지막 프래그먼트는 1개 이상 1000개 이하의 콘텐츠 옥텟을 가져야 합니다.

10			Distinguished encoding rules
10.2		String encoding forms
			For bitstring, octetstring and restricted character string types, the constructed form of encoding shall not be used. (Contrast with 8.23.6.)
			비트스트링, 옥텟스트링 및 제한된 문자열 유형의 경우 "CONSTRUCTED" 형식의 인코딩이 사용되지 않습니다. (8.23.6과 대조)

11			Restrictions on BER employed by both CER and DER

11.2		Unused bits

11.2.1		Each unused bit in the final octet of the encoding of a bit string value shall be set to zero.
			BIT STRING 값 인코딩의 마지막 옥텟에서 사용되지 않은 각 비트는 0으로 설정되어야 합니다.

11.2.2		Where Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.7, applies, the bitstring shall have all trailing 0 bits removed before it is encoded.
			Rec. ITU-T X.680 | ISO/IEC 8824-1, 22.7을 적용하여, 비트 스트링은 인코딩되기 전에 모든 트레일 0 비트를 제거해야합니다.

			NOTE 1 -	In the case where a size constraint has been applied, the abstract value delivered by a decoder to the application will be one of those satisfying 
						the size constraint and differing from the transmitted value only in the number of trailing 0 bits.
			NOTE 2 -	If a bitstring value has no 1 bits, then an encoder shall encode the value with a length of 1 and an initial octet set to 0.
*/
bool_t Dz1Asn1BitStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1BitStr *v = (Dz1Asn1BitStr *)dataPtr;
	Dz1Asn1MetaDataRange *sz_cons = NULL;
	if ((sz_cons = p->size) != NULL)
	{	// max bit is over to high -> ERROR
		if (Dz1Asn1MetaDataRange_test(sz_cons, (Dz1Asn1Int)v->maxBit) > 0) ERR_SET_OUT(errp, E2BIG);
		// allocByte is under of low -> ensure memory allocation to high
		else if (Dz1Asn1MetaDataRange_test(sz_cons, (Dz1Asn1Int)(v->allocByte << 3)) < 0)
		{
			u32_t new_alloc = (u32_t)((sz_cons->high + 7) >> 3);
			u8_t *new_bits = Dz1Calloc(sizeof(u8_t), new_alloc, errp);
			if (new_bits == NULL) ERR_OUT(errp);
			else
			{
				if (v->bits != NULL && v->allocByte > 0)
				{
					memcpy(new_bits, v->bits, v->allocByte);
					Dz1Free(v->bits);
					v->bits = NULL;
				}

				v->bits = new_bits;
				new_bits = NULL;

				v->allocByte = new_alloc;

				Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bitstring_v_enc(Dz1ElasticBuf *dst, u8_t unused_bits, u8_t *data, u32_t sz, void *param, Dz1Error *errp)
{
	if (_Dz1ElasticBuf_push(dst, &unused_bits, 1, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1ElasticBuf_push(dst, data, sz, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bitstring_tlv_enc(Dz1ElasticBuf *dst, Dz1Asn1Tag *origin_tag, u8_t unused_bits, u8_t *data, u32_t sz, void *param, Dz1Error *errp)
{
	Dz1Asn1Tag tag = { origin_tag->cls, Dz1Asn1TagFlag_primitive, origin_tag->numb };
	if (Dz1Asn1Tag_enc_BER(dst, &tag, FALSE, param, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1Asn1BerLength_enc_BER(dst, 1 + sz, param, errp) == FALSE) ERR_OUT(errp);
	else if (_bitstring_v_enc(dst, unused_bits, data, sz, param, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

// Dz1Asn1TypeDescr *descr, Dz1Asn1BerEncoder *encoder, Dz1ElasticBuf *dst, void *_src, bool_t *ret_is_constructed_form, void *param, Dz1Error *err
bool_t Dz1Asn1BitStr_enc_BER(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1BitStr *src = (Dz1Asn1BitStr *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t frag_size = dz1Asn1EncoderFragSize - 1;

		u32_t bits_size = (u32_t)(src->maxBit + 1);
		u32_t octet_size = (u32_t)((src->maxBit + 7) >> 3);
		u8_t unused_bits = 8 - (u8_t)(bits_size & 0x7);
		if (param->opt == Dz1Asn1BerEncoderOpt_cer && octet_size > frag_size)
		{
			u8_t *cp = src->bits;
			u32_t work_size;
			while(octet_size > frag_size)
			{
				work_size = octet_size > frag_size ? frag_size : octet_size;
				if (_bitstring_tlv_enc(dst, descr->tag, 0, cp, work_size, param, errp) == FALSE) ERR_OUT(errp);
				else
				{
					cp += work_size;
					octet_size -= work_size;
					bits_size -= (work_size << 3);
					Dz1Error_set(errp, 0);
				}
			}

			if (errp->code == 0)
			{
				if (_bitstring_tlv_enc(dst, descr->tag, unused_bits, cp, octet_size, param, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}

			*ret_is_constructed_form = TRUE;
		}
		else if (_bitstring_v_enc(dst, unused_bits, src->bits, octet_size, param, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			*ret_is_constructed_form = FALSE;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1ElasticBuf_modifyByte(Dz1ElasticBuf *dst, size_t offset, u8_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		bool_t modified = FALSE;
		u32_t node_data_size = 0;
		Dz1ElasticBufEntry *node = NULL;
		for (node = dst->head; node != NULL; node = node->next)
		{
			node_data_size = node->data_end - node->data_start;
			if (offset >= node_data_size) offset -= node_data_size;
			else
			{
				Dz1Binary *bin = node->buf;
				bin->data[node->data_start + offset] = v;
				modified = TRUE;
				break;
			}
		}

		if (modified == FALSE) ERR_SET_OUT(errp, ENOMEM);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1BitStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1WipValue *wip = NULL;
	Dz1Asn1WipBitString *wip_bits = NULL;
	Dz1Asn1Tag *tag = stk->tag;
	Dz1Error_set(errp, 0);
	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{	// construct form, length is either soc or specific value
		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			dst->u8data = 0;
			if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_bit_str, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
			else if ((wip_bits = wip->x.bit_str = Dz1Asn1WipBitString_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((wip_bits->elb = Dz1ElasticBuf_new(1000, FALSE, errp)) == NULL) ERR_OUT(errp);
			else if (_Dz1ElasticBuf_push(wip_bits->elb, &dst->u8data, 1, errp) == FALSE) ERR_OUT(errp);
			else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((wip_bits = wip->x.bit_str) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrBitStr, errp) == FALSE) ERR_OUT(errp);
			else 
			{
				dst->state = Dz1Asn1BerDecoderDataState_nested;
				ret = Dz1Asn1BerLength_ssoc;
			}
			break;
		case Dz1Asn1BerDecoderDataState_nested:
			if ((ret_stk = stk->ret_stk) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
//				u8_t initial_octet = 0;

				ssize_t sz = 0;
				Dz1Asn1WipValue *ret_data = NULL;
				Dz1Asn1WipBitString *ret_bits = NULL;
				Dz1ElasticBuf *ret_elb = NULL, *cur_elb = NULL;
				pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);

				dst->u64data += ret_stk->consumed;
				stk->consumed += ret_stk->consumed;

				if (0) { }
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (wip->present != Dz1Asn1WipValuePresent_bit_str) ERR_SET_OUT(errp, EFAULT);
				else if ((wip_bits = wip->x.bit_str) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((cur_elb = wip_bits->elb) == NULL) ERR_SET_OUT(errp, EFAULT);
				// resolve source data struct
				else if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (ret_data->present == Dz1Asn1WipValuePresent_max)
				{
					if (Dz1ElasticBuf_modifyByte(cur_elb, 0, dst->u8data, errp) == FALSE) ERR_OUT(errp);
					else
					{
						dst->state = Dz1Asn1BerDecoderDataState_max; // return EOC -> End of Constructed Decoding
						ret = Dz1Asn1BerLength_ssoc;
					}
				}
				else
				{
					if (ret_data->present != Dz1Asn1WipValuePresent_bit_str) ERR_SET_OUT(errp, EFAULT);
					// resolve source data struct
					else if ((ret_bits = ret_data->x.bit_str) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((ret_elb = ret_bits->elb) == NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if ((sz = Dz1ElasticBuf_pop(ret_elb, &dst->u8data, 1, errp)) < 0) ERR_OUT(errp);		// get initial octet
					else if (sz != 1) ERR_SET_OUT(errp, EFAULT);
					else if (wip_bits->trim_bits != 0 && dst->u8data != 0) ERR_SET_OUT(errp, EPERM);			// duplicate final segment
					else if (Dz1ElasticBuf_move(cur_elb, ret_elb, errp) == FALSE) ERR_OUT(errp);
					else
					{	// save some state
						if (wip_bits->trim_bits != 0) wip_bits->trim_bits = (u32_t)dst->u8data;					// save trail unused bits count

						if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)
						{	// Next Segment
							if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrBitStr, errp) == FALSE) ERR_OUT(errp);
							else ret = Dz1Asn1BerLength_ssoc;
						}
						else if (dst->u64data == stk->len)
						{	// End of Decoding
							if (Dz1ElasticBuf_modifyByte(cur_elb, 0, dst->u8data, errp) == FALSE) ERR_OUT(errp);
							else
							{
								dst->state = Dz1Asn1BerDecoderDataState_max;
								ret = Dz1Asn1BerLength_ssoc;
							}
						}
						else ERR_SET_OUT(errp, EFAULT); // size fault
					}
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	// primitive form
	else if (tag->flag != Dz1Asn1TagFlag_primitive) ERR_SET_OUT(errp, EFAULT);
	else if (stk->len == Dz1Asn1BerLength_soc) ERR_SET_OUT(errp, EPERM);	// length can't be SOC
	else if (stk->len == 0) ERR_SET_OUT(errp, EPERM);					// BIT STRING contents length can't be 0 (at least 1)
	else
	{
		ssize_t sz;
		u8_t buf[1000];
		bool_t done = FALSE;
		Dz1ElasticBuf *elb = NULL;
		u32_t copy_sz = 0;

		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< BITS : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_bit_str, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
				else if ((wip_bits = wip->x.bit_str = Dz1Asn1WipBitString_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((wip_bits->elb = Dz1ElasticBuf_new(1000, FALSE, errp)) == NULL) ERR_OUT(errp);
				else
				{
					dst->s32data = (s32_t)(stk->len & 0x7FFFFFFF);
					dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				}
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				copy_sz = dst->s32data > sizeof(buf) ? sizeof(buf) : (u32_t)dst->s32data;

				if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((wip_bits = wip->x.bit_str) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((elb = wip_bits->elb) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((sz = Dz1Asn1Stream_popOctets(src, buf, copy_sz, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else if (_Dz1ElasticBuf_push(elb, buf, (size_t)sz, errp) == FALSE) ERR_OUT(errp);	// critical
				else
				{
					u32_t log_lv = 0;
					Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
					if (log_lv & DZ1_THREAD_LOG_DEBUG)
					{
						ssize_t i;
						for (i = 0; i < sz; i++) Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", buf[i]);
					}

					ret += sz;
					dst->u64data += sz;
					dst->s32data -= sz;

					if (dst->u64data == stk->len)
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						done = TRUE;
					}
					else if (dst->u64data > stk->len) ERR_SET_OUT(errp, EFAULT);	// size fault
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}

