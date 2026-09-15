#include "dz1_asn1_codec_ber.h"

/*
8.3		Encoding of an integer value
8.3.1	The encoding of an integer value shall be primitive. The contents octets shall consist of one or more octets.
		정수 값의 인코딩은 "Primitive"입니다. 콘텐츠 옥텟은 하나 이상의 옥텟으로 구성되어야 합니다.

8.3.2	If the contents octets of an integer value encoding consist of more than one octet, then the bits of the first octet and bit 8 of the second octet:
		정수 값 인코딩의 내용 옥텟이 둘 이상의 옥텟으로 구성된 경우 첫 번째 옥텟의 비트와 두 번째 옥텟의 비트 8(처음 9개 비트)은 다음과 같습니다.

		a)	shall not all be ones; and		-> 처음 9bit의 값은 모두 1일 수 없다.
		b)	shall not all be zero.			-> 처음 9bit의 값은 모두 0일 수 없다.

		NOTE -	These rules ensure that an integer value is always encoded in the smallest possible number of octets.
				이러한 규칙은 정수 값이 항상 가능한 가장 작은 수의 옥텟으로 인코딩되도록 합니다.

8.3.3	The contents octets shall be a two's complement binary number equal to the integer value, and consisting of bits 8 to 1 of the first octet,
		followed by bits 8 to 1 of the second octet, followed by bits 8 to 1 of each octet in turn up to and including the last octet of the contents octets.
		내용 옥텟은 정수 값과 동일한 2의 보수 이진수이어야 하며 첫 번째 옥텟의 비트 8~1, 두 번째 옥텟의 비트 8~1, 내용 옥텟의 마지막 옥텟까지 각 옥텟의 비트 8~1로 구성됩니다.

		NOTE -	The value of a two's complement binary number is derived by numbering the bits in the contents octets, starting with bit 1 of the last octet as 
				bit zero and ending the numbering with bit 8 of the first octet. 
				2의 보수 이진수 값은 마지막 옥텟의 비트 1을 0번으로 시작하여 첫 번째 옥텟의 비트 8까지의 데이터 옥텟 비트에 번호를 매겨 파생됩니다.
				각 비트에는 2^N 의 숫자 값이 할당됩니다. 여기서 N 은 위의 번호 지정 순서에 의한 위치(비트번호)입니다.

				Each bit is assigned a numerical value of 2^N, where N is its position in the above numbering sequence. The value of the two's complement binary 
				number is obtained by summing the numerical values assigned to each bit for those bits which are set to one, excluding bit 8 of the first octet, 
				and then reducing this value by the numerical value assigned to bit 8 of the first octet if that bit is set to one.
				2의 보수 이진수 값은 첫 번째 옥텟의 비트 8을 제외한 나머지 데이터 옥텟에 1로 설정된 비트에 대해 각 비트에 할당된 숫자(를 이용하여 2N 연산한) 값을 
				합산한 다음 첫 번째 옥텟의 비트 8이 1로 설정되면, 할당된 숫자 값만큼 이 값을 줄입니다.
*/

bool_t Dz1Asn1Int_enc_BER(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Int *src = (Dz1Asn1Int *)_src;

	u8_t buf[8] = { 0, };
	ssize_t sz = 0;

	if (0) { }
	else if ((sz = Dz1Asn1_2sComplementPacking(buf, 8, *src, errp)) < 0) ERR_OUT(errp);
	else if (_Dz1ElasticBuf_push(dst, buf, (size_t)sz, errp) == FALSE) ERR_OUT(errp);
	else
	{
		*ret_is_constructed_form = FALSE;
		Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

#define _do_minus		s32data
#define _is_first		u32data

ssize_t Dz1Asn1Int_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	u8_t v;
	ssize_t ret = 0, sz;
	bool_t done = FALSE;
	Dz1Asn1WipValue *wip = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)	ERR_SET_OUT(errp, EPERM);	// don't use constructed encoding
	else if (stk->len == Dz1Asn1BerLength_soc)			ERR_SET_OUT(errp, EPERM);	// don't use indefinite size
	else if (stk->len == 0)								ERR_SET_OUT(errp, EPERM);	// don't be 0 length contents octet
	else
	{
		Dz1Error_set(errp, 0);
		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< INT : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if ((dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_number, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					dst->_is_first = TRUE;
					dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				}
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);
					ret += sz;
					dst->u64data += sz;

					if (dst->_is_first)
					{	// fist
						if (v & 0x80) wip->x.number = -1;
 						dst->_is_first = FALSE;
					}

					wip->x.number = (wip->x.number << 8) | ((Dz1Asn1Int)v & 0xFF);

					if (dst->u64data == stk->len)
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						done = TRUE;
					}
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}

