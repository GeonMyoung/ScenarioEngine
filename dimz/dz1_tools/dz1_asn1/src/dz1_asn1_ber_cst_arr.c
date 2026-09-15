#include "dz1_asn1_codec_ber.h"

/*
### X.680
26		Notation for sequence-of types

26.1	The notation for defining a sequence-of type (see 3.8.68) from another type shall be the "SequenceOfType".
		다른 유형에서 SEQUENCE-OF 유형(3.8.68 참조)을 정의하기 위한 표기법을 "SequenceOfType"이라 합니다.

			SequenceOfType ::= SEQUENCE OF Type | SEQUENCE OF NamedType

		NOTE -	If an initial letter which is upper-case is needed for an XML tag name used in XML Value Notation for the "SequenceOfType", 
				then the first alternative  should be used.  (The XML tag name is then formed from the name of the "Type".)
				"SequenceOfType"에 대한 XML 값 표기법에서 사용되는 XML 태그 이름에 대문자인 초기 문자가 필요한 경우 첫 번째 대안을 사용해야 합니다.
				(XML 태그 이름은 "Type"의 이름으로 구성됩니다.)

26.2	All sequence-of types have a tag which is universal class, number 16.
		모든 SEQUENCE-OF 유형에는 UNIVERSAL 클래스 번호 16인 태그가 있습니다.

		NOTE -	Sequence types have the same tag as sequence-of types (see 25.17)
				SEQUENCE 유형은 SEQUENCE-OF 유형과 동일한 태그를 갖습니다(25.17 참조).

28		Notation for set-of types

28.1	The notation for defining a set-of type (see 3.8.73) from another type shall be the "SetOfType":
		다른 유형에서 SET-OF 유형(3.8.73 참조)을 정의하기 위한 표기법을 "SetOfType"이라 합니다.

			SetOfType ::=
				SET OF  Type
			|	SET OF  NamedType

		NOTE -	If an initial letter which is upper-case is needed for an XML tag name used in XML Value Notation for the "SetOfType", 
				then the first alternative should be used. (The XML tag name is then formed from the name of the "Type".)
				"SetOfType"에 대한 XML 값 표기법에서 사용되는 XML 태그 이름에 대문자인 초기 문자가 필요한 경우 첫 번째 대안을 사용해야 합니다.
				(XML 태그 이름은 "Type"의 이름으로 구성됩니다.)

28.2	All set-of types have a tag which is universal class, number 17.
		모든 SET-OF 유형에는 UNIVERSAL 클래스 번호 17인 태그가 있습니다.

		NOTE -	Set types have the same tag as set-of types (see 27.5).
				SET 유형은 SET-OF 유형과 동일한 태그를 갖습니다(27.5 참조).

### X.690
8.10	Encoding of a sequence-of value

8.10.1	The encoding of a sequence-of value shall be constructed.
		SEQUENCE-OF 값의 인코딩은 constructed 여야 합니다.

8.10.2	The contents octets shall consist of zero, one or more complete encodings of data values from the type listed in the ASN.1 definition.
		내용 옥텟은 ASN.1 정의에 나열된 유형의 데이터 값에 대한 0개 이상의 완전한 인코딩으로 구성되어야 합니다.

8.10.3	The order of the encodings of the data values shall be the same as the order of the data values in the sequence of value to be encoded.
		데이터 값의 인코딩 순서는 인코딩될 값 시퀀스의 데이터 값 순서와 동일해야 합니다.


8.12	Encoding of a set-of value

8.12.1	The encoding of a set-of value shall be constructed.
		SET OF 값의 인코딩은 constructed 여야 합니다.

8.12.2	The text of 8.10.2 applies.
		내용 옥텟은 ASN.1 정의에 나열된 유형의 데이터 값에 대한 0개 이상의 완전한 인코딩으로 구성되어야 합니다.

8.12.3	The order of data values need not be preserved by the encoding and subsequent decoding.
		데이터 값의 순서는 인코딩 및 후속 디코딩에 의해 보존될 필요가 없습니다.


11.6	Set of components
		The encodings of the component values of a set-of value shall appear in ascending order, 
		the encodings being compared as octet strings with the shorter components being padded at their trailing end with 0-octets.
		SET-OF 값의 구성 요소 값의 인코딩은 오름차순으로 나타나야 하며 인코딩은 8진수 문자열로 비교되며 더 짧은 구성 요소는 후미에 0 옥텟으로 채워집니다.

		NOTE -	The padding octets are for comparison purposes only and do not appear in the encodings.
				패딩 옥텟은 비교 목적으로만 사용되며 인코딩에는 표시되지 않습니다.
*/

typedef struct Dz1Asn1ListEnvArg
{
	Dz1ElasticBuf				*dst;
	Dz1Asn1TypeDescrChild		*child;
	Dz1Asn1BerEncoderArg		*param;

	u32_t						 enc_cnt;
} Dz1Asn1ListEnvArg;
static Dz1Asn1ListTravelRet _Dz1Asn1Array_enc_BER(void *ptr, void *_src, Dz1Error *errp)
{
	Dz1Asn1ListEnvArg *arg = (Dz1Asn1ListEnvArg *)ptr;
	Dz1Asn1TypeDescrChild *child = arg->child;
	bool_t is_constructed = FALSE;
	if (Dz1Asn1BerDecoderDataCtx_enc_child(arg->dst, child, child->descr, _src, NULL, &is_constructed, arg->param, errp) == FALSE) ERR_OUT(errp);
	else
	{
		arg->enc_cnt++;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? Dz1Asn1ListTravelRet_no_issue : Dz1Asn1ListTravelRet_error;
}
// Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err
bool_t Dz1Asn1Array_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	int idx = 0;
	void *child_ptr = NULL;

	Dz1Asn1ListTravelRet status = Dz1Asn1ListTravelRet_no_issue;

	Dz1Asn1List *list = (Dz1Asn1List *)_src;
	Dz1Asn1ListEnvArg arg = { dst, descr->childs, param, 0 };
	if ((status = list->travel(list, TRUE, _Dz1Asn1Array_enc_BER, (void *)&arg, errp)) < Dz1Asn1ListTravelRet_no_issue) ERR_OUT(errp);
	else if (status > Dz1Asn1ListTravelRet_no_issue) ERR_SET_OUT(errp, EINTR);
	else
	{
		*ret_is_constructed_form = TRUE;
		Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1SequenceOf_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1Asn1Array_enc_BER(Dz1Asn1BerEncoder_contentsEncParams) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1SetOf_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1Asn1Array_enc_BER(Dz1Asn1BerEncoder_contentsEncParams) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _array_child_apply(Dz1Asn1WipValue *wip, Dz1Asn1BerDecoderStk *ret_stk, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
{
	Dz1Asn1WipCst *wip_seq = NULL;

	Dz1Asn1WipValue *ret_data = NULL;

	if (wip->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((wip_seq = wip->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Asn1TypeDescrChild *child = NULL;

		dst->s32data++;

		if ((child = ret_stk->child) == NULL)
		{	// unknown element TAG
			if (ret_data->present != Dz1Asn1WipValuePresent_any) ERR_SET_OUT(errp, EFAULT);
			else if (_Dz1Asn1WipOpenTypeList_addOpenType(wip_seq->unknowns, (u32_t)dst->s32data, &ret_data->x.any, errp) == FALSE) ERR_OUT(errp);
		}
		else
		{	// known element TAG
			Dz1Asn1Custom *wip_sto = NULL;
			if (0) { }
			else if ((wip_sto = wip_seq->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if (wip_sto->data == NULL)					ERR_SET_OUT(errp, EFAULT);
			else if (child->apply_data(wip, child->descr, ret_data, (u32_t)dst->s32data, errp) == FALSE) ERR_OUT(errp);		// apply data
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static ssize_t Dz1Asn1BerDecoderDataCtx_dec_arr(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1TypeDescr *descr = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{	// constructed form, length is SOC or some value
		Dz1Asn1WipValue *wip = NULL;
		Dz1Asn1WipCst *wip_seq = NULL;
		Dz1Asn1Custom *wip_sto = NULL;
		Dz1Asn1TypeDescr *indirect = NULL;

		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_cst_seq, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
			else if ((wip_seq = wip->x.cst_seq = Dz1Asn1WipCst_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((wip_sto = wip_seq->storage = Dz1Asn1TypeDescr_genWipCustom(descr, errp)) == NULL) ERR_OUT(errp);
			else if ((indirect = wip_seq->indirect = Dz1Asn1TypeDescr_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				indirect->childs = descr->childs;
				indirect->ber_dec = Dz1Asn1BerDecoderDataCtx_dec_indirect;

				dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			}
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (stk->len == 0)
			{	// empty array
				dst->state = Dz1Asn1BerDecoderDataState_max;
				ret = Dz1Asn1BerLength_ssoc;
			}
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
			else if ((wip_seq = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if ((wip_sto = wip_seq->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if (wip_sto->data == NULL)					ERR_SET_OUT(errp, EFAULT);
			else if (wip_seq->indirect == NULL)				ERR_SET_OUT(errp, EFAULT);
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_seq->indirect, errp) == FALSE) ERR_OUT(errp);
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
				Dz1Asn1WipValue *ret_data = NULL;
				pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);

				dst->u64data += ret_stk->consumed;
				stk->consumed += ret_stk->consumed;
				

				if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (ret_data->present == Dz1Asn1WipValuePresent_max)
				{	// return EOC -> End of Constructed Decoding
					dst->state = Dz1Asn1BerDecoderDataState_max;
					ret = Dz1Asn1BerLength_ssoc;
				}
				else
				{	// return DATA
					if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if (_array_child_apply(wip, ret_stk, dst, errp) == FALSE) ERR_OUT(errp);
					else if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)	// SOC or not reach to end
					{	// Array decoder always call child decoder with EXPLICIT
						if ((wip_seq = wip->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (wip_seq->indirect == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_seq->indirect, errp) == FALSE) ERR_OUT(errp);
						else ret = Dz1Asn1BerLength_ssoc;
					}
					else if (dst->u64data == stk->len)	// reach to END
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						ret = Dz1Asn1BerLength_ssoc;
					}
					else ERR_SET_OUT(errp, EFAULT); // count fault
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	else ERR_SET_OUT(errp, EPERM);		// *-OF can't be primitive
	return errp->code == 0 ? ret : -1;
}

ssize_t Dz1Asn1SequenceOf_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs) { return Dz1Asn1BerDecoderDataCtx_dec_arr(Dz1Asn1BerDecoderDataCtx_dec_params); } // SEQUENCE-OF
ssize_t Dz1Asn1SetOf_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs) { return Dz1Asn1BerDecoderDataCtx_dec_arr(Dz1Asn1BerDecoderDataCtx_dec_params); } // SET-OF
