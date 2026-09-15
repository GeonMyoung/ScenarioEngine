#include "dz1_asn1_codec_ber.h"

/*
8.7			Encoding of an octetstring value

8.7.1		The encoding of an octetstring value shall be either primitive or constructed at the option of the sender.
			Octet String 값의 인코딩은 전송측의 선택에 따라 Primitive 인코딩 또는 Constructed 인코딩을 사용하여야 합니다.
			NOTE -	Where it is necessary to transfer part of an octet string before the entire octetstring is available, the constructed encoding is used.
					전체 OctetString을 사용할 수 있기 전에 "OCTET STRING"의 일부를 전송해야 하는 경우 "CONSTRUCTED" 인코딩이 사용됩니다.

8.7.2		The primitive encoding contains zero, one or more contents octets equal in value to the octets in the data value, in the order they appear in the data value, 
			and with the most significant bit of an octet of the data value aligned with the most significant bit of an octet of the contents octets.
			"PRIMITIVE" 인코딩에는 데이터 값에 나타나는 순서대로 데이터 값의 옥텟과 값이 동일한 0개 이상의 콘텐츠 옥텟이 포함되며 
			데이터 값 옥텟의 최상위 비트가 내용 옥텟 중 옥텟의 최상위 비트 데이터 값과 정렬됩니다.

8.7.3		The contents octets for the constructed encoding shall consist of zero, one, or more encodings.
			"CONSTRUCTED" 인코딩에 대한 콘텐츠 옥텟은 0개 이상의 인코딩으로 구성되어야 합니다.
			NOTE -	Each such encoding includes identifier, length, and contents octets, and may include end-of-contents octets if it is constructed.
					이러한 각 인코딩은 식별자, 길이 및 콘텐츠 옥텟을 포함하고 "CONSTRUCTED" 인코딩인 경우 "end-Of-contents" 옥텟을 포함할 수 있습니다.

8.7.3.1		To encode an octetstring value in this way, it is segmented. Each segment shall consist of a series of consecutive octets of the value. 
			이 방법으로 Octet String값을 인코딩 하려면, 세그먼트화 해야 합니다. 각 세그먼트는 연이어 붙여서 원래 옥텟 스트링 값을 만듭니다.
			There shall be no significance placed on the segment boundaries. 
			세그먼트의 범위는 중요하지 않습니다.
			NOTE -	A segment may be of size zero, i.e. contain no octets.
					콘텐츠 옥텟이 없는 경우, 세그먼트 크기는 0일 수 있습니다.

8.7.3.2		Each encoding in the contents octets shall represent a segment of the overall octetstring, the encoding arising from a recursive application of this sub clause.
			개별 인코딩의 콘텐츠 옥텟은 전체 옥텟 스트링 값의 세그먼트이며, 이 세부 절의 응용으로 재귀적일 수 있습니다.
			In this recursive application, each segment is treated as if it were an octetstring value. 
			이러한 재귀적 적용에서, 각 세그먼트는 옥텟 스트링으로 다루어야 합니다.
			The encodings of the segments shall appear in the contents octets in the order in which their octets appear in the overall value.
			세그먼트의 순서와 컨텐츠 옥텟의 순서는 전체 옥텟 스트링 값에 나타난 순서와 일치하여야 합니다.
			NOTE 1 -	As a consequence of this recursion, each encoding in the contents octets may itself be primitive or constructed. 
						이 재귀적 적용에 결과로 컨텐츠 옥텟의 각 인코딩은 Primitive 인코딩이거나 Constructed 인코딩 일 수 있습니다.
						However, such encodings will usually be primitive. 
						그러나 이런 (세그먼트) 인코딩은 보통 Primitive 인코딩입니다.
			NOTE 2 -	In particular, the tags in the contents octets are always universal class, number 4.
						특히 컨텐츠 옥텟의 태그는 항상 UNIVERSAL 4를 사용합니다.

9			Canonical encoding rules

9.2			String encoding forms
			Bitstring, octetstring, and restricted character string values shall be encoded with a primitive encoding if they would require no more than 1000 contents octets, 
			and as a constructed encoding otherwise. 
			비트스트링, 옥텟스트링 및 제한된 문자열 값은 1000개 이하의 콘텐츠 옥텟이 필요한 경우 "PRIMITIVE"로 인코딩되고 그렇지 않은 경우 "CONSTRUCTED"로 인코딩됩니다.

			The string fragments contained in the constructed encoding shall be encoded with a primitive encoding. 
			구성된 인코딩에 포함된 문자열 조각은 "PRIMITIVE"로 인코딩되어야 합니다.

			The encoding of each fragment, except possibly the last, shall have 1000 contents octets. (Contrast with 8.23.6.)  
			마지막을 제외한 각 조각의 인코딩은 1000 개의 목차 옥텟을  가져야합니다. (8.23.6과 대조)

			The last fragment shall have at least one, and no more than 1000, contents octets.
			마지막 프래그먼트는 1개 이상 1000개 이하의 콘텐츠 옥텟을 가져야 합니다.

10			Distinguished encoding rules

10.2		String encoding forms
			For bitstring, octetstring and restricted character string types, the constructed form of encoding shall not be used. (Contrast with 8.23.6.)
			비트스트링, 옥텟스트링 및 제한된 문자열 유형의 경우 "CONSTRUCTED" 형식의 인코딩이 사용되지 않습니다. (8.23.6과 대조)

*/

static bool_t _octet_str_v_enc(Dz1ElasticBuf *dst, u8_t *data, u32_t sz, void *param, Dz1Error *errp)
{
	if (_Dz1ElasticBuf_push(dst, data, sz, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _octet_str_tlv_enc(Dz1ElasticBuf *dst, Dz1Asn1Tag *origin_tag, u8_t *data, u32_t sz, void *param, Dz1Error *errp)
{
	Dz1Asn1Tag tag = { origin_tag->cls, Dz1Asn1TagFlag_primitive, origin_tag->numb };
	if (Dz1Asn1Tag_enc_BER(dst, &tag, FALSE, param, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1Asn1BerLength_enc_BER(dst, sz, param, errp) == FALSE) ERR_OUT(errp);
	else if (_octet_str_v_enc(dst, data, sz, param, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1OctetStr_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OctetStr *src = (Dz1Asn1OctetStr *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (param->opt == Dz1Asn1BerEncoderOpt_cer && src->size > dz1Asn1EncoderFragSize)
		{
			u8_t *cp = src->data;
			u32_t sz = src->size;
			u32_t work_size;
			while(sz > dz1Asn1EncoderFragSize)
			{
				work_size = sz > dz1Asn1EncoderFragSize ? dz1Asn1EncoderFragSize : sz;
				if (_octet_str_tlv_enc(dst, descr->tag, cp, work_size, param, errp) == FALSE) ERR_OUT(errp);
				else
				{
					cp += work_size;
					sz -= work_size;
					Dz1Error_set(errp, 0);
				}
			}

			if (errp->code == 0)
			{
				if (_octet_str_tlv_enc(dst, descr->tag, cp, sz, param, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}

			*ret_is_constructed_form = TRUE;
		}
		else if (_octet_str_v_enc(dst, src->data, src->size, param, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			*ret_is_constructed_form = FALSE;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// Dz1Asn1BerDecoderDataCtx *dst, Dz1Asn1Stream *src, Dz1Asn1BerDecoderStk *stk, Dz1Asn1BerDecoder *decoder, void *param, Dz1Error *errp
ssize_t Dz1Asn1OctetStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1WipValue *wip = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End of Contents -> wip->x.octet_str = NULL
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{	// constructed form. length either soc or specific value
		Dz1Asn1TypeDescr *descr = NULL;
		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_octet_str, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
			else if ((wip->x.octet_str = Dz1ElasticBuf_new(1000, FALSE, errp)) == NULL) ERR_OUT(errp);
			else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
			else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);	// critical
			else if (wip->x.octet_str == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, descr, errp) == FALSE) ERR_OUT(errp);
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
				ssize_t sz = 0;
				Dz1Asn1WipValue *ret_data = NULL;
				Dz1ElasticBuf *ret_octets = NULL, *cur_octets = NULL;
				pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);

				dst->u64data += ret_stk->consumed;
				stk->consumed += ret_stk->consumed;

				if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (ret_data->present == Dz1Asn1WipValuePresent_max)
				{
					dst->state = Dz1Asn1BerDecoderDataState_max;	// return EOC -> End of Constructed Decoding
					ret = Dz1Asn1BerLength_ssoc;
				}
				else if (ret_data->present != Dz1Asn1WipValuePresent_octet_str) ERR_SET_OUT(errp, EFAULT);
				// resolve source data struct
				else if ((ret_octets = ret_data->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((cur_octets = wip->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
				// applying source data to destination data
				else if (Dz1ElasticBuf_move(cur_octets, ret_octets, errp) == FALSE) ERR_OUT(errp);
				else 
				{	// save some state
					if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)
					{
						if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, descr, errp) == FALSE) ERR_OUT(errp);
						else ret = Dz1Asn1BerLength_ssoc;
					}
					else if (stk->len == dst->u64data)
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						ret = Dz1Asn1BerLength_ssoc;
					}
					else
					{
						ERR_SET_OUT(errp, EFAULT); // size fault
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
	else if (stk->len == Dz1Asn1BerLength_soc) ERR_SET_OUT(errp, EPERM);	// length of primitive form can't be SOC
	else
	{	
		bool_t done = FALSE;

		ssize_t sz = 0;
		u8_t buf[1000];
		Dz1ElasticBuf *elb = NULL;
		u32_t copy_sz = 0;

		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< OCTETS : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if (0) { }
				// initialize destination data struct
				else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_octet_str, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
				else if ((wip->x.octet_str = Dz1ElasticBuf_new(1000, FALSE, errp)) == NULL) ERR_OUT(errp);
				else
				{
					dst->s32data = (s32_t)(stk->len & 0x7FFFFFFF);
					dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				}
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				copy_sz = dst->s32data > sizeof(buf) ? (u32_t)sizeof(buf) : (u32_t)dst->s32data;

				if (0) { }
				else if (dst->s32data == 0)
				{	// zero length octet string
					dst->state = Dz1Asn1BerDecoderDataState_max;
					done = TRUE;
					ret = Dz1Asn1BerLength_ssoc;
				}
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);				// critical
				else if (wip->present != Dz1Asn1WipValuePresent_octet_str) ERR_SET_OUT(errp, EFAULT);
				else if ((elb = wip->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);		// critical
				// read from STREAM
				else if ((sz = Dz1Asn1Stream_popOctets(src, buf, (u32_t)dst->s32data, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				// apply buffer to destination data struct
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
					dst->u32data += sz;

					if (dst->u32data == stk->len)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[E]");
						dst->state = Dz1Asn1BerDecoderDataState_max;
						done = TRUE;
					}
					else if (dst->u32data > stk->len) ERR_SET_OUT(errp, EFAULT); // size fault
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}

