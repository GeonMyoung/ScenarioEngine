#include "dz1_asn1_codec_per.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerRangeValue
typedef enum Dz1Asn1PerRangeValuePresent
{
	Dz1Asn1PerRangeValuePresent_undefined,
	Dz1Asn1PerRangeValuePresent_value,
	Dz1Asn1PerRangeValuePresent_max
} Dz1Asn1PerRangeValuePresent;

typedef struct Dz1Asn1PerRangeValue
{
	Dz1Asn1PerRangeValuePresent	 present;
	union
	{
		s64_t					 undefined;
		s64_t					 value;
	} x;
} Dz1Asn1PerRangeValue;
#define Dz1Asn1PerRangeValue_NULL		{ Dz1Asn1PerRangeValuePresent_undefined, { 0 } }

static void Dz1Asn1PerRangeValue_set(Dz1Asn1PerRangeValue *dst, Dz1Asn1Int v)
{
	if (dst != NULL)
	{
		dst->present = Dz1Asn1PerRangeValuePresent_value;
		dst->x.value = v;
	}
}

static void Dz1Asn1PerRangeValue_setLower(Dz1Asn1PerRangeValue *dst, Dz1Asn1Int v)
{
	if (dst != NULL)
	{
		if (dst->present != Dz1Asn1PerRangeValuePresent_value)
		{
			dst->present = Dz1Asn1PerRangeValuePresent_value;
			dst->x.value = v;
		}
		else if (v < dst->x.value) dst->x.value = v;
	}
}

static void Dz1Asn1PerRangeValue_setHigher(Dz1Asn1PerRangeValue *dst, Dz1Asn1Int v)
{
	if (dst != NULL)
	{
		if (dst->present != Dz1Asn1PerRangeValuePresent_value)
		{
			dst->present = Dz1Asn1PerRangeValuePresent_value;
			dst->x.value = v;
		}
		else if (v > dst->x.value) dst->x.value = v;
	}
}
// Dz1Asn1PerRangeValue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerVisibleRange
typedef struct Dz1Asn1PerVisibleRange
{
	Dz1Asn1PerRangeValue		 lb;
	Dz1Asn1PerRangeValue		 ub;
} Dz1Asn1PerVisibleRange;
#define Dz1Asn1PerVisivleRange_NULL		{ Dz1Asn1PerRangeValue_NULL, Dz1Asn1PerRangeValue_NULL }

static void Dz1Asn1PerVisibleRange_initFromRanges(Dz1Asn1PerVisibleRange *dst, Dz1Asn1MetaDataRangeInfo *src)
{
	u32_t idx ;
	Dz1Asn1MetaDataRange *i;
	for (i = src->arr, idx = 0; idx < src->cnt; i++, idx++)
	{
		Dz1Asn1PerRangeValue_setLower(&dst->lb, i->low);
		Dz1Asn1PerRangeValue_setHigher(&dst->ub, i->low);
	}
}

static bool_t Dz1Asn1PerVisibleRange_width(Dz1Asn1PerVisibleRange *r, u64_t *v)
{
	bool_t ret = FALSE;
	if (r == NULL || v == NULL) { }
	else if (r->lb.present != Dz1Asn1PerRangeValuePresent_value) { }
	else if (r->ub.present != Dz1Asn1PerRangeValuePresent_value) { }
	else { *v = (u64_t)(r->ub.x.value - r->lb.x.value + 1); ret = TRUE; }
	return ret;
}

typedef enum Dz1Asn1PerConsType
{
	Dz1Asn1PerConsType_none,
	Dz1Asn1PerConsType_semi,
	Dz1Asn1PerConsType_limited,
	Dz1Asn1PerConsType_full
} Dz1Asn1PerConsType;

static bool_t Dz1Asn1PerVisibleRange_type(Dz1Asn1PerVisibleRange *r, Dz1Asn1PerConsType *t)
{
	bool_t ret = FALSE;
	if (r == NULL || t == NULL) { }
	else
	{
		*t = Dz1Asn1PerConsType_none;
		if (r->lb.present == Dz1Asn1PerRangeValuePresent_value)
		{
			*t = Dz1Asn1PerConsType_semi;
			if (r->ub.present == Dz1Asn1PerRangeValuePresent_value)
				*t = Dz1Asn1PerConsType_full;
		}
		else if (r->ub.present == Dz1Asn1PerRangeValuePresent_value)
			*t = Dz1Asn1PerConsType_limited;
	}
	return ret;
}

// Dz1Asn1PerVisibleRange
///////////////////////////////////////////////////////////////////////////////

/*
13			Encoding the Integer type
			NOTE -	Ranges which allow the encoding of all values into one octet or less go into a minimun sized bit-field with no length count.
					모든 값을 한 옥텟 이하로 인코딩할 수 있는 범위는 길이 카운트 없이 최소 크기의 비트 필드로 됩니다.
					
					Ranges which allow encoding of all balues into two octets in an octet-aligned bit-field with no length count.
					모든 값을 두 개의 옥텟으로 인코딩할 수 있는 범위는 길이 카운트 없이 옥텟 정렬된 비트 필드의 두 개의 옥텟으로 됩니다. 
					
					Otherwise, the value is encoded into the minimum number of octets (using non-negative-binary-integer or 2's complement-binary-integer encoding as appropriate)
					and a length determinant is added.
					그렇지 않으면, 값은 최소 개수의 옥텟으로 인코딩 되고 (음이 아닌 이진 정수 또는 2의 보수 이진 정수의 인코딩) 길이 결정자가 추가 됩니다.
								   
					In this case, if the integer value can be encoded in less than 127 octets (as an offset from any lower bound that might be detemined), and there is no finite upper and lower bound,
					이 경우, 만약 127개 이하의 옥텟으로 인코딩 될 수 있는 정수 값이고 (결정될 수 있는 하한으로부터의 오프셋으로) 유한한 상한과 하한이 없다면,
					
					there is a one-octet length determinant,
					한 개의 octet의 길이 결정자를 가지고,

					else the length is encoded in the fewest number of bits needed.
					그렇지 않으면 길이가 필요한 최소 수의 비투 수로 인코딩 됩니다.
					
					Other cases are not of any practical interest, but are specified for completeness.
					기타 사례도 명시 되어 있습니다. (실질적 비중이 크진 않음)
					
13.1		If an extension marker is present in the constraint specification of the integer type, then a single bit shall be added 
			to the field-list in a bit-field of length one. The bit shall be set to 1 if the value to be encoded is not within the range 
			of the extension root, and zero otherwise. 
			정수 유형의 제약 스펙에 확장 마커가 존재하면, 비트 필드의 필드 목록에 길이 1의 단일 비트가 추가됩니다. 추가되는 1 비트의 값은 루트 범위에 속하지 
			않는 경우 1, 루트 범위에 속하는 경우면 0을 사용합니다. 
			
			In the former case, the value shall be added to the field-list as an unconstrained  integer value, 
			as specified in 13.2.4 to 13.2.6, completing this procedure. In the latter case, the value shall be 
			encoded as if the extension marker is not present.
			전자의 경우 (루트 범위에 속하지 않는 경우), unconstrained integer value로 13.2.4 ~ 13.2.6 절에 명시된 내용에 따라 비트 필드를 추가하고 
			이 절차를 완료합니다. 후자의 경우 (루트 범위에 속하는 경우), 확장 마커가 없는것과 동일하게 인코딩 됩니다.

13.2		If an extension marker is not present in the constraint specification of the integer type, then the following applies.
			정수 유형의 제약 스펙에 확장 마커가 존재하지 않는 경우, 다음 절차를 적용한다.

13.2.1		If PER-visible constraints restrict the integer value to a single value, then there shall be no addition to the field-list, 
			completing the procedures.
			만약 PER-visible 제약조건이 정수값을 단일 값으로 제한한다면, 필드 목록에 아무런 추가를 하지 않고 이 절차를 완료한다.

13.2.2		If PER-visible constraints restrict the integer value to be a constrained whole number,
			then it shall be converted to a field according to the procedures of 11.5 (encoding of a constrained whole number),
			and the procedures of 13.2.5 to 13.2.6 shall then be applied.
			만약 PER-visible 제약조건이 정수값을 constrained whole number로 제한한다면, (lb, ub 모두 주어지는 경우)
			11.5절(constraned whole number의 인코딩)의 절차에 따라 변환되고, 13.2.5 ~ 13.2.6절의 절차가 적용된다.

13.2.3		If PER-visible constraints restrict the integer value to be a semi-constrained whole number,
			then it shall be converted to a field according to the procedures of 11.7 (encoding of a semi-constrained whole number),
			and the procedures of 13.2.6 shall be then be applied.
			만약 PER-visible 제약조건이 정수값을 semi-constrained whole number로 제한한다면, (lb만 주어지는 경우)
			11.7절(semi-constrained whole number의 인코딩)의 절차에 따라 변환되고, 13.2.6절의 절차가 적용된다.

13.2.4		If PER-visible constraints do not restrict the integer to be either a constrained or semi-constrained whole number,
			then it shall be converted to a field according to the procedures of 11.8 (encoding of an unconstrained whole number),
			and the procedures of 13.2.6 shall then be applied.
			만약 PER-visible 제약조건이 정수값을 제한하지 않는다면,
			11.8절(unconstrained whole number의 인코딩)의 절차에 따라 변환되고, 13.2.6절의 절차가 적용된다.

13.2.5		If the procedures invoked to encode the integer value into a field did not produce indefinite length case (see 11.5.7.4 and 11.8.2),
			then that field shall be appended to the field-list completing these procedures.
			필드에 정수값을 인코딩하기 위한 절차에서 길이가 확정된 케이스를 생성하였다면 (11.5.7.4, 11.8.2절 참고) 
			필드 목록에 그 필드를 추가하고 이러한 절차를 완료한다.

13.2.6		Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append the field to the field-list preceded by one of the following:
			그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

			a)	A constrained length determinant "len" (as determined by 11.5.7.4) if PER-visible constraints restrict the type 
				with finite upper and lower bounds and, if the type is extensible, the value lies within the range of the extension root.
				유한한 상한과 하한의 범위가 모두 주어지고, 확장 가능하며 그 값이 확장 루트 범위의 값인 경우는
				A constrained length determinant "len" 사용 (11.5.7.4절에 의해 결정된)

				The lower bound "lb" used in the length determinant shall be 1,
				and the upper bound "ub" shall be the count of the number of octets required to hold the range of the integer value.
				하한은 길이 결정자 1을 사용하고, 상한은 range의 최대 값을 수용할 수 있는 최소 길이 값으로 설정한다.
			
			NOTE -	The encoding of the value "foo INTEGER (256 .. 1234567) ::= 256" would thus be encoded in the ALIGNED variant as 00xxxxxx00000000,
					where each 'x' represents a zero pad bit may or may not be present depending on where within the octet length occurs.
					"foo INTEGER (256 .. 1234567) ::= 256"의 값은 ALIGNED 변형의 경우 00xxxxxx00000000로 인코딩된다. 
					'x'는 옥텟 내에서 길이가 발생하는 위치에 따라 존재할수도 아닐수도 있다.
					-> (1234567 - 256 + 1) = 1234312, 1234312는 64K보다 큰 값임으로, minimum octet 변환하여 결과 값 0x00과 길이 1이 리턴 된다, 
					여기서 lb = 1, ub = 3, len = 1로 11.9에 넣으면 0(len - lb)으로 계산되고 길이 값은 1비트 길이의 0이 된다. 
					확장 마커 1비트 + 길이 1비트 = ‘0b00’임 ALIGNED는 Contents의 시작을 정렬된 위치에서 하도록 하기 때문에 ‘0b00’과 Contents사이에는 
					Padding이 생길 수 있다.

					(e.g., the encoding is 00 xxxxxx 000000 if the length starts on an octet boundary,
					and 00 00000000 if it starts with the two least significant bits (bits 2 and 1) of an octet)
					예를 들어, 만약 길이가 옥텟 경계에서 시작하면 인코딩은 00 xxxxxxx 00000000
					만약 옥텟의 최소 유효 2 비트에서 시작하면 (bit 2, 1) 인코딩은 00 00000000 이다.
					-> 길이를 표현하는 비트가 옥텟의 어디 지점에서 시작하는지에 따라 제로 패딩 비트가 존재여부를 결정함. (ALIGNED variant의 경우)
			
			b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) if PER-visible constraints 
				do not restrict the type with finite upper and lower bounds, or if the type is extensible and the value 
				does not lie within the range of the extension root.
				값의 범위를 제한하지 않거나, 
				확장이 가능하며 그 값이 확장 루트 범위의 값이 아닌 경우는
				unconstrained length determinant "len" 사용 (11.7 ~ 11.8절에 의해 결정된)
*/

static bool_t _is_extensible(Dz1Asn1TypeComformance *c, Dz1Asn1PerVisibleRange *r)
{
	bool_t ret = FALSE;
	Dz1Asn1Constraint *cons = NULL;
	Dz1Asn1MetaDataRangeInfo *rngs = NULL;
	if (c == NULL || (cons = c->cons) == NULL) { }
	else if ((rngs = cons->i_ranges) == NULL) { }
	else
	{
		ret = rngs->extensible;
		Dz1Asn1PerVisibleRange_initFromRanges(r, rngs);
	}
	return ret;
}

#if 0
static bool_t encode_13_2_6(Dz1Asn1Stream *dst, Dz1Asn1PerIntInfo *src, Dz1Asn1PerVisibleRange *r, bool_t is_ext, 
							Dz1Asn1PerEncoderArg *param, Dz1Error *errp)
{	// unconstrained, semi-constrained, extended(may constrained)
	u64_t width = 0;
/*
	a)	A constrained length determinant "len" (as determined by 11.5.7.4) if PER-visible constraints restrict the type 
		with finite upper and lower bounds and, if the type is extensible, the value lies within the range of the extension root.
		유한한 상한과 하한의 범위가 모두 주어지고, 확장 가능하며 그 값이 확장 루트 범위의 값인 경우는
		A constrained length determinant "len" 사용 (11.5.7.4절에 의해 결정된)

		The lower bound "lb" used in the length determinant shall be 1,
		and the upper bound "ub" shall be the count of the number of octets required to hold the range of the integer value.
		하한은 길이 결정자 1을 사용하고, 상한은 최대 값을 수용할 수 있는 최소 길이 값으로 설정한다.

		NOTE -	The encoding of the value "foo INTEGER (256 .. 1234567) ::= 256" would thus be encoded in the ALIGNED variant as 00xxxxxx00000000,
				where each 'x' represents a zero pad bit may or may not be present depending on where within the octet length occurs.
				"foo INTEGER (256 .. 1234567) ::= 256"의 값은 ALIGNED 변형의 경우 00xxxxxx00000000로 인코딩된다. 
				'x'는 옥텟 내에서 길이가 발생하는 위치에 따라 존재할수도 아닐수도 있다.
				-> (1234567 - 256 + 1) = 1234312, 1234312는 64K보다 큰 값임으로, minimum octet 변환하여 결과 값 0x00과 길이 1이 리턴 된다, 
				ub는 1234312를 담을 수 있는 최소 옥텟임으로 0x12 0xD5 0x88로 3옥텟이다.
				여기서 lb = 1, ub = 3, len = 1로 11.9에 넣으면 0(len - lb)으로 계산되고 길이 값은 1비트 길이의 0이 된다. 
				확장 마커 1비트 + 길이 1비트 = ‘0b00’임 ALIGNED는 Contents의 시작을 정렬된 위치에서 하도록 하기 때문에 ‘0b00’과 Contents사이에는 
				Padding이 생길 수 있다.

				(e.g., the encoding is 00 xxxxxx 000000 if the length starts on an octet boundary,
				and 00 00000000 if it starts with the two least significant bits (bits 2 and 1) of an octet)
				예를 들어, 만약 길이가 옥텟 경계에서 시작하면 인코딩은 00 xxxxxxx 00000000
				만약 옥텟의 최소 유효 2 비트에서 시작하면 (bit 2, 1) 인코딩은 00 00000000 이다.
				-> 길이를 표현하는 비트가 옥텟의 어디 지점에서 시작하는지에 따라 제로 패딩 비트가 존재여부를 결정함. (ALIGNED variant의 경우)
*/
	if (Dz1Asn1PerVisibleRange_width(r, &width) == TRUE && is_ext == FALSE)
	{	// 범위가 주어지고, 값이 Root Value인 경우
		ssize_t bit_sz = 0;
		Dz1Asn1PerIntInfo len = Dz1Asn1PerIntInfo_NULL;

		if ((bit_sz = Dz1Asn1CodecPer_nnbi(NULL, width, FALSE, errp)) < 0) ERR_OUT(errp);
		else if (Dz1Asn1CodecPer_mk_cwn(&len, (s64_t)src->size.x.indefinite, 1, bit_sz >> 3, param->mode, errp) == FALSE) ERR_OUT(errp);
		else if (len.size.present >= Dz1Asn1PerIntSizePresent_indefinite) ERR_SET_OUT(errp, EFAULT);
		else
		{
			Dz1Asn1PerIntSize *size = &len.size;
			switch(size->present)
			{
			case Dz1Asn1PerIntSizePresent_bits:
				if (0) { }
				else if (Dz1Asn1Stream_pushBitsI64(dst, len.value, size->x.bits, errp) == FALSE) ERR_OUT(errp);
				else if (param->mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
				else if (Dz1Asn1Stream_pushBitsI64(dst, src->value, src->size.x.indefinite << 3, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Asn1PerIntSizePresent_octet1:
				if (0) { }
				else if (Dz1Asn1Stream_pushBitsI64(dst, len.value, 8, errp) == FALSE) ERR_OUT(errp);
				else if (param->mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
				else if (Dz1Asn1Stream_pushBitsI64(dst, src->value, src->size.x.indefinite << 3, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Asn1PerIntSizePresent_octet2:
				if (0) { }
				else if (Dz1Asn1Stream_pushBitsI64(dst, len.value, 16, errp) == FALSE) ERR_OUT(errp);
				else if (param->mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
				else if (Dz1Asn1Stream_pushBitsI64(dst, src->value, src->size.x.indefinite << 3, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
	}

/*
	b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) if PER-visible constraints 
		do not restrict the type with finite upper and lower bounds, or if the type is extensible and the value 
		does not lie within the range of the extension root.
		값의 범위를 제한하지 않거나, 
		확장이 가능하며 그 값이 확장 루트 범위의 값이 아닌 경우는
		unconstrained length determinant "len" 사용 (11.7 ~ 11.8절에 의해 결정된)
*/
	else
	{	// 범위가 없거나, 확장 값인 경우, 암묵적으로 아무 제한이 없는 경우도 포함됨
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t encode_13_2_5__13_2_6(Dz1Asn1Stream *dst, Dz1Asn1PerIntInfo *src, Dz1Asn1PerVisibleRange *r, 
									bool_t can_ext, bool_t is_ext, Dz1Asn1PerEncoderArg *param, Dz1Error *errp)
{
	Dz1Asn1PerIntSize *size = &src->size;
	Dz1Asn1PerMode mode = src->mode != Dz1Asn1PerMode_max ? src->mode : param->mode;
	switch(size->present)
	{
/*
13.2.5		If the procedures invoked to encode the integer value into a field did not produce indefinite length case (see 11.5.7.4 and 11.8.2),
			then that field shall be appended to the field-list completing these procedures.
			필드에 정수값을 인코딩하기 위한 절차에서 길이가 정해지지 않은 케이스를 생성하지 않았다면 (11.5.7.4, 11.8.2절 참고)
			필드 목록에 그 필드를 추가하고 이러한 절차를 완료한다.
			-> 길이가 유한한 경우는, 인코딩 필드 목록에 필드를 이어 붙이고 모든 값을 다 이어 붙였으면 완료
*/
	case Dz1Asn1PerIntSizePresent_bits:
		if (Dz1Asn1Stream_pushBitsI64(dst, src->value, (s32_t)size->x.bits, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1PerIntSizePresent_octet1:
		if (mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1Stream_pushBitsI64(dst, src->value, 8, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1PerIntSizePresent_octet2:
		if (mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1Stream_pushBitsI64(dst, src->value, 16, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1PerIntSizePresent_indefinite:
		if (encode_13_2_6(dst, src, r, can_ext, is_ext, param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ERR_IS_SUCCESS(errp);
}
#endif

// 제약이 있지만, Root 값인 경우
static bool_t encode_cons_but_no_ext(Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, Dz1Asn1Int src,
									 Dz1Asn1PerVisibleRange *r, Dz1Asn1PerEncoderArg *param, Dz1Error *errp)
{
}

// 제약이 없거나, 확장 마커가 없는 경우, 
static bool_t encode_root_value(Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, Dz1Asn1Int src,
								Dz1Asn1PerVisibleRange *r, Dz1Asn1PerEncoderArg *param, Dz1Error *errp)
{
	Dz1Asn1PerConsType type = Dz1Asn1PerConsType_none;
	Dz1Asn1PerIntInfo tgt = Dz1Asn1PerIntInfo_NULL;
	if (0) { }
	else if (Dz1Asn1PerVisibleRange_type(r, &type) == FALSE)	// 제약 조건이 없는 경우
	{	/* 13.2.4
		If PER-visible constraints do not restrict the integer to be either a constrained or 
		semi-constrained whole number, then it shall be converted to a field according to the 
		procedures of 11.8 (encoding of an unconstrained whole number), and the procedures of 
		13.2.6 shall then be applied.
		만약 PER-visible 제약조건이 정수값을 제한하지 않는다면, 11.8절(unconstrained whole number 의 
		인코딩)의 절차에 따라 변환되고, 13.2.6절의 절차가 적용된다.

		13.2.6		
		Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append 
		the field to the field-list preceded by one of the following:
		그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

		b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) 
			if PER-visible constraints do not restrict the type with finite upper and lower bounds, 
			or if the type is extensible and the value does not lie within the range of the extension root.
			값의 범위를 제한하지 않거나, 확장이 가능하며 그 값이 루트 범위의 값인 경우는 unconstrained length 
			determinant "len" 사용 (11.7 ~ 11.8절에 의해 결정된) */
		if (Dz1Asn1CodecPer_mk_ucwn(&tgt, src, param->mode, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			Dz1Asn1PerIntSize *size = &tgt.size;
			switch(size->present)
			{	/* 13.2.6
				Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append the field to the 
				field-list preceded by one of the following:
				그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

				b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) if PER-visible 
					constraints do not restrict the type with finite upper and lower bounds, or if the type is extensible 
					and the value does not lie within the range of the extension root.
					값의 범위를 제한하지 않거나, 확장이 가능하며 그 값이 루트 범위의 값이 아닌 경우는 unconstrained length determinant 
					"len" 사용 (11.7 ~ 11.8절에 의해 결정된) */
			case Dz1Asn1PerIntSizePresent_indefinite:
				if ((sz = Dz1Asn1CodecPer_length_enc(dst, tgt.size.x.indefinite, 0, NULL, param->mode, errp)) < 0) ERR_OUT(errp);
				else if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, tgt.size.x.indefinite << 3, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;	// 그 이외의 케이스는 오류임
			}
		}
	}
	else
	{	// 제약 조건이 있는데. Root 값인 경우
		u64_t width = 0;
		switch(type)
		{
		case Dz1Asn1PerConsType_full:	// constrained
			/* 13.2.1
			If PER-visible constraints restrict the integer value to a single value, 
			then there shall be no addition to the field-list, completing the procedures.
			만약 PER-visible 제약조건이 정수값을 단일 값으로 제한한다면, 필드 목록에 아무런 추가를 
			하지 않고 이 절차를 완료한다. */
			if (Dz1Asn1PerVisibleRange_width(r, &width) == FALSE) ERR_SET_OUT(errp, EFAULT);
			else if (width == 1) Dz1Error_set(errp, 0);
			/* 13.2.2
			If PER-visible constraints restrict the integer value to be a constrained whole 
			number, then it shall be converted to a field according to the procedures of 11.5 
			(encoding of a constrained whole number), and the procedures of 13.2.5 to 13.2.6 
			shall then be applied.
			만약 PER-visible 제약조건이 정수값을 constrained whole number 로 제한한다면, (lb, ub 모두 
			주어지는 경우) 11.5절(constrained whole number 의 인코딩)의 절차에 따라 변환되고, 13.2.5 ~ 
			13.2.6절의 절차가 적용된다. */
			else if (Dz1Asn1CodecPer_mk_cwn(&tgt, src, r->lb.x.value, r->ub.x.value, param->mode, errp) == FALSE) ERR_OUT(errp);
			else
			{
				switch(tgt.size.present)
				{	/* 13.2.5
					If the procedures invoked to encode the integer value into a field did not 
					produce indefinite length case (see 11.5.7.4 and 11.8.2), then that field 
					shall be appended to the field-list completing these procedures.
					필드에 정수값을 인코딩하기 위한 절차에서 길이가 정해진 케이스를 생성하였다면 (11.5.7.4, 
					11.8.2절 참고) 필드 목록에 그 필드를 추가하고 이러한 절차를 완료한다.
					-> 길이가 유한한 경우는, 인코딩 필드 목록에 필드를 이어 붙이고 모든 값을 다 이어 붙였으면 완료 */
				case Dz1Asn1PerIntSizePresent_bits:
				case Dz1Asn1PerIntSizePresent_octet1:
				case Dz1Asn1PerIntSizePresent_octet2:
					break;
				case Dz1Asn1PerIntSizePresent_indefinite:
					/* 13.2.6
					Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked 
					to append the field to the field-list preceded by one of the following:
					그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 
					필드 목록에 추가한다.
					a)	A constrained length determinant "len" (as determined by 11.5.7.4) if PER-visible 
						constraints restrict the type with finite upper and lower bounds and, if the type 
						is extensible, the value lies within the range of the extension root.
						유한한 상한과 하한의 범위가 모두 주어지고, 확장 가능하며 그 값이 확장 루트 범위의 값인 경우는
						constrained length determinant "len" 사용 (11.5.7.4절에 의해 결정된)

						The lower bound "lb" used in the length determinant shall be 1, and the upper bound 
						"ub" shall be the count of the number of octets required to hold the range of the 
						integer value.
						하한은 길이 결정자 1을 사용하고, 상한은 range 의 최대 값을 수용할 수 있는 최소 길이 값으로 
						설정한다. */
					if (encode_13_2_6_a(dst, &tgt, param, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				default: ERR_SET_OUT(errp, EFAULT); break;
				}
			}
			break;
		case Dz1Asn1PerConsType_semi:	// semi-constrained == unconstrained
			/* 13.2.3
			If PER-visible constraints restrict the integer value to be a semi-constrained whole number,
			then it shall be converted to a field according to the procedures of 11.7 (encoding of a 
			semi-constrained whole number), and the procedures of 13.2.6 shall be then be applied.
			만약 PER-visible 제약조건이 정수값을 semi-constrained whole number 로 제한한다면, (lb 만 주어지는 경우)
			11.7절(semi-constrained whole number 의 인코딩)의 절차에 따라 변환되고, 13.2.6절의 절차가 적용된다.

			13.2.6
			Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append the 
			field to the field-list preceded by one of the following:
			그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

			b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) 
				if PER-visible constraints do not restrict the type with finite upper and lower bounds, 
				or if the type is extensible and the value does not lie within the range of the extension root.
				값의 범위를 제한하지 않거나, 확장이 가능하며 그 값이 확장 루트 범위의 값이 아닌 경우는
				unconstrained length determinant "len" 사용 (11.7 ~ 11.8절에 의해 결정된) */
			if (Dz1Asn1CodecPer_mk_scwn(&tgt, src, r->lb.x.value, param->mode, errp) == FALSE) ERR_OUT(errp);
			else if (encode_13_2_6_b(dst, &tgt, param, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			/* 13.2.4
			If PER-visible constraints do not restrict the integer to be either a constrained or semi-constrained 
			whole number, then it shall be converted to a field according to the procedures of 11.8 (encoding of 
			an unconstrained whole number), and the procedures of 13.2.6 shall then be applied.
			만약 PER-visible 제약조건이 정수값을 제한하지 않는다면, 11.8절(unconstrained whole number 의 인코딩)의 절차에 
			따라 변환되고, 13.2.6절의 절차가 적용된다.

			13.2.6
			Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append the field to 
			the field-list preceded by one of the following:
			그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

			b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) if PER-visible constraints 
				do not restrict the type with finite upper and lower bounds, or if the type is extensible and the value 
				does not lie within the range of the extension root.
				값의 범위를 제한하지 않거나, 확장이 가능하며 그 값이 확장 루트 범위의 값이 아닌 경우는
				unconstrained length determinant "len" 사용 (11.7 ~ 11.8절에 의해 결정된) */
			if (Dz1Asn1CodecPer_mk_ucwn(&tgt, src, param->mode, errp) == FALSE) ERR_OUT(errp);
			else if (encode_13_2_6_b(dst, &tgt, param, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1Asn1Int_enc_PER(Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, void *_src, Dz1Asn1PerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	bool_t is_ext = FALSE;
	Dz1Asn1Int *src = (Dz1Asn1Int *)_src;
	Dz1Asn1PerVisibleRange range = Dz1Asn1PerVisivleRange_NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1TypeDescr_chkConformance(descr, _src, &is_ext) == FALSE) ERR_SET_OUT(errp, EPERM);
	else if (_is_extensible(descr->conformance, &range) == TRUE)	// extensible
	{	/* 13.1
		If an extension marker is present in the constraint specification of the integer type, then a single bit shall be added 
		to the field-list in a bit-field of length one. The bit shall be set to 1 if the value to be encoded is not within the range 
		of the extension root, and zero otherwise. 
		정수 유형의 제약 스펙에 확장 마커가 존재하면, 비트 필드의 필드 목록에 길이 1의 단일 비트가 추가됩니다. 추가되는 1 비트의 값은 루트 범위에 속하지 
		않는 경우 1, 루트 범위에 속하는 경우면 0을 사용합니다.

		In the former case, the value shall be added to the field-list as an unconstrained  integer value, 
		as specified in 13.2.4 to 13.2.6, completing this procedure. In the latter case, the value shall be 
		encoded as if the extension marker is not present.
		전자의 경우 (루트 범위에 속하지 않는 경우), 13.2.4 ~ 13.2.6 절에 명시된 내용에 따라 unconstrained integer value 로 변환한 비트 필드를 추가하고 
		이 절차를 완료합니다. 후자의 경우 (루트 범위에 속하는 경우), 확장 마커가 없는것과 동일하게 인코딩 됩니다. */
		if (Dz1Asn1Stream_pushBit1(dst, is_ext, errp) == FALSE) ERR_OUT(errp);
		else if (is_ext)	// Extended Value
		{	/* 13.2.4
			If PER-visible constraints do not restrict the integer to be either a constrained or 
			semi-constrained whole number, then it shall be converted to a field according to the 
			procedures of 11.8 (encoding of an unconstrained whole number), and the procedures of 
			13.2.6 shall then be applied.
			만약 PER-visible 제약조건이 정수값을 제한하지 않는다면, 11.8절(unconstrained whole number 의 
			인코딩)의 절차에 따라 변환되고, 13.2.6절의 절차가 적용된다. */
			Dz1Asn1PerIntInfo tgt = Dz1Asn1PerIntInfo_NULL;
			if (Dz1Asn1CodecPer_mk_ucwn(&tgt, *src, errp) == FALSE) ERR_OUT(errp);
			else
			{
				ssize_t sz = 0;
				Dz1Asn1PerIntSize *size = &tgt.size;
				switch(size->present)
				{	/* 13.2.6
					Otherwise, (the indefinite length case) the procedures of 11.9 shall be invoked to append the field to the 
					field-list preceded by one of the following:
					그 외의 경우, (길이가 정해지지 않은 경우) 다음중 한가지로 11.9 절차를 수행하여 길이 값을 필드 목록에 추가한다.

					b)	An unconstrained length determinant equal to 'len" (as determined by 11.7 and 11.8) if PER-visible 
						constraints do not restrict the type with finite upper and lower bounds, or if the type is extensible 
						and the value does not lie within the range of the extension root.
						값의 범위를 제한하지 않거나, 확장이 가능하며 그 값이 루트 범위의 값이 아닌 경우는 unconstrained length determinant 
						"len" 사용 (11.7 ~ 11.8절에 의해 결정된) */
				case Dz1Asn1PerIntSizePresent_indefinite:
					if ((sz = Dz1Asn1CodecPer_length_enc(dst, tgt.size.x.indefinite, 0, NULL, param->mode, errp)) < 0) ERR_OUT(errp);
					else if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, tgt.size.x.indefinite << 3, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				default: ERR_SET_OUT(errp, EFAULT); break;	// 그 이외의 케이스는 오류임
				}
			}
		}
		// Root Value -> 확장 마커가 없는것과 동일하게 인코딩 됩니다.
		else if (encode_root_value(dst, descr, *src, &range, param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{	// none-extensible -> Root Value
		if (encode_root_value(dst, descr, *src, &range, param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

