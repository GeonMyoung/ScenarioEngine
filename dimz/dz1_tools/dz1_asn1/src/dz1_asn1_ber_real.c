#include <math.h>
#include "dz1_asn1_codec_ber.h"

/*
8.5		Encoding of a real value

8.5.1		The encoding of a real value shall be primitive.
			프리미티브 인코딩

8.5.2		If the real value is the value plus zero, there shall be no contents octets in the encoding.
			0.0f 값은 Data에 기록하지 않는다.

8.5.3		If the real value is the value minus zero, then it shall be encoded as specified in 8.5.9.
			-0.0f 값은 8.5.9에 지정한것 처럼 인코딩 해야한다.

8.5.4		For a non-zero real value, if the base of the abstract value is 10, then the base of the encoded value shall be 10, 
			and if the base of the abstract value is 2 the base of the encoded value shall be 2, 8 or 16 as a sender's option.
			0이아닌 실수값에 대해, Base 가 10인 값은 Base10 인코딩을 사용하여야 하고, Base 가 2인 값은 Base2, Base8 또는 Base16 인코딩
			중에 하나를 사용해야 한다. 어떤것을 사용할지는 전송측의 선택사항이다.

8.5.5		If the real value is non-zero, then the base used for the encoding shall be B' as specified in 8.5.4. If B' is 2, 8 or 16, 
			a binary encoding, specified in 8.5.7, shall be used. If B' is 10, a character encoding, specified in 8.5.8, shall be used.
			0이 아닌 실수값이라면, 8.5.4에 기술한 대로, B' 의 base 가 사용단다. 만약 B' 이 2, 8 또는 16이라면, 8.5.7의 방법을 따라야 한다.

8.5.6		Bit 8 of the first contents octet shall be set as follows:
			첫번째 옥텟의 Bit 8번은 다음에 따라 설정한다:

			a)	if bit 8 = 1, then the binary encoding specified in 8.5.7 applies;
				bit 8이 1이면 8.5.7에 기술한 바이너리 인코딩을 적용한다.
				-> 1xxx xxxx

			b)	if bit 8 = 0 and bit 7 = 0, then the decimal encoding specified in 8.5.8 applies;
				bit 8이 0이고 bit 7이 0이면 8.5.8에 기술한 10진 인코딩을 적용한다.
				-> 00xx xxxx

			c)	if bit 8 = 0 and bit 7 = 1, then either a "SpecialRealValue" (see Rec. ITU-T X.680 | ISO/IEC 8824 1) or  the value minus zero is encoded as specified in 8.5.9.
				bit 8이 0이고 bit 7이 1이면 "SpecialRealValue"(X.680 참조) 또는 -0.0f의 값을 8.5.9에 기술한대로 인코딩합니다.
				-> 01xx xxxx

8.5.7		When binary encoding is used (bit 8 = 1), then if the mantissa M is non-zero, 
			it shall be represented by a sign S, a positive integer value N and a binary scaling factor F, such that:
			바이너리 인코딩이 사용될 때(bit 8 = 1), 만티사 M 값이 0이 아니면,
			부호값 S, 양의 정수값 N 그리고 바이너리 스케일링 팩터 F 를 사용하여 다음과 같이 표현할 수 있다.
			
						M = S * N * 2^F
						S = +1 or -1
						0 <= F <= 4

			NOTE -	The binary scaling factor F is required under certain circumstances in order to align the implied point 
					of the mantissa to the position required by the encoding rules of this sub clause. 
					이 하위 절의 인코딩 규칙에 의해 요구되는 위치에 가수의 함축된 포인트를 정렬하기 위해 특정 상황에서 이진 스케일링 계수 F 가 필요합니다.

					This alignment cannot always be achieved by modification of the exponent E.
					이 정렬은 지수 E 의 수정으로 항상 달성될 수는 없습니다.

					If the base B' used for encoding is 8 or 16, the implied point can only be moved in steps of 3 or 4 bits, 
					respectively, by changing the component E.
					인코딩에 사용되는 기본 B' 가 8 또는 16인 경우 구성 요소 E 를 변경하여 함축 포인트를 각각 3비트 또는 4비트 단위로 이동할 수 있습니다.

					Therefore, values of the binary scaling factor F other than zero may be required in order to move 
					the implied point to the required position.
					따라서 함축된 점을 필요한 위치로 이동하기 위해 0이 아닌 이진 스케일링 계수 F 의 값이 필요할 수 있습니다.

8.5.7.1		Bit 7 of the first contents octets shall be 1 if S is -1 and 0 otherwise.
			첫번째 컨텐츠 옥텟의 Bit 7은 S 가 -1인 경우 1로 설정된다.
			-> 11xx xxxx

8.5.7.2		Bits 6 to 5 of the first contents octets shall encode the value of the base B' as follows:
			첫번째 컨텐츠 옥텟의 Bit 6과 5는 base B' 을 의미하며 다음을 따릅니다.
			-> --xx ----

						Bits 6 to 5		Base
						00				base 2
						01				base 8
						10				base 16
						11				Reserved for further editions of this Recommendation | International Standard.

8.5.7.3		Bits 4 to 3 of the first contents octet shall encode the value of the binary scaling factor F as an unsigned binary integer.
			첫번째 컨텐츠 옥텟의 Bit 4와 3은 F 값을 부호없는 2비트 정수로 인코딩하는데 사용됩니다.
			-> ---- xx--

8.5.7.4		Bits 2 to 1 of the first contents octet shall encode the format of the exponent as follows:
			첫번째 컨텐츠 옥텟의 Bit 2와 1은 다음과 같이 지수 형식을 인코딩해야 합니다.
			-> ---- --xx

			a)	if bits 2 to 1 are 00, then the second contents octet encodes the value of the exponent as a two's complement binary number;
				비트 2에서 1이 00이면 두 번째 내용 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
				-> ---- --00 => [1 Octet for Exponent Value]

			b)	if bits 2 to 1 are 01, then the second and third contents octets encode the value of the exponent as a two's complement binary number;
				비트 2에서 1이 01이면 두 번째 및 세 번째 내용 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
				-> ---- --01 => [2 Octet for Exponent Value]

			c)	if bits 2 to 1 are 10, then the second, third and fourth contents octets encode the value of the exponent as a two's complement binary number;
				비트 2에서 1이 10이면 두 번째, 세 번째 및 네 번째 내용 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
				-> ---- --10 => [3 Octet for Exponent Value]

			d)	if bits 2 to 1 are 11, then the second contents octet encodes the number of octets, X say, (as an unsigned binary number) used to 
				encode the value of the exponent, and the third up to the (X plus 3)th (inclusive) contents octets encode the value of the exponent 
				as a two's complement binary number; 
				비트 2 ~ 1이 11이면 두 번째 콘텐츠 옥텟은 지수 값을 인코딩하는 데 사용되는 옥텟의 수(X : 부호 없는 이진수)를 인코딩하고 세 번째 콘텐츠 옥텟은 
				(X + 3)번째(포함) 콘텐츠 옥텟까지 지수 값을 2의 보수 이진수로 인코딩합니다. 
				-> ---- --11 => <1 octet = number of octet = X> <n octet = exponent value>

				the value of X shall be at least one;
				X의 값은 적어도 1이어야 합니다.

				the first nine bits of the transmitted exponent shall not be all zeros or all ones.
				전송된 지수의 처음 9비트는 모두 0 또는 모두 1이 아니어야 합니다.

8.5.7.5			The remaining contents octets encode the value of the integer N (see 8.5.7) as an unsigned binary number.
				나머지 내용 옥텟은 정수 N(8.5.7 참조)의 값을 부호 없는 이진수로 인코딩합니다.

			NOTE 1 	For non-canonical BER there is no requirement for floating point normalization of the mantissa. This allows an implementer 
					to transmit octets containing the mantissa without performing shift functions on the mantissa in memory.
					비정규 BER의 경우 가수의 부동 소수점 정규화에 대한 요구 사항이 없습니다. 이를 통해 구현자는 메모리의 가수에 
					대해 시프트 기능을 수행하지 않고 가수를 포함하는 옥텟을 전송할 수 있습니다.

					In the Canonical Encoding Rules and the Distinguished Encoding Rules normalization is specified and the mantissa (unless it is 0) 
					needs to be repeatedly shifted until the least significant bit is a 1.
					Canonical Encoding Rules 및 Distinguished Encoding Rules에서는 정규화가 지정되고 가수(0이 아닌 경우)는 최하위 비트가 1이 될 때까지 반복적으로 이동해야 합니다.

			NOTE 2	This representation of real numbers is very different from the formats normally used in floating point hardware, 
					but has been designed to be easily converted to and from such formats (see Annex C).
					이 실수 표현은 부동 소수점 하드웨어에서 일반적으로 사용되는 형식과 매우 다르지만 이러한 형식으로 쉽게 변환할 수 있도록 설계되었습니다(부록 C 참조).

8.5.8			When decimal encoding is used (bits 8 to 7 = 00), all the contents octets following the first contents octet form a field, 
				as the term is used in ISO 6093, of a length chosen by the sender, and encoded according to ISO 6093. 
				10진수 인코딩이 사용되는 경우(비트 8 ~ 7 = 00), 첫 번째 콘텐츠 옥텟 다음에 오는 모든 콘텐츠 옥텟은 ISO 6093에서 
				사용되는 용어로 발신자가 선택하고 ISO 6093에 따라 인코딩된 길이의 필드를 형성합니다.

				The choice of ISO 6093 number representation is specified by bits 6 to 1 of the first contents octet as follows:
				ISO 6093 번호 표현의 선택은 다음과 같이 첫 번째 콘텐츠 옥텟의 비트 6에서 1로 지정됩니다.

						Bits 6 to 1		Number representation
						00 0001			ISO 6093 NR1 form
						00 0010			ISO 6093 NR2 form
						00 0011			ISO 6093 NR3 form

				The remaining values of bits 6 to 1 are reserved for further editions of this Recommendation | International Standard.
				비트 6에서 1의 나머지 값은 이 권장 표준의 추가 버전을 위해 예약되어 있습니다.

				There shall be no use of scaling factors specified in accompanying documentation (see ISO 6093).
				첨부 문서(ISO 6093 참조)에 지정된 배율 인수를 사용해서는 안 됩니다.

			NOTE 1	The recommendations in ISO 6093 concerning the use of at least one digit to the left of the decimal mark are also recommended 
					in this Recommendation | International Standard, but are not mandatory.
					ISO 6093에서 소수점 왼쪽에 있는 최소 한 자리 숫자의 사용에 관한 권장 사항은 이 권장 표준에서도 권장되지만 필수 사항은 아닙니다.

			NOTE 2	Use of the normalized form (see ISO 6093) is a sender's option, and has no significance.
					표준화된 형식의 사용(ISO 6093 참조)은 발신자의 선택사항이며 의미가 없습니다.

8.5.9			When "SpecialRealValues" or minus zero are to be encoded (bits 8 to 7 = 01), there shall be only one contents octet, with values as follows:
				"SpecialRealValues" 또는 마이너스 0이 인코딩되어야 하는 경우(비트 8 ~ 7 = 01) 다음과 같은 값을 갖는 콘텐츠 옥텟이 하나만 있어야 합니다.

						01000000	Value is PLUS-INFINITY
						01000001	Value is MINUS-INFINITY
						01000010	Value is NOT-A-NUMBER
						01000011	Value is minus zero
				All other values having bits 8 and 7 equal to 0 and 1 respectively are reserved for addenda to this Recommendation | International Standard.
				비트 8 및 7이 각각 0 및 1인 다른 모든 값은 이 권장 표준에 대한 부록을 위해 예약되어 있습니다.

11.3	Real values
11.3.1		If the encoding represents a real value whose base B is 2, then binary encoding employing base 2 shall be used. 
			encoding 된 값이 B 가 2인 실수 값을 표현 한다면 base 가 2인 바이너리 encoding 이 수행되어야 한다.

			Before encoding, the mantissa M and exponent E are chosen so that M is either 0 or is odd.
			encoding 전에, M 이 0이거나 홀수가 되는 M 과 E 값을 선택하여야 한다.

			NOTE -	This is necessary because the same real value can be regarded as both {M, 2, E} and {M', 2, E'} with M != M' if, for some non-zero integer n:
			이것은 동일한 실수 값이 0이 아닌 정수 n에 대해 M != M'인 {M, 2, E} 및 {M', 2, E'}로 간주될 수 있기 때문에 필요합니다.
			M' = M * 2^-n
			E' = E + n

			In encoding the value, the binary scaling factor F shall be zero, and M and E shall each be represented in the fewest octets necessary.
			값을 encoding 함에 있어, F 는 0으로, M 과 E 는 최소한의 Octet 으로 표현되어야 한다.

11.3.2		If the encoding represents a real value whose base B is 10, then decimal encoding shall be used.
			encoding 된 값이 B 가 10인 실수 값을 표현 한다면, 10진법의 encoding 이 사용된다.

			In forming the encoding, the following applies:
			encoding 형태는 다음과 같다:

11.3.2.1	The ISO 6093 NR3 form shall be used (see 8.5.8). 
			ISO-6093 NR3 형식이 사용된다.( 8.5.8 참조) (00 00 0011)

11.3.2.2	SPACE shall not be used within the encoding.
			encoding 내부에 SPACE는 사용되지 않는다.

11.3.2.3	If the real value is negative, then it shall begin with a MINUS SIGN (-), otherwise, it shall begin with a digit.
			실수 값이 음수이면 MINUS SIGN(-)으로 시작하고, 그렇지 않으면 숫자로 시작한다.

11.3.2.4	Neither the first nor the last digit of the mantissa may be a 0.
			M 값의 첫 번째와 마지막 숫자는 0이 될 수 없다.

11.3.2.5	The last digit in the mantissa shall be immediately followed by FULL STOP (.), followed by the exponent-mark "E".
			M 값의 마지막 숫자 뒤에 FULL STOP(.)이 오고 다음에 “E”가 붙는다.

11.3.2.6	If the exponent has the value 0, it shall be written "+0", otherwise the exponent's first digit shall not be zero, and PLUS SIGN shall not be used.
			E 값이 0이면 “+0”으로, 그렇지 않으면 0이 아닌 숫자로 시작하며, PLUX SIGN 은 사용하지 않는다.

			{integer number} {dot} {mantisa number} 'E' <'+0' |  <exponent number>

*/
static bool_t Dz1Asn1Real_enc_BER_binary(Dz1ElasticBuf *dst, Dz1Asn1Real value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t dvalue[sizeof(value)], *d = NULL;	// value of buf & control
	u8_t temp_buf[16], *pstr = temp_buf;	// finally buf
	s32_t exponent;

	u8_t first_encode_byte;

	u8_t *mstop = dvalue;					// last byte
	u8_t  vmstop;							// value of the last byte
	u8_t *s, *start = (u8_t *)&value;
	u32_t account = 0;
	u32_t buflen;							// value length

	double mantisa = frexp(value, &exponent);
	exponent -= 1;

	s = (u8_t *)&value + sizeof(value) - 2;
	first_encode_byte = 0x80 | ((s[1] >> 1) & 0x40);

	for (d = dvalue; s >= start; d++, s--)
	{
		*d = *s;
		if (*d) mstop = d;
	}

	//compute the first byte of value with 1
	dvalue[0] = 0x10 | (dvalue[0] & 0x0f);
	exponent -= 8 * (s32_t)(mstop - dvalue) + 4;

	//the last byte
	vmstop = *mstop;

	//compute finally exponent
	if ((vmstop & 1) == 0)
	{
		u8_t shift_count = 1;
		u8_t isshift;
		u8_t *mpstr;

		//compute the count of zero
		if ((vmstop & 0x0f) == 0) shift_count = 4;

		while(((vmstop >> shift_count) & 1) == 0) shift_count++;

		isshift = 8 - shift_count;	//missing part

		//move all value right
		for(mpstr = dvalue; mpstr <= mstop; mpstr++)
		{
			vmstop = *mpstr;
			*mpstr = account | (vmstop >> shift_count);
			account = vmstop << isshift;
		}
		exponent += shift_count;
	}
	
	//encode exponent
	if (exponent < 0) 
	{
		if ((exponent >> 7) == -1) 
		{
			*pstr++ = first_encode_byte | 0x00;
			*pstr++ = exponent;
		} 
		else if ((exponent >> 15) == -1) 
		{
			*pstr++ = first_encode_byte | 0x01;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		} 
		else 
		{
			*pstr++ = first_encode_byte | 0x02;
			*pstr++ = exponent >> 16;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		}
	} 
	else if (exponent <= 0x7f) 
	{
		*pstr++ = first_encode_byte | 0x00;
		*pstr++ = exponent;
	} 
	else if (exponent <= 0x7fff) 
	{
		*pstr++ = first_encode_byte | 0x01;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	} 
	else 
	{
		*pstr++ = first_encode_byte | 0x02;
		*pstr++ = exponent >> 16;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	}

	
	buflen = (u32_t)(mstop - dvalue) + 1;
	memcpy(pstr, dvalue, buflen);					// only copy value
	pstr += buflen;

	buflen = (u32_t)(pstr - temp_buf);
	if (_Dz1ElasticBuf_push(dst, temp_buf, buflen, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Real_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Real *src = (Dz1Asn1Real *)_src;

	*ret_is_constructed_form = FALSE;

	if (*src == 0.f) { /* no data to encode */ }
	else if (*src >= Dz1Asn1Real_plus_inf)
	{	// 0b01xx xxxx : 0b0100 0000
		u8_t v[] = { 0x40, 0x00 };
		if (_Dz1ElasticBuf_push(dst, v, sizeof(v), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (*src <= Dz1Asn1Real_minus_inf)
	{	// 0b01xx xxxx : 0b0100 0001
		u8_t v[] = { 0x40, 0x01 };
		if (_Dz1ElasticBuf_push(dst, v, sizeof(v), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (*src == Dz1Asn1Real_not_num)
	{	// 0b01xx xxxx : 0b0100 0010
		u8_t v[] = { 0x40, 0x02 };
		if (_Dz1ElasticBuf_push(dst, v, sizeof(v), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (*src == Dz1Asn1Real_minus_zero)
	{	// 0b01xx xxxx : 0b0100 0011
		u8_t v[] = { 0x40, 0x03 };
		if (_Dz1ElasticBuf_push(dst, v, sizeof(v), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
//		if (_is_binary_enc_mode)
		{	// 0b1xxx xxxx
			if (Dz1Asn1Real_enc_BER_binary(dst, *src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
// 		else if (_is_decimal_enc_mode)
// 		{	// 0b00xx xxxx : 0b0000 0011 : Forced NR3
// 		}
	}

	return errp->code == 0 ? TRUE : FALSE;
}

typedef enum BinaryBaseMode
{
	BinaryBaseMode_bin,
	BinaryBaseMode_oct,
	BinaryBaseMode_hex,
	BinaryBaseMode_reserved
} BinaryBaseMode;

typedef struct BinaryBaseModeStrMapA
{
	BinaryBaseMode				 mode;
	str_t						 str;
} BinaryBaseModeStrMapA;

static BinaryBaseModeStrMapA binaryBaseModeStrMapA[] =
{
	{ BinaryBaseMode_bin,		"bin" },
	{ BinaryBaseMode_oct,		"oct" },
	{ BinaryBaseMode_hex,		"hec" },
	{ BinaryBaseMode_reserved,	"reserved" },
	{ -1,						"unknown" }
};

static str_t BinaryBaseModeStrA(BinaryBaseMode mode)
{
	BinaryBaseModeStrMapA *i;
	for (i = binaryBaseModeStrMapA; i->mode != -1; i++)
		if (mode == i->mode) break;
	return i->str;
}

static s64_t _get_exponent_base(BinaryBaseMode mode, Dz1Error *errp)
{
	switch(mode)
	{
	case BinaryBaseMode_bin: return 1;
	case BinaryBaseMode_oct: return 3;
	case BinaryBaseMode_hex: return 4;
	case BinaryBaseMode_reserved:
	default:			return -1;
	}
}

typedef enum ExponentLengthMode
{
	ExponentLengthMode_single,
	ExponentLengthMode_duo,
	ExponentLengthMode_trinity,
	ExponentLengthMode_variable
} ExponentLengthMode;

typedef struct ExponentLengthModeStrMapA
{
	ExponentLengthMode			 mode;
	str_t						 str;
} ExponentLengthModeStrMapA;

static ExponentLengthModeStrMapA exponentLengthModeStrMapA[] =
{
	{ ExponentLengthMode_single,	"single" },
	{ ExponentLengthMode_duo,		"duo" },
	{ ExponentLengthMode_trinity,	"trinity" },
	{ ExponentLengthMode_variable,	"variable" },
	{ -1,							"unknown" }
};

static str_t ExponentLengthModeStrA(ExponentLengthMode mode)
{
	ExponentLengthModeStrMapA *i;
	for (i = exponentLengthModeStrMapA; i->mode != -1; i++)
		if (mode == i->mode) break;
	return i->str;
}

static bool_t _fetch_exponent(Dz1ElasticBuf *elb, ExponentLengthMode e_len_mode, s64_t *ret_exp, Dz1Error *errp)
{
	u8_t v;
	ssize_t sz;
	size_t len;
	switch(e_len_mode)
	{
	case ExponentLengthMode_single:		len = 1; break;	// 00이면 1개 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
	case ExponentLengthMode_duo:		len = 2; break;	// 01이면 2개 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
	case ExponentLengthMode_trinity:	len = 3; break;	// 10이면 3개 옥텟은 지수 값을 2의 보수 이진수로 인코딩합니다.
	case ExponentLengthMode_variable:					// 11이면 1개 옥텟은 지수 값 옥텟의 수(X : 부호 없는 이진수) 세 번째 에서 X개 옥텟까지 지수 값을 2의 보수 이진수로 인코딩합니다.
		if ((sz = Dz1ElasticBuf_pop(elb, &v, 1, errp)) < 0) ERR_OUT(errp);
		else if (sz != 1) ERR_SET_OUT(errp, EFAULT);
		else if (v > 8) ERR_SET_OUT(errp, EFAULT);
		else len = (size_t)v;
		break;
	}

	if (errp->code == 0)
	{
		u8_t buf[8];
		if ((sz = Dz1ElasticBuf_pop(elb, buf, len, errp)) < 0) ERR_OUT(errp);
		else if (sz != (ssize_t)len) ERR_SET_OUT(errp, EFAULT);
		else 
		{
			size_t i;
			(*ret_exp) = 0;
			if (buf[0] & 0x80) (*ret_exp) = -1;
			for (i = 0; i < len; i++) (*ret_exp) = ((*ret_exp) << 8) | ((s64_t)buf[i] & 0xFF);
		}
	}

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _fetch_nutural(Dz1ElasticBuf *elb, u64_t *ret_nutural, Dz1Error *errp)
{
	u8_t buf[16];
	ssize_t sz = 0;
	if ((sz = Dz1ElasticBuf_pop(elb, buf, 16, errp)) < 0) ERR_OUT(errp);
	else
	{
		ssize_t i;
		(*ret_nutural) = 0;
		for (i = 0; i < sz; i++)
			(*ret_nutural) = ((*ret_nutural) << 8) + buf[i];
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Real_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0, sz;
	bool_t done = FALSE;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)	ERR_SET_OUT(errp, EPERM);	// don't use constructed encoding
	else if (stk->len == Dz1Asn1BerLength_soc)			ERR_SET_OUT(errp, EPERM);	// don't use indefinite size
	else
	{
		u8_t buf[16];
		Dz1Asn1WipValue *wip = NULL;
		Dz1Asn1WipReal *wip_real = NULL;
		Dz1ElasticBuf *elb = NULL;
		u32_t copy_sz = 0;

		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< REAL : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if ((wip = dst->wip) == NULL && (wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_realnum, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((wip_real = wip->x.realnum) == NULL && (wip_real = wip->x.realnum = Dz1Asn1WipReal_new(NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((elb = wip_real->elb) == NULL && (elb = wip_real->elb = Dz1ElasticBuf_new(16, FALSE, errp)) == NULL) ERR_OUT(errp);
				else if (stk->len == 0)
				{	// 0.0f 값은 Data 에 기록하지 않는다.
					wip_real->value = 0.f;
					dst->state = Dz1Asn1BerDecoderDataState_max;
					done = TRUE;
				}
				else
				{
					dst->s32data = (s32_t)(stk->len & 0x7FFFFFFF);
					if ((sz = Dz1Asn1Stream_popOctet(src, &dst->u8data, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
					else
					{
						Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", dst->u8data);

						ret += sz;
						dst->u64data += sz;
						dst->s32data -= sz;

						if (dst->u8data & 0x80)
						{	// bit 8이 1이면 8.5.7에 기술한 바이너리 인코딩을 적용한다.
							dst->state = Dz1Asn1BerDecoderDataState_data_wait;
						}
						// 0??? ????
						else if (dst->u8data & 0x40)
						{	// 01?? ???? : bit 8이 0이고 bit 7이 1이면 8.5.9에 기술한 "SpecialRealValue" 또는 -0.0f 의 값을 인코딩한다.
							switch(dst->u8data & 0x3F)
							{
							case 0:	wip_real->value = Dz1Asn1Real_plus_inf;		dst->state = Dz1Asn1BerDecoderDataState_max; done = TRUE; break; // 000000	Value is PLUS-INFINITY
							case 1: wip_real->value = Dz1Asn1Real_minus_inf;	dst->state = Dz1Asn1BerDecoderDataState_max; done = TRUE; break; // 000001	Value is MINUS-INFINITY
							case 2: wip_real->value = Dz1Asn1Real_not_num;		dst->state = Dz1Asn1BerDecoderDataState_max; done = TRUE; break; // 000010	Value is NOT-A-NUMBER
							case 3: wip_real->value = Dz1Asn1Real_minus_zero;	dst->state = Dz1Asn1BerDecoderDataState_max; done = TRUE; break; // 000011	Value is minus zero
							default: ERR_SET_OUT(errp, EPERM);																			  break;
							}
						}
						else
						{	// 00?? ???? : bit 8이 0이고 bit 7이 0이면 8.5.8에 기술한 10진 인코딩을 적용한다.
							dst->state = Dz1Asn1BerDecoderDataState_data_wait;
						}
					}
				}
				break;
			case Dz1Asn1BerDecoderDataState_data_wait:
				copy_sz = dst->s32data > sizeof(buf) ? sizeof(buf) : (u32_t)dst->s32data;

				if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((wip_real = wip->x.realnum) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((elb = wip_real->elb) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((sz = Dz1Asn1Stream_popOctets(src, buf, copy_sz, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else
				{
					u32_t log_lv = 0;

					ret += sz;
					dst->u64data += sz;
					dst->s32data -= sz;

					Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
					if (log_lv & DZ1_THREAD_LOG_DEBUG)
					{
						ssize_t i;
						for (i = 0; i < sz; i++) Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", buf[i]);
					}

					if (_Dz1ElasticBuf_push(elb, buf, sz, errp) == FALSE) ERR_OUT(errp);
					else if (dst->u64data == stk->len)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
						if ((dst->u8data & 0xC0) == 0x00)
						{	// 00?? ???? : bit 8이 0이고 bit 7이 0이면 8.5.8에 기술한 10진 인코딩을 적용한다.
							Dz1Str nr123 = Dz1ElasticBuf_flattenStr(elb, errp);
							if (nr123 == NULL) ERR_SET_OUT(errp, EFAULT);
							else wip_real->value = Dz1StrToF(nr123);
						}
						else
						{	// 1??? ???? : bit 8이 1이면 8.5.7에 기술한 바이너리 인코딩을 적용한다.
							bool_t				m_is_minus = (dst->u8data & 0x40) ? TRUE : FALSE;		// Bit 7은 S 가 -1인 경우 1로 설정된다.

							u64_t				N = 0;
							s64_t				E = 0, B = 0;
							BinaryBaseMode		B_mode = (BinaryBaseMode)(dst->u8data & 0x30) >> 4;		// Bit 6과 5는 base B' 을 의미하며 다음을 따른다
							s64_t				F = (s64_t)((dst->u8data & 0x0C) >> 2);					// Bit 4와 3은 F 값을 부호없는 2비트 정수로 저장하는데 사용한다.
							ExponentLengthMode	E_len_mode = (ExponentLengthMode)(dst->u8data & 0x3);	// Bit 2와 1은 다음과 같이 지수 형식을 인코딩해야 합니다.

							if ((B = _get_exponent_base(B_mode, errp)) < 0) ERR_OUT(errp);
							else if (_fetch_exponent(elb, E_len_mode, &E, errp) == FALSE) ERR_OUT(errp);
							else if (_fetch_nutural(elb, &N, errp) == FALSE) ERR_OUT(errp);
							else
							{	// M = S * N * 2^F
								Dz1Thread_tlog(DZ1_THREAD_LOG_MESSAGE, stk->tab, "Dz1Asn1Real_dec_BER() : B Mode = %s(%d), E Length = %s(%d)\n",
																		BinaryBaseModeStrA(B_mode), B_mode,
																		ExponentLengthModeStrA(E_len_mode), E_len_mode);
								Dz1Thread_tlog(DZ1_THREAD_LOG_MESSAGE, stk->tab, "Dz1Asn1Real_dec_BER() : %cS * N(" DZ1_FMT64U_A ") * 2^F("DZ1_FMT64_A")\n", m_is_minus ? '-' : '+', N, F);
								wip_real->value = ldexp((Dz1Asn1Real)N, (int)(E * B + F));
								if (m_is_minus) wip_real->value = -wip_real->value;
							}
						}

						if (errp->code == 0)
						{
							dst->state = Dz1Asn1BerDecoderDataState_max;
							done = TRUE;
						}
					}
					else if (dst->u64data > stk->len) ERR_SET_OUT(errp, EFAULT); // size fault
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
	}
	return ret;
}

