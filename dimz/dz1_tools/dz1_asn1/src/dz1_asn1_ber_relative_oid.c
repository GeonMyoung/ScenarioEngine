#include "dz1_asn1_codec_ber.h"

/*
8.20	Encoding of a relative object identifier value
		NOTE -	The encoding of the object identifier components in a relative object identifier is 
				the same as the encoding of components (after the second) in an object identifier.
				RELATIVE-OID에서 객체 식별자 구성 요소의 인코딩은 OID에서 두 번째 이후 의 구성 요소 인코딩과 동일합니다.

8.20.1	The encoding of a relative object identifier value shall be primitive.
		RELATIVE-OID 값의 인코딩은 PRIMITIVE이어야 합니다.

8.20.2	The contents octets shall be an (ordered) list of encodings of sub-identifiers (see 8.20.3 and 8.20.4) concatenated together. 
		콘텐츠 옥텟은 함께 연결된 부 식별자(8.20.3 및 8.20.4 참조)의 인코딩(순서화된) 목록이어야 합니다.

		Each sub-identifier is represented as a series of (one or more) octets. 
		각 하위 식별자는 일련의 (하나 이상의) 옥텟으로 표시됩니다.

		Bit 8 of each octet indicates whether it is the last in the series: bit 8 of the last octet is zero; bit 8 of each preceding octet is one.
		각 옥텟의 비트 8은 이것이 시리즈의 마지막인지 여부를 나타냅니다. 마지막 옥텟의 비트 8은 0입니다. 각 이전 옥텟의 비트 8은 1입니다.

		Bits 7 1 of the octets in the series collectively encode the sub-identifier. 
		시리즈의 8진수 비트 7 - 1은 하위 식별자를 집합적으로 인코딩합니다.

		Conceptually, these groups of bits are concatenated to form an unsigned binary number whose most significant bit is bit 7 of the first octet 
		and whose least significant bit is bit 1 of the last octet.
		개념적으로, 이러한 비트 그룹은 연결되어 최상위 비트가 첫 번째 옥텟의 비트 7이고 최하위 비트가 마지막 옥텟의 비트 1인 부호 없는 이진수를 형성합니다.

		The sub-identifier shall be encoded in the fewest possible octets, that is, the leading octet of the sub-identifier shall not have the value 0x80.
		부 식별자는 가능한 가장 적은 수의 옥텟으로 인코딩되어야 합니다. 즉, 부 식별자의 선행 옥텟은 값 0x80을 갖지 않아야 합니다.

8.20.3	The number of sub-identifiers (N) shall be equal to the number of object identifier arcs in the relative object identifier value being encoded.
		부식별자(N)의 수는 인코딩되는 RELATIVE-OID 값의 객체 식별자 호의 수와 같아야 합니다.

8.20.4	The numerical value of the i th sub-identifier (1 <= i <= N) is that of the i th object identifier arc in the relative object identifier value being encoded.
		i 번째 부식별자(1 <= i <= N)의 숫자 값은 인코딩되는 RELATIVE-OID 값에서 i 번째 객체 식별자 arc의 값입니다.
*/
bool_t Dz1Asn1RelOID_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OID *src = (Dz1Asn1OID *)_src;

	*ret_is_constructed_form = FALSE;

	if (src->cnt == 0) { }
	else
	{
		u32_t i;
		for (i = 0; errp->code == 0 && i < src->cnt; i++)
		{
			if (Dz1Asn1_encOidArc(dst, (u64_t)src->data[i], errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#define _oid_arc		u32data
static bool_t _roid_apply(Dz1Asn1WipOid *oid, u8_t v, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
{
	dst->_oid_arc = (dst->_oid_arc << 7) + (v & 0x7F);		// take 7 bit

	if ((v & 0x80) == 0x00)
	{	// end of sub-identifier
		if (Dz1Asn1WipOid_append(oid, dst->_oid_arc, errp) == FALSE) ERR_OUT(errp);
		dst->_oid_arc = 0;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1RelOID_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)	ERR_SET_OUT(errp, EPERM);	// don't use constructed encoding
	else if (stk->len == Dz1Asn1BerLength_soc)			ERR_SET_OUT(errp, EPERM);	// don't use indefinite size
	else if (stk->len == 0)								ERR_SET_OUT(errp, EPERM);	// don't be 0 size
	else
	{
		u8_t v;
		ssize_t sz;
		bool_t done = FALSE;
		Dz1Asn1WipValue *wip = NULL;
		Dz1Asn1WipOid *oid = NULL;

		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< ROID : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if (0) { }
				// initialize destination data struct
				else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_oid, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((oid = wip->x.oid = Dz1Asn1WipOid_new(errp)) == NULL) ERR_OUT(errp);
				else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				if (0) { }
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (wip->present != Dz1Asn1WipValuePresent_oid) ERR_SET_OUT(errp, EFAULT);
				else if ((oid = wip->x.oid) == NULL) ERR_SET_OUT(errp, EFAULT);
				// read from STREAM
				else if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				// apply buffer to destination data struct
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);

					ret += sz;
					dst->u64data += sz;

					if (_roid_apply(oid, v, dst, errp) == FALSE) ERR_OUT(errp);
					else if (dst->u64data == stk->len)
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						done = TRUE;
					}
					else if (dst->u64data > stk->len) ERR_SET_OUT(errp, EFAULT); // size fault
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}

