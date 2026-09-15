#include "dz1_asn1_codec_per.h"

/*
11.3		Encoding as a non-negative-binary-number
			
			NOTE - This subclause gives precision to the term 'non-negative-binary-integer encoding", putting the integer into a field which is a fixed number of bits,
				   a field which is a fixed number of octets, or a field that is the minimum number of octets needed to hold it.
				   이 하위절은 고정된 bit, octet들의 수 또는 필드를 유지하는데 필요한 최소 개수인 정수를 필드에 넣어,
				   'non-negative-binary-integer encoding"이라는 용어에 정확성을 부여한다.

11.3.1		Subsequent subclauses refer to the generation of a non-negative-binary-integer encoding of a non-negative whole number into a field
			which is either a bit-field of specified length, a single octet, a double octet, or the minimum number of octets for the value.
			후속 하위절들은 length, single octet, double octet 또는 value에 대한 최소 수의 octet들의 bit-field인 필드 안에 음이아닌 정수의 
			non-negative-binary-integer 인코딩의 생성을 나타낸다.

			This subclause (11.3) specifies the precise encoding to be applied when such references are made.
			11.3 절은 이러한 참조들 (length, single octet, double octet, minimum number of octets)이 생성될 때 적용되는 정확한 인코딩 방법을 정의한다.

11.3.2		The leading bit of the field is defined as the leading bit of the bit-field, or as the most significant bit of the fiest octet in the field,
			and the trailing bit of the field is defined as the trailing bit of the bit-field or as the least significant bit of the last octet in the field.
			필드의 선행 비트는 비트 필드의 선행 비트 또는 필드의 첫번째 옥텟의 최상위 비트로 정의된다.
			필드의 후행 비트는 비트 필드의 후행 비트 또는 필드의 마지막 옥텟의 최하위 비트로 정의된다.
			> 필드의 leading bit = 첫번째 octet의 MSB, trailding bit = 마지막 octet의 LSB

11.3.3		For the following definition only, the bits shall be numbered zero for the trailing bit of the field, one for the next bit, and so up to the leading bit of the field.
			하위 정의에 한하여, 필드의 trailing bit를 0번, 다음 비트가 1번으로 하여 leading bit까지 번호가 부여된다.

11.3.4		In a non-negative-binary-integer encoding, the value of the whole number represented by the encoding shall be the sum of the values specified by each bit.
			non-negative-binary-integer encoding에서, 인코딩이 표현하는 정수의 값은 각 비트 값의 합이된다.

			A bit which is set to "0" has zero value. A bit with number "n" which is set to "1" has the value 2^n.
			"0"으로 설정된 bit는 0 값을 가지고, "1"로 설정되어 있는 "n"번 비트는 2^n의 값을 가진다.

11.3.5		The encoding which sums (as defined above) to the value being encoded is an encoding of that value.
			위에 정의된 합산 값의 인코딩은 그 값에 대한 인코딩이다.

			NOTE - Where the size of the encoded field is fixed (a bit-field of specified length, a single octet or a double octet),
				   then there is a unique encoding which sums to the value being encoded.
				   인코딩 되는 필드의 크기가 고정인 경우 (length 비트필드, 단일 옥텟, 이중 옥텟), 인코딩 되는 값에 더해지는 고유한 인코딩이 있다.

11.3.6		A minimum octet non-negative-binary-integer encoding of the whole number (which does not predetermine the number of octets to be used for the encoding)
			has a field which is a multiple of eight bits and also satisfies the condition that the leading eight bits of the field shall not all be zero
			unless the field is precisely eight bits long.
			인코딩에 사용되는 옥텟의 수를 미리 정해놓지 않은 경우, 정수의 최소 길이 octet의 non-negative-binary-integer 인코딩은 8의 배수의 크기의 비트의 수를 가지고
			또한 정확히 8비트가 아닌한 필드의 선행 8개의 비트가 전부 0이 아니어야 하는 조건을 만족한다.

			NOTE - This is a necessary and sufficient condition to produce a unique encoding.
				   이 사항은 고유한 인코딩을 생성하는 필요 충분 조건이다.
*/
ssize_t Dz1Asn1CodecPer_nnbi(u64_t *dst, u64_t src, bool_t mode_bits, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0, i = 0;
	ssize_t ret = 0;

	if (src == 0)
	{
		*dst = 0;
		ret = 8;
	}
	else if (mode_bits)
	{
		cnt = sizeof(u64_t) * 8;
		ret = sizeof(u64_t) * 8;

		while((src & DZ1UINT64(0x8000000000000000)) == 0) { src <<= 1; ret--; }
		if (dst != NULL) *dst = src >> (cnt - ret);
	}
	else
	{
		cnt = sizeof(u64_t);
		ret = sizeof(u64_t);

		while((src & DZ1UINT64(0xFF00000000000000)) == 0) { src <<= 8; cnt--; }
		if (dst != NULL) *dst = src >> ((cnt - ret) * 8);
		ret *= 8;
	}
	return errp->code == 0 ? ret : -1;
}

/*
11.4		Encoding as a 2's-complement-binary-integer
			NOTE - This subclause give precision to the term "2's-complement-binary-integer encoding", putting a signed integer into a field that is the minimum number of octets hold it.
				   이 하위절은 필드를 유지하는데 필요한 최소 개수의 부호를 가진 정수 octet을 필드에 넣어
				   "2's-complement-binary-integer encoding" 이라는 용어에 정확성을 부여한다.

				   These procedures are referenced in later encoding specifications.
				   이러한 절차들은 이후의 인코딩 규격에서 참조된다.

11.4.1		Subsequent subclause refer to the generation of a 2's-complement-binary-integer encoding of a whole number (which may be negative, or positive)
			into the minimum octets for the value.
			후속 하위절들은 값에 부호가 있는 정수의 2's-complement-binary-integer 인코딩의 최소 개수의 octet으로의 생성을 나타낸다.

			This subclause (11.4) specifies the precise encoding to be applied when such references are made.
			11.4 절은 이러한 참조들 (nagative or positive whole number)이 생성될 때 적용되는 정확한 인코딩 방법을 정의한다.


11.4.2		The leading bit of the field is defined as the leading bit of the bit-field, or as the most significant bit of the fiest octet in the field,
			and the trailing bit of the field is defined as the trailing bit of the bit-field or as the least significant bit of the last octet in the field.
			필드의 선행 비트는 비트 필드의 선행 비트 또는 필드의 첫번째 옥텟의 최상위 비트로 정의된다.
			필드의 후행 비트는 비트 필드의 후행 비트 또는 필드의 마지막 옥텟의 최하위 비트로 정의된다.
			> 필드의 leading bit = 첫번째 octet의 MSB, trailding bit = 마지막 octet의 LSB

11.4.3		For the following definition only, the bits shall be numbered zero for the trailing bit of the field, one for the next bit, and so up to the leading bit of the field.
			하위 정의에 한하여, 필드의 trailing bit를 0번, 다음 비트가 1번으로 하여 leading bit까지 번호가 부여된다.

11.4.4		In a 2's-complement-binary-integer encoding, the value of the whole number represented by the encoding shall be the sum of the values specified by each bit.
			2's-complement-binary-integer encoding에서, 인코딩이 표현하는 정수의 값은 각 비트 값의 합이된다.

			A bit which is set to "0" has zero value. A bit with number "n" which is set to "1" has the value 2^n unless it is the leading bit, it which case it has the (negative) value -2^n.
			"0"으로 설정된 bit는 0 값을 가지고, "1"로 설정되어 있는 "n"번 비트는 2^n의 값을 가진다.
			단 n이 leading bit (첫 번째 비트)라면 -(2^n) 값을 가진다. 

11.4.5		Any encoding which subs (as defined above) to the value being encoded is an encoding of that value.
			위에 정의된 합산 값의 인코딩은 그 값에 대한 인코딩이다.

11.4.6		A minimum octet 2's-complement-binary-integer encoding of the whole number has a field-width that is a multiple of eight bis and also satisfies the condition
			that the leading nine bits of the field shall not all be zero and shall not all be ones.
			정수의 최소 개수의 2's-complement-binary-integer 인코딩은 8 비트 배수의 필드 크기를 가지고 또한 필드의 첫 9개 선행 비트는 모두 0 이거나 모두 1이 될 수 없다는 조건을 만족한다.
			->  [        ] [        ] ... [    ]		-- 총 비트의 수는 8의 배수
			    [00000000] [0_______] ... [    ]		-- invalid
				[11111111] [1_______] ... [    ]		-- invalid

			NOTE - This is a nescessary and sufficient condition to produce a unique encoding.
				   이 사항은 고유한 인코딩을 생성하는 필요 충분 조건이다.

*/

ssize_t Dz1Asn1CodecPer_2cbi(u64_t *dst, u64_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (src == 0)
	{
		if (dst != NULL) *dst = 0;
		ret = 8;
	}
	else
	{
		u32_t cnt = sizeof(u64_t), i = 0;
		u64_t chk_v = src > 0 ? 0 : DZ1UINT64(0xFF80000000000000);

		while((src & DZ1UINT64(0xFF80000000000000)) == chk_v) { src <<= 8; cnt--; }
		if (dst != NULL) *dst = src >> ((cnt - ret) * 8);
		ret *= 8;
	}
	return errp->code == 0 ? ret : -1;
}

/* 11.5
	Encoding of a constrained whole number
	NOTE -	This subclause is referenced by other clauses, and itself references earlier clauses for the production
			of a non-negative-binary-integer or a 2's-complement-binary-integer encoding.
			이 하위절은 다른 절에 의해 참조되고, non-negative-binary-integer 또는 2's-complement-binary-integer encoding의 
			생성을 위해 이전의 절들을 참조한다.

			For the UNALIGNED variant the value is always encoded in the minimum number of bits necessary to represent 
			the range (defined in 11.5.3).
			UNALIGNED의 경우, 값은 항상 범위를 표현하는데 필요한 최소 비트의 수로 인코딩 된다. (11.5.3 절에 정의 됨)

			The rest of this Note addresses the ALIGNED variant. Where the range is less than or equal to 255, the value 
			encodes into a bit-field of the minimim size for the range. Where the range is exactly 256, the value encodes 
			into a single octet octet-aligned bit-field. Where the range is 257 to 64K, the value encodes into a two octet 
			octet-aligned bit-field. Where the range is greater than 64K, the range is ignored and the value encodes into 
			an octet-aligned bit-field which is the minimum number of octets for the value.
			이 Note의 나머지 부분에서는 ALIGNED의 경우를 다룬다. 범위가 255 이하인 경우, 값은 범위에 대해 최소 크기의 비트 필드로 인코딩된다.
			범위가 정확히 256인 경우, 값은 octet-aligned인 비트 필드의 단일 옥텟으로 인코딩된다. 범위가 257 이상 64K 이하인 경우, 값은 
			octet aligned인 비트 필드의 이중 옥텟으로 인코딩된다. 범위가 64K 초과인 경우, 범위는 무시 되고 값은 octet-aligned인 비트필드의 
			값에 대한 최소 수의 octet으로 인코딩 된다.

			In this latter case, later procedures (see 11.9) also encode a length field (usally a single octet) to indicate 
			the length of the encoding. For the other case, the length of the encoding is independant of the value being 
			encoded, and is not explicitly encoded.
			범위가 64K 초과인 경우, 인코딩의 길이를 표시하기 위해 11.9절의 절차를 통해 length field를 인코딩 한다. (보통 단일 비트)
			나머지 경우, 인코딩의 길이는 값이 인코딩 되는것과 독립적이고 명시적으로 인코딩 되지 않는다.

11.5.1		This subclause (11.5) specifies a mapping from a constrained whole number into either a bit-field (unaligned) or 
			a bit-field (octet-aligned in a ALIGNED variant), and is invoked by later clauses in this Recommendation.
			11.5 절은 constrained whole number를 unaligned 비트필드, octet aligned 비트필드(ALIGEND의 경우)로의 매핑을 명시한다. 
			그리고 이는 이 표준에서 이후의 절에서 사용된다.

11.5.2		The procedures of this subclause are invoked only if a constrained whole number to be encoded is available, and 
			the values of the lower bound "lb", and the upper bound, "ub", have been determined from the type notation(after 
			the application of PER-visible constraints).
			이 절의 절차는 constrained whole number의 인코딩이 가능할 때, 그리고 값의 하한 범위 "lb", 상한 범위 "ub"가 type notation에서 
			이미 정해져 있는 경우(PER-visible constraints 적용 이후)에만 호출된다.

			NOTE -	A lower bound cannot be determined if MIN evaluates to an infinite number, nor can an upper bound be 
					determined if MAX evaluates to an infinite number. For example, no upper or lower bound can be determined 
					for INTEGER (MIN..MAX).
					INTEGER (MIN..MAX) 처럼, 값의 범위가 MIN, MAX가 무한대인 경우, 해당 범위 (상한, 하한)를 정할 수 없다.
					
11.5.3		Let "range" be defined as the integer value ("ub" - "lb" + 1), and let the value to be encoded be "n".
			"range"를 ("ub" - "lb" + 1)의 정수 값으로 정의하고, 인코딩 되는 값은 "n"으로 한다.

11.5.4		If "range" has the value 1, then the result of the encoding shall be an empty bit-field (no bits).
			"range"의 값이 1이라면, 인코딩의 결과는 빈 비트필드가 된다. (비트 없음)

11.5.5		There are five other cases (leading to different encodings) to consider, where one applies to the UNALIGNED variant and four to the ALIGNED variant.
			다른 인코딩으로 이어지는 5가지의 경우가 있는데, 한 경우는 UNALIGNED variant에 적용하고, 나머지 4개는 ALIGNED variant에 적용한다.

11.5.6		In the case of the UNALIGNED variant the value ("n" - "lb") shall be encoded as a non-negative-binary-integer in a bit-field
			as a specified in 11.3 with the minimum number of bits necessary to represent the range.
			UMALIGNED variant의 경우, 값 ("n" - "lb")는 비트 필드에서 range를 표현하는데 필요한 최소의 비트 수로 11.3 절의 절차를 통해 
			non-negative-binary-integer로 인코딩된다.

			NOTE - If "range" satisfies the inequality 2^m < "range" < 2^(m+1), then the number of bits = m + 1.
				   "range"가 부등식 2^m < "range" < 2^(m+1)를 만족하면, 비트의 수는 m + 1 이다.

11.5.7		In the case of ALIGNED variant the encoding depends on whether:
			ALIGNED의 variant의 경우, 인코딩은 다음 여부에 따라 달라진다:

			a) "range" is less  than or equal to 255 (the bit-field case);
			   "range"가 255 이하인 경우 (bit-field case)

			b) "range" is exactly 256 (the one-octet case);
			   "range"가 정확히 256인 경우 (one-octet case)

			c) "range" is greater than 256 and less than or equal to 64K (the two octet case);
			   "range"가 256 초과 64K 이하인 경우 (two octet case)

			d) "range" is greater than 64K (the indefinite length case)
			   "range"가 64K 초과인 경우 (indeifinite length case)

11.5.7.1	(The bit-field case.) If "range" is less than or equal to 255, then invocation of this subclause requires the generation of a bit-field with a number of bits
			as specified in the table below, and containing the value ("n" - "lb") as a non-negative-binary-integer encoding in a bit-field as specified in 11.3
			"range"가 255 이하인 경우, 아래 표에 명시된 비트의 수인 비트 필드의 생성해야 하고, 비트필드에 11.3 절에 명시된 non-neagative-binary-integer 인코딩으로 "n-lb" 값을 포함한다.

				-------------------------------------------------
				|	"range"		|	Bit-field size (in bits)	|
				-------------------------------------------------
				|	2			|				1				|
				-------------------------------------------------
				|	3, 4		|				2				|
				-------------------------------------------------
				|	5, 6, 7, 8	|				3				|
				-------------------------------------------------
				|	9 to 16		|				4				|
				-------------------------------------------------
				|	17 to 32	|				5				|
				-------------------------------------------------
				|	33 to 64	|				6				|
				-------------------------------------------------
				|	65 to 128	|				7				|
				-------------------------------------------------
				|	129 to 255	|				8				|
				-------------------------------------------------
11.5.7.2	(The one-octet case.) If the range has a value of 256, then the value ("n" - "lb") shall be encoded in a one-octet bit-field
			(octet-aligned in the ALIGNED variant) as a non-negative-binary-integer as specified in 11.3.
			값의 범위가 256인 경우, 값 ("n" - "lb")는 11.3 절에 명시된 non-negative-binary-integer의 단일 옥텟의 비트필드로 인코딩 되어야 한다.
			(ALIGNED variant의 경우 octet-aligned)

11.5.7.3	(The two-octet case.) If the range has a value greater or equal to 257 and less than or equal to 64K, then the value ("n" - "lb")
			shall be encoded in a two-octet bit-field (octet-aligned in the ALIGNED variant) as a non-negative-binary-integer encoding as 
			specified in 11.3.
			값의 범위가 257 이상, 64K 이하인 경우, 값 ("n" - "lb")는 11.3 절에 명시된 non-negative-binary-integer의 두 옥텟의 비트필드로 인코딩 되어야 한다.
			(ALIGNED variant의 경우 octet-aligned)

11.5.7.4	(The indefinite case.) Ohterwise, the value ("n" - "lb") shall be encoded as a non-negative-binary-integer in a field (octet-aligned in the ALIGNED variant)
			with the minimum number of octets as specified in 11.3, and the number of octets "len" used in the encoding is used by other clauses that reference
			this subsclause to specify an encoding of the length.
			값의 범위가 64K 초과인 경우, 값 ("n" - "lb")는 필드에 11.3절에 명시된 최소 옥텟의 수의 non-negative-binary-integer로 인코딩 되어야 한다.
			그리고 인코딩에 사용된 octet의 수인 "len"은 길이의 인코딩을 지정하기 위해 이 하위절을 참조하는 다른절에서 사용된다.
			(ALIGNED variant의 경우 octet-aligned)
*/

static s32_t _get_bits_width(u64_t range)
{	/* 11.5.6
	NOTE -	If "range" satisfies the inequality 2^m < "range" <= 2^(m+1), then 
			the number of bits = m + 1.
			"range"가 부등식 2^m < "range" <= 2^(m+1)를 만족하면, 비트의 수는 m + 1 이다. */
	s32_t m;
	u64_t low, high;
	for (m = 0; m < 63; m++)
	{
		low = (DZ1UINT64(1) << m);
		high = (DZ1UINT64(1) << (m + 1));
		if ((low < range) && (range <= high)) return m + 1;
	}
	return 0;
}

static bool_t Dz1Asn1CodecPer_mk_cwn_unaligned(Dz1Asn1PerIntInfo *dst, u64_t offset, u64_t range, Dz1Error *errp)
{	/* 11.5.6
	In the case of the UNALIGNED variant the value ("n" - "lb") shall be encoded as a 
	non-negative-binary-integer in a bit-field as a specified in 11.3 with the minimum 
	number of bits necessary to represent the range.
	UMALIGNED variant 의 경우, 값 ("n" - "lb")는 비트 필드에서 range 를 표현하는데 필요한 최소의 
	비트 수로 11.3 절의 절차를 통해 non-negative-binary-integer 로 인코딩된다.

	NOTE -	If "range" satisfies the inequality 2^m < "range" < 2^(m+1), then 
			the number of bits = m + 1.
			"range"가 부등식 2^m < "range" < 2^(m+1)를 만족하면, 비트의 수는 m + 1 이다. */
	s32_t sz = _get_bits_width(range);
	if (sz == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u64_t mask = (1 << sz) - 1;
		dst->size.present = Dz1Asn1PerIntSizePresent_bits;
		dst->size.x.bits = (size_t)sz;
		dst->value = (offset & mask);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t Dz1Asn1CodecPer_mk_cwn_aligned_bf(Dz1Asn1PerIntInfo *dst, u8_t offset, u8_t range, Dz1Error *errp)
{	/* 11.5.7.1	
	(The bit-field case.) If "range" is less than or equal to 255, then invocation of this 
	subclause requires the generation of a bit-field with a number of bits as specified in 
	the table below, and containing the value ("n" - "lb") as a non-negative-binary-integer 
	encoding in a bit-field as specified in 11.3
	"range"가 255 이하인 경우, 아래 표에 명시된 비트 길이인 비트필드를 생성해야 하고, 비트필드에 11.3 
	절에 명시된 non-negative-binary-integer 인코딩으로 "n-lb" 값을 포함한다.

	-------------------------------------------------
	|	"range"		|	Bit-field size (in bits)	|
	-------------------------------------------------
	|	2			|				1				|
	-------------------------------------------------
	|	3, 4		|				2				|
	-------------------------------------------------
	|	5, 6, 7, 8	|				3				|
	-------------------------------------------------
	|	9 to 16		|				4				|
	-------------------------------------------------
	|	17 to 32	|				5				|
	-------------------------------------------------
	|	33 to 64	|				6				|
	-------------------------------------------------
	|	65 to 128	|				7				|
	-------------------------------------------------
	|	129 to 255	|				8				|
	------------------------------------------------- */
	s32_t bits_len = 0;
	if (0) { }
	else if (range <= 2)	bits_len = 1;
	else if (range <= 4)	bits_len = 2;
	else if (range <= 8)	bits_len = 3;
	else if (range <= 16)	bits_len = 4;
	else if (range <= 32)	bits_len = 5;
	else if (range <= 64)	bits_len = 6;
	else if (range <= 128)	bits_len = 7;
	else if (range <= 255)	bits_len = 8;

	if (bits_len == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u64_t mask = (1 << bits_len) - 1;
		dst->size.present = Dz1Asn1PerIntSizePresent_bits;
		dst->size.x.bits = bits_len;
		dst->value = ((u64_t)offset & mask);
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t Dz1Asn1CodecPer_mk_cwn_aligned_1o(Dz1Asn1PerIntInfo *dst, u8_t nnbi, Dz1Error *errp)
{	/* 11.5.7.2	
	(The one-octet case.) If the range has a value of 256, then the value ("n" - "lb") 
	shall be encoded in a one-octet bit-field (octet-aligned in the ALIGNED variant) 
	as a non-negative-binary-integer as specified in 11.3.
	값의 범위가 256인 경우, 값 ("n" - "lb")는 11.3 절에 명시된 non-negative-binary-integer 의 
	단일 옥텟의 비트필드로 인코딩 되어야 한다. (ALIGNED variant 의 경우 octet-aligned) */
	dst->size.present = Dz1Asn1PerIntSizePresent_octet1;
	dst->size.x.octet1 = NULL;
	dst->value = (u64_t)nnbi & 0xFF;
	Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t Dz1Asn1CodecPer_mk_cwn_aligned_2o(Dz1Asn1PerIntInfo *dst, u16_t nnbi, Dz1Error *errp)
{/* 11.5.7.3
	(The two-octet case.) If the range has a value greater or equal to 257 and less than 
	or equal to 64K, then the value ("n" - "lb") shall be encoded in a two-octet bit-field 
	(octet-aligned in the ALIGNED variant) as a non-negative- binary-integer encoding as 
	specified in 11.3.
	값의 범위가 257 이상, 64K 이하인 경우, 값 ("n" - "lb")는 11.3 절에 명시된 non-negative-binary-integer 의 
	두 옥텟의 비트필드로 인코딩 되어야 한다. (ALIGNED variant 의 경우 octet-aligned) */
	dst->size.present = Dz1Asn1PerIntSizePresent_octet2;
	dst->size.x.octet2 = NULL;
	dst->value = (u64_t)nnbi & 0xFFFF;
	Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t Dz1Asn1CodecPer_mk_cwn_aligned_ul(Dz1Asn1PerIntInfo *dst, u64_t nnbi, u64_t range, Dz1Error *errp)
{	/* 11.5.7.4	
	(The indefinite case.) Otherwise, the value ("n" - "lb") shall be encoded as a 
	non-negative-binary-integer in a  field (octet-aligned in the ALIGNED variant) 
	with the minimum number of octets as specified in 11.3, and the number of octets 
	"len" used in the encoding is used by other clauses that reference this subclause 
	to specify an encoding of the length.
	값의 범위가 64K 초과인 경우, 값 ("n" - "lb")는 필드에 11.3절에 명시된 최소 옥텟의 수의 
	non-negative-binary-integer 로 인코딩 되어 field-list 에 추가되어야 한다.(ALIGNED variant 의 
	경우 octet-aligned) 그리고 인코딩에 사용된 옥텟수인 "len"은 길이의 인코딩을 지정하기 위해 
	이 하위절을 참조하는 다른절에서 사용된다. */
	ssize_t sz = 0;
	if ((sz = Dz1Asn1CodecPer_nnbi(NULL, range, FALSE, errp)) < 0) ERR_OUT(errp);
	else
	{
		dst->size.present = Dz1Asn1PerIntSizePresent_indefinite;
		dst->size.x.indefinite = (size_t)(sz >> 3);
		dst->value = nnbi;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t Dz1Asn1CodecPer_mk_cwn_aligned(Dz1Asn1PerIntInfo *dst, u64_t offset, u64_t range, Dz1Error *errp)
{	/* 11.5.7
	In the case of ALIGNED variant the encoding depends on whether:
	ALIGNED의 variant 의 경우, 인코딩은 다음 여부에 따라 달라진다: */
	if (range <= 255)
	{	/* a) 
		"range" is less  than or equal to 255 (the bit-field case);
		"range"가 255 이하인 경우 (bit-field case) */
		if (Dz1Asn1CodecPer_mk_cwn_aligned_bf(dst, (u8_t)(offset & 0xFF), (u8_t)(range & 0xFF), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (range == 256)
	{	/* b) 
		"range" is exactly 256 (the one-octet case);
		"range"가 정확히 256인 경우 (one-octet case) */
		if (Dz1Asn1CodecPer_mk_cwn_aligned_1o(dst, (u8_t)(offset & 0xFF), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (range <= 65536)
	{	/* c) 
		"range" is greater than 256 and less than or equal to 64K (the two octet case);
		"range"가 256 초과 64K 이하인 경우 (two octet case) */
		if (Dz1Asn1CodecPer_mk_cwn_aligned_2o(dst, (u16_t)(offset & 0xFFFF), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{	/* d) 
		"range" is greater than 64K (the indefinite length case)
		"range"가 64K 초과인 경우 (indefinite length case) */
		if (Dz1Asn1CodecPer_mk_cwn_aligned_ul(dst, offset, range, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

/* 11.5
	Encoding of a constrained whole number
	NOTE -	This subclause is referenced by other clauses, and itself references earlier clauses for 
			the production of a non-negative-binary-integer or a 2's-complement-binary-integer encoding.
			이 하위절은 다른 절에 의해 참조되고, non-negative-binary-integer 또는 2's-complement-binary-integer 
			encoding 의 생성을 위해 이전의 절들을 참조한다.

			For the UNALIGNED variant the value is always encoded in the minimum number of bits necessary 
			to represent the range (defined in 11.5.3). The rest of this Note addresses the ALIGNED variant.
			UNALIGNED의 경우, 값은 항상 범위를 표현하는데 필요한 최소 비트의 수로 인코딩 된다. (11.5.3 절에 정의 됨)
			이 Note 의 나머지 부분에서는 ALIGNED의 경우를 다룬다.

			Where the range is less than or equal to 255, the value encodes into a bit-field of the minimum 
			size for the range. Where the range is exactly 256, the value encodes into a single octet 
			octet-aligned bit-field. Where the range is 257 to 64K, the value encodes into a two octet 
			octet-aligned bit-field. Where the range is greater than 64K, the range is ignored and the value 
			encodes into an octet-aligned bit-field which is the minimum number of octets for the value.
			범위가 255 이하인 경우, 값은 범위에 대해 최소 크기의 비트 필드로 인코딩된다. 범위가 정확히 256인 경우, 
			값은 octet-aligned 인 비트 필드의 1옥텟으로 인코딩된다. 범위가 257 이상 64K 이하인 경우, 값은 octet 
			aligned 인 비트 필드의 2옥텟으로 인코딩된다. 범위가 64K 초과인 경우, 범위는 무시 되고 값은 octet-aligned 인 
			비트필드의 값에 대한 최소 수의 옥텟으로 인코딩 된다.

			In this latter case, later procedures (see 11.9) also encode a length field (usually a single octet) 
			to indicate the length of the encoding. For the other case, the length of the encoding is independent 
			of the value being encoded, and is not explicitly encoded.
			범위가 64K 초과인 경우, 인코딩의 길이를 표시하기 위해 11.9절의 절차를 통해 length field 를 인코딩 한다.(보통 단일 비트)
			나머지 경우, 인코딩의 길이는 값이 인코딩 되는것과 독립적임으로 전혀 인코딩 되지 않는다. */

bool_t Dz1Asn1CodecPer_mk_cwn(Dz1Asn1PerIntInfo *dst, s64_t src, s64_t lb, s64_t ub, Dz1Asn1PerMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	/* 11.5.3
	Let "range" be defined as the integer value ("ub" - "lb" + 1), and let the value to be encoded be "n".
	"range"를 ("ub" - "lb" + 1)의 정수 값으로 정의하고, 인코딩 되는 값은 "n"으로 한다. */
	u64_t range = (u64_t)(ub - lb + 1);
	if (range == 1) 
	{	/* 11.5.4
		If "range" has the value 1, then the result of the encoding shall be an empty bit-field (no bits).
		"range"의 값이 1이라면, 인코딩의 결과는 빈 비트필드가 된다. (비트 없음) */
		dst->size.present = Dz1Asn1PerIntSizePresent_max;
		dst->size.x.bits = 0;
		dst->value = 0;
		Dz1Error_set(errp, 0);
	}
	else
	{	/* 11.5.5
		There are five other cases (leading to different encodings) to consider, 
		where one applies to the  UNALIGNED variant and four to the ALIGNED variant.
		다른 인코딩으로 이어지는 5가지의 경우가 있는데, 한 경우는 UNALIGNED variant 에 적용하고, 
		나머지 4개는 ALIGNED variant 에 적용한다. */
		switch(mode)
		{
		case Dz1Asn1PerMode_unaligned:
			if (Dz1Asn1CodecPer_mk_cwn_unaligned(dst, (u64_t)(src - lb), range, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1Asn1PerMode_aligned:
			if (Dz1Asn1CodecPer_mk_cwn_aligned(dst, (u64_t)(src - lb), range, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		}
	}

	return ERR_IS_SUCCESS(errp);
}

/*
11.7		Encoding of a semi-constrained whole number
			NOTE - This procedure is used when a lower bound can be identified but not an upper bound.
				   이 절차는 하한은 지정되었으나 상한은 그렇지 않은 경우에 사용된다.

				   The encoding procedure places the offset from the lower bound into the minimum number 
				   of octets as a non-negative-binary-integer, and requires an explicit length encoding 
				   (typically a single octet) as specified in later procedures.
				   인코딩 절차는 하한으로부터 offset까지 최소 옥텟 수의 non-negative-binary-integer로 인코딩하고, 
				   그 다음 뒤에 후행 절의 절차대로 명시적 length 값(보통 단일 옥텟)을 필요로 한다.

11.7.1		This subclause specifies a mapping from a semi-constrained whole number into a bit-field 
			(octet-aligned in the ALIGNED variant), and is invoked by later clauses in this Recoommendation.
			이 절은 semi-constrained whole number에서 bit-field(ALIGNED 변형에서 옥텟 정렬)로의 mapping을 지정하고, 
			이 표준에서 이후의 절에서 호출된다.

11.7.2		The procedures of this subclause (11.7) are invoked only if a semi-constrained whole number 
			("n" say) to be encoded is available, and the value of "lb" has been determined from the type 
			notation (after the application of PER-visible constraints).
			11.7 절의 절차들은 오직 seme-constrained whole number("n"이라고 함)의 인코딩이 가능하고, "lb"의 값이 
			type notation에서 결정된 경우(PER-visible 제약조건들이 적용된 이후)에만 호출된다.

			NOTE - A lower bound cannot be determined if MIN evaluates to an infinite number.
				   For example, no lower bound can be determined for INTEGER (MIN..MAX).
				   MIN이 무한수인 경우 하한을 정할수 없다. 예를 들어, INTEGER (MIN..MAX)의 하한 값은 결정될 수 없다.

11.7.3		The procedures of this subclause always produce the indefinite length case.
			이 절의 절차는 항상 정해지지 않은 길이의 경우를 생성한다.

11.7.4		(The indefinite length case.) The value ("n"-"lb") shall be encoded as a non-negative-binary integer 
			in a bit-field (octet-aligned in the ALIGNED variant) with the minimum number of octets as specified 
			in 11.3, and the number of octets "len" used in the encoding is used by other clauses that reference 
			this subclause to specify an encoding of the length.
			값 ("n"-"lb")는 11.3 절에 명시된것처럼 최소 옥텟수의 non-negative-binary integer 비트필드로 인코딩 되고,
			인코딩에서 사용되는 옥텟의 수 "len"은 길이의 인코딩을 지정하기 위해 이 절을 참조하는 다른절에 의해 사용된다.
*/

bool_t Dz1Asn1CodecPer_mk_scwn(Dz1Asn1PerIntInfo *dst, s64_t src, s64_t lb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u64_t v = (u64_t)(src - lb);
	ssize_t sz = 0;
	if (dst == NULL) ERR_OUT(errp);
	else if ((sz = Dz1Asn1CodecPer_nnbi(&dst->value, v, FALSE, errp)) < 0) ERR_OUT(errp);
	else
	{
		dst->size.present = Dz1Asn1PerIntSizePresent_indefinite;
		dst->size.x.indefinite = (size_t)(sz >> 3);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

/*
11.8		Encoding of an unconstrained whole number
			NOTE - This case only arises in the encoding of the value of an integer type with no lower bound.
				   이 케이스는 오직 하한이 없는 integer type의 인코딩에서만 발생한다.

				   The procedure encodes the values 2's-complement-binary-integer into the minumum number 
				   of octets required to accommodate the encoding, and the requires an explicit length 
				   encoding (typically a single octet) as specified in later procedures.
				   이 절차는 인코딩을 구성하는데 필요한 최소 수의 옥텟의 2's complement-binary-integer로 값을 인코딩 
				   하고, 후행 절차에 명시된 대로 명시적 length encoding(보통 단일 옥텟)을 필요로 한다.

11.8.1		This subsclause (11.8) specifies a mapping from an unconstrained whole number ("n" say) 
			into a bit-field (octet-aligned in the ALIGNED variant), and is invoked by later clauses 
			in this Recommendation | International Standard.
			이 절(11.8절)은 unconstrained whole number에서 bit-field(ALIGNED 변형에서 옥텟 정렬)로의 mapping을 
			지정하고, 이 표준에서 이후의 절에서 호출된다. 

11.8.2		The procedures of this subclause always produce the indefinite length case.
			이 절의 절차는 항상 정해지지 않은 길이의 경우를 생성한다.

11.8.3		(The indeifinite length case.) The value "n" shall be encoded as 2's-complement-binary-integer 
			in a bit-field (octet aligned in the ALIGNED variant) with the minimum number of octets as 
			specified in 11.4, and number of octets "len" used in the encoding is used by other clauses that 
			reference this subclause to specify an emcoding of the length.
			값 "n"은 11.4절에 명시된것처럼 최소 수의 옥텟의 2's-complement-binary-integer 비트필드로 인코딩 되고,
			인코딩에서 사용되는 옥텟의 수 "len"은 길이의 인코딩를 지정하기 위해 이 절을 참조하는 다른절에 의해 사용된다.
*/

bool_t Dz1Asn1CodecPer_mk_ucwn(Dz1Asn1PerIntInfo *dst, s64_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz = 0;
	if (dst == NULL) ERR_OUT(errp);
	else if ((sz = Dz1Asn1CodecPer_2cbi(&dst->value, src, errp)) < 0) ERR_OUT(errp);
	else
	{
		dst->size.present = Dz1Asn1PerIntSizePresent_indefinite;
		dst->size.x.indefinite = (size_t)(sz >> 3);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

/* 11.6	Encoding of a normally small non-negative whole number
		NOTE -	This procedure is used when encoding a non-negative whole number that is expected to be 
				small, but whose size is potentially unlimited due to the presence of an extension marker. 
				An example is a choice index.
				이 절차는 extension marker 의 존재로 인해 잠재적으로 길이의 제한이 없지만, 그 값이 작을것으로 예상되는 
				non-negative 정수를 인코딩할 때 사용된다. choice index 가 예시이다. */

bool_t Dz1Asn1CodecPer_mk_nsnnwn(Dz1Asn1PerNormallySmallNNBI *dst, u64_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src < 64)
	{	/* 11.6.1
		If the non-negative whole number, "n", is less than or equal to 63, 
		then a single-bit bit-field shall be appended to the field-list
		with the bit set to 0, and "n" shall be encoded as a non-negative-
		binary-integer into a 6-bit bit-field.
		non-negative whole number "n"이 63 이하인 경우라면, 필드 목록에 단일 비트의 
		0값이 비트 필드가 더해지고 "n"은 non-negative-binary-integer로 6비트 비트 
		필드로 인코딩 된다. */
		dst->present = Dz1Asn1PerNormallySmallNNBIPresent_small_num;
		dst->x.small_num = (u8_t)(src & 0x3F);
		Dz1Error_set(errp, 0);
	}
	else
	{	/* 11.6.2
		If "n" is greater than or equal to 64, a single-bit bit-field with 
		the bit set to 1 shall be appended to the field-list.
		"n"이 64 이상인 경우라면, 1로 설정된 단일 비트의 비트필드가 필드 목록에 더해진다.

		The value "n" shall then be encoded as a semi-constrained whole number 
		with "lb" equal to 0 and the procedures of 11.9 shall be invoked to add 
		it to the field-list preceded by a length determinant.
		값 "n"은 "lb"를 0으로 하여 semi-constrained whole number "v"로 변환한다. 
		11.9절의 절차를 통해 "v"에 대한 length determinant 와 "v"를 필드 목록에 추가한다.	*/
		if (Dz1Asn1CodecPer_mk_scwn(&dst->x.big_num, src, 0, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1PerNormallySmallNNBIPresent_big_num;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static ssize_t _length_enc_no_cons(Dz1Asn1Stream *dst, u64_t len, Dz1Asn1PerMode mode, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (len <= 127)
	{	/* 11.9.3.6
		If "n" is less than or equal to 127, then "n" shall be encoded 
		as a non-negative-binary-integer (using the procedures of 11.3) into bits 7
		(most significant) to 1 (least significant) of a single octet and bit 8 
		shall be set to zero. This shall be appended to the field-list as a bit-field 
		(octet-aligned in the ALIGNED variant) followed by the associated field or list 
		of fields, completing these procedures.
		길이 n 이 127이하의 값을 가지는 경우, 단일 옥텟에 MSB를 0으로 설정하고 남은 7비트에 n 값이 
		non-negative-binary-integer(11.3 절차)로 저장된다. 이는 bit-field 로 저장되어야 하고
		(ALIGNED인 경우 Octet 정렬 위치에) 뒤이어 연관 필드 또는 필드 리스트를 추가하여 본 절차를 
		종료합니다.

		NOTE -	For example, if in the following a value of A is 4 characters long, 
				and that of B is 4 items long:
				예를 들어, 다음 A 값이 4글자를 가지고, B 가 4개의 아이템을 가지면
			A ::= IA5String									// unconstrained
			B ::= SEQUENCE (SIZE (4..123456)) OF INTEGER	// large “ub”
				both values are encoded with the length octet occupying one octet, 
				and with the most significant set to 0 to indicate that the length 
				is less than or equal to 127:
				두 값 다 단일 옥텟길이의 길이 값을 가지며, MSB가 0으로 설정됩니다. 이는 길이가 127 
				이하라는 의미입니다. */
		u8_t v = (u8_t)(len & 0x7F);
		if (mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1Stream_pushOctet(dst, v, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
	}
	else if (len < 16384)
	{	/* 11.9.3.7	
		If "n" is greater than 127 and less than 16K, then "n" shall be encoded as a 
		non-negative-binary-integer (using the procedures of 11.3) into bit 6 of octet one 
		(most significant) to bit 1 of octet two (least significant) of a two-octet bit-field 
		(octet-aligned in the ALIGNED variant) with bit 8 of the first octet set to 1 and 
		bit 7 of the first octet set to zero.
		길이 값 n 이 127보다 크고 16K보다 작으면, 2 octet 길이의 (short) MSB가 1, MSB - 1이 0으로 
		설정되며 나머지 14bit에 n 값이 non-negative-binary-integer(11.3 절차)에 의해 변환되어 저장
		됩니다. (ALIGNED인 경우 Octet 정렬)

		This shall be appended to the field-list followed by the associated field or list of 
		fields, completing these procedures.
		뒤따라 연관 필드의 데이터를 저장하고 본 절차를 종료합니다.

		NOTE -	If in the example of 11.9.3.6 a value of A is 130 characters long, and a value 
				of B is 130 items long, both values are encoded with the length component 
				occupying 2 octets, and with the two most significant bits (bits 8 and 7) of 
				the octet set to 10 to indicate that the length is greater than 127 but less 
				than 16K.
				11.9.3.6의 예제에서 A 가 130 자, B 가 130 아이템을 가지는 경우 두 값 모두 2 옥텟길이의 
				길이 값이 MSB와 MSB - 1이 "10"으로 설정되어 저장되며 이는 길이가 127초과 16K미만임을 
				의미합니다. */
		u16_t v = 0x8000 | (u16_t)(len & 0x3FFF);
		if (mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1Stream_pushBitsI16(dst, v, 16, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.3.8
		If "n" is greater than or equal to 16K, then there shall be appended to the field-list 
		a single octet in a bit-field (octet-aligned in the ALIGNED variant) with bit 8 set to 
		1 and bit 7 set to 1, and bits 6 to 1 encoding the value 1, 2, 3 or 4 as a non-negative-
		binary-integer (using the procedures of 11.8). 
		길이 값 n 이 16K이상이면, 단일 옥텟의 MSB와 MSB - 1이 "11"로 설정되고 남은 6비트에 1,2,3 또는 4값이 
		non-negative-binary-integer(11.8 절차)로 변환되어 저장됩니다(ALIGNED인 경우 Octet 정렬)

		This single octet shall be followed by part of the associated field or list of fields, 
		as specified below.
		이후 연관 필드 또는 필드 리스트의 일부분이 아래와 같이 저장됩니다.

		NOTE -	The value of bits 6 to 1 is restricted to 1-4 (instead of the theoretical limits 
				of 0-63) so as to limit the number of items that an implementation has to have 
				knowledge of to a more manageable number (64K instead of 1024K).
				비트 6~1의 값은 구현 시 알아야 하는 항목 수를 보다 관리하기 쉬운 수(1024K 대신 64K)로 제한
				하기 위해 (이론적 제한인 0~63 대신) 1~4로 제한됩니다.
				-> 비트 6~1의 값은 최대 길이를 64K로 제한하기위해 (이론적으로 가능한 0~63 대신) 1~4로 제한 합니다. 

		11.9.3.8.1	
		The value of bits 6 to 1 (1 to 4) shall be multiplied by 16K giving a count ("m" say). The 
		choice of the integer in bits 6 to 1 shall be the maximum allowed value such that the 
		associated field or list of fields contains more than or exactly "m" octets, bits, components 
		or characters, as appropriate.
		6비트에 저장되는 (1~4)값에 16K를 곱하여 원래 길이를 구해야 합니다. 비트 6~1에 저장되는 정수 값을 결정할 
		때에는 관련 필드 또는 필드 목록에 "m"개 이상의 옥텟, 비트, 구성 요소 또는 문자가 적절하게 포함되도록 허용되는 
		최대 값이어야 합니다.

		NOTE 1 -	The un-fragmented form handles lengths up to 16K. The fragmentation therefore 
					provides for lengths up to 64K with a granularity of 16K.
					조각화 되지 않은 양식은 최대 16K 길이를 처리합니다. 따라서 조각화는 16K 단위로 최대 64K의 
					길이를 제공합니다.
					-> 단일 조각은 최소 16K를 가질 수 있습니다. 따라서 조각화의 한 조각은 16K 단위로 최대 64K 
					길이를 가질 수 있습니다.

		NOTE 2 -	If in the example of 11.9.3.6 a value of "B" is 144K + 1 (i.e., 64K + 64K + 16K + 1) 
					items long, the value is fragmented, with the two most significant bits (bits 8 and 7) 
					of the first three fragments set to 11 to indicate that one to four blocks each of 16K 
					items follow, and that another length component will follow the last block of each fragment:
					11.9.3.6의 예에서 "B" 값이 144K + 1(즉, 64K + 64K + 16K + 1) 항목 길이인 경우 값은 처음 세 개의 
					조각은 (길이 결정자의) 최상위 비트 8 및 7이 11로 설정되어 16K단위의 블록이 1~4개 존재하고 마지막에는 
					다른 구성의 길이 요소를 가진 블록이 따라오는 것으로 나타낼 수 있습니다. */
		u8_t v = 0xC0, cnt = 0;
		if (0) { }
		else if (len >= (16384 * 4))	cnt = 0x04;
		else if (len >= (16384 * 3))	cnt = 0x03;
		else if (len >= (16384 * 2))	cnt = 0x02;
		else							cnt = 0x01;

		if (mode == Dz1Asn1PerMode_aligned && Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1Stream_pushOctet(dst, v | cnt, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ret = 16384 * cnt;
			Dz1Error_set(errp, 0);
		}
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

static ssize_t _length_dec_no_cons(Dz1Asn1Stream *src, Dz1Asn1PerMode mode, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t v1 = 0;
	ssize_t sz = 0;
	if ((sz = Dz1Asn1Stream_popOctet(src, &v1, errp)) < 0) ERR_OUT(errp);
	else if ((v1 & 0x80) == 0)		// v = 0b0xxxxxxx
	{	/* 11.9.3.6
		If "n" is less than or equal to 127, then "n" shall be encoded 
		as a non-negative-binary-integer (using the procedures of 11.3) into bits 7
		(most significant) to 1 (least significant) of a single octet and bit 8 
		shall be set to zero. This shall be appended to the field-list as a bit-field 
		(octet-aligned in the ALIGNED variant) followed by the associated field or list 
		of fields, completing these procedures.
		길이 n이 127이하의 값을 가지는 경우, 단일 옥텟에 MSB를 0으로 설정하고 남은 7비트에 n 값이 
		non-negative-binary-integer(11.3 절차)로 저장된다. 이는 bit-field 로 저장되어야 하고
		(ALIGNED인 경우 Octet 정렬 위치에) 뒤이어 연관 필드 또는 필드 리스트를 추가하여 본 절차를 
		종료합니다.

		NOTE -	For example, if in the following a value of A is 4 characters long, 
				and that of B is 4 items long:
				예를 들어, 다음 A 값이 4글자를 가지고, B 가 4개의 아이템을 가지면
			A ::= IA5String									// unconstrained
			B ::= SEQUENCE (SIZE (4..123456)) OF INTEGER	// large “ub”
				both values are encoded with the length octet occupying one octet, 
				and with the most significant set to 0 to indicate that the length 
				is less than or equal to 127:
				두 값 다 단일 옥텟길이의 길이 값을 가지며, MSB가 0으로 설정됩니다. 이는 길이가 127 
				이하라는 의미입니다. */
		ret = (ssize_t)v1 & 0x7F;
		Dz1Error_set(errp, 0);
	}
	else if ((v1 & 0x40) == 0)	// v = 0b10xxxxxx
	{	/* 11.9.3.7	
		If "n" is greater than 127 and less than 16K, then "n" shall be encoded as a 
		non-negative-binary-integer (using the procedures of 11.3) into bit 6 of octet one 
		(most significant) to bit 1 of octet two (least significant) of a two-octet bit-field 
		(octet-aligned in the ALIGNED variant) with bit 8 of the first octet set to 1 and 
		bit 7 of the first octet set to zero.
		길이 값 n 이 127보다 크고 16K보다 작으면, 2 octet 길이의 (short) MSB가 1, MSB - 1이 0으로 
		설정되며 나머지 14bit에 n 값이 non-negative-binary-integer(11.3 절차)에 의해 변환되어 저장
		됩니다. (ALIGNED인 경우 Octet 정렬)

		This shall be appended to the field-list followed by the associated field or list of 
		fields, completing these procedures.
		뒤따라 연관 필드의 데이터를 저장하고 본 절차를 종료합니다.

		NOTE -	If in the example of 11.9.3.6 a value of A is 130 characters long, and a value 
				of B is 130 items long, both values are encoded with the length component 
				occupying 2 octets, and with the two most significant bits (bits 8 and 7) of 
				the octet set to 10 to indicate that the length is greater than 127 but less 
				than 16K.
				11.9.3.6의 예제에서 A 가 130 자, B 가 130 아이템을 가지는 경우 두 값 모두 2 옥텟길이의 
				길이 값이 MSB와 MSB - 1이 "10"으로 설정되어 저장되며 이는 길이가 127초과 16K미만임을 
				의미합니다. */
		u8_t v2 = 0;
		if ((sz = Dz1Asn1Stream_popOctet(src, &v2, errp)) < 0) ERR_OUT(errp);
		else
		{
			ret = ((ssize_t)v1 & 0x3F);
			ret <<= 8;
			ret |= ((ssize_t)v2 & 0xFF);
			Dz1Error_set(errp, 0);
		}
	}
	else						// v1 = 0b11nnnnnn
	{	/* 11.9.3.8
		If "n" is greater than or equal to 16K, then there shall be appended to the field-list 
		a single octet in a bit-field (octet-aligned in the ALIGNED variant) with bit 8 set to 
		1 and bit 7 set to 1, and bits 6 to 1 encoding the value 1, 2, 3 or 4 as a non-negative-
		binary-integer (using the procedures of 11.8). 
		길이 값 n 이 16K이상이면, 단일 옥텟의 MSB와 MSB - 1이 "11"로 설정되고 남은 6비트에 1,2,3 또는 4값이 
		non-negative-binary-integer(11.8 절차)로 변환되어 저장됩니다(ALIGNED인 경우 Octet 정렬)

		This single octet shall be followed by part of the associated field or list of fields, 
		as specified below.
		이후 연관 필드 또는 필드 리스트의 일부분이 아래와 같이 저장됩니다.

		NOTE -	The value of bits 6 to 1 is restricted to 1-4 (instead of the theoretical limits 
				of 0-63) so as to limit the number of items that an implementation has to have 
				knowledge of to a more manageable number (64K instead of 1024K).
				비트 6~1의 값은 구현 시 알아야 하는 항목 수를 보다 관리하기 쉬운 수(1024K 대신 64K)로 제한
				하기 위해 (이론적 제한인 0~63 대신) 1~4로 제한됩니다.
				-> 비트 6~1의 값은 최대 길이를 64K로 제한하기위해 (이론적으로 가능한 0~63 대신) 1~4로 제한 합니다. 

		11.9.3.8.1	
		The value of bits 6 to 1 (1 to 4) shall be multiplied by 16K giving a count ("m" say). The 
		choice of the integer in bits 6 to 1 shall be the maximum allowed value such that the 
		associated field or list of fields contains more than or exactly "m" octets, bits, components 
		or characters, as appropriate.
		6비트에 저장되는 (1~4)값에 16K를 곱하여 원래 길이를 구해야 합니다. 비트 6~1에 저장되는 정수 값을 결정할 
		때에는 관련 필드 또는 필드 목록에 "m"개 이상의 옥텟, 비트, 구성 요소 또는 문자가 적절하게 포함되도록 허용되는 
		최대 값이어야 합니다.

		NOTE 1 -	The un-fragmented form handles lengths up to 16K. The fragmentation therefore 
					provides for lengths up to 64K with a granularity of 16K.
					조각화 되지 않은 양식은 최대 16K 길이를 처리합니다. 따라서 조각화는 16K 단위로 최대 64K의 
					길이를 제공합니다.
					-> 단일 조각은 최소 16K를 가질 수 있습니다. 따라서 조각화의 한 조각은 16K 단위로 최대 64K 
					길이를 가질 수 있습니다.

		NOTE 2 -	If in the example of 11.9.3.6 a value of "B" is 144K + 1 (i.e., 64K + 64K + 16K + 1) 
					items long, the value is fragmented, with the two most significant bits (bits 8 and 7) 
					of the first three fragments set to 11 to indicate that one to four blocks each of 16K 
					items follow, and that another length component will follow the last block of each fragment:
					11.9.3.6의 예에서 "B" 값이 144K + 1(즉, 64K + 64K + 16K + 1) 항목 길이인 경우 값은 처음 세 개의 
					조각은 (길이 결정자의) 최상위 비트 8 및 7이 11로 설정되어 16K단위의 블록이 1~4개 존재하고 마지막에는 
					다른 구성의 길이 요소를 가진 블록이 따라오는 것으로 나타낼 수 있습니다. */
		u8_t cnt = (v1 & 0x7);
		if (cnt > 4) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret = 16384 * cnt;
			Dz1Error_set(errp, 0);
		}
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

static ssize_t _length_enc_unalign(Dz1Asn1Stream *dst, u64_t len, u64_t lb, u64_t *_ub, Dz1Error *errp)
{
	ssize_t ret = 0;

	u64_t v = (u64_t)(len - lb);
	if (_ub != NULL)
	{	// may constrained
		s64_t ub = *_ub;
		u64_t range = (u64_t)(ub - lb + 1);
		if (range == 1)
		{	/* 11.9.1
			This subclause is not invoked if, in accordance with the specification of later clauses, 
			the value of the length determinant, "n", is fixed by the type definition (constrained by 
			PER-visible constraints) to a value less than 64K.
			후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
			본 절차가 호출되지 않습니다. */
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
		else if (ub <= 65535)
		{	/* 11.9.4.1
			If the length determinant "n" to be encoded is a constrained whole number with "ub" less than 64K, 
			then ("n"-"lb") shall be encoded as a non-negative-binary-integer (as specified in 11.3) using the 
			minimum number of bits necessary to encode the "range" ("ub" - "lb" + 1), unless "range" is 1, in 
			which case there shall be no length encoding. 
			인코딩할 길이 결정자 "n"이 "ub"가 64K 미만인 constrained-whole-number 인 경우 v("n"-"lb")는 non-negative-
			binary-integer (11.3에 지정된 대로)로 변환하여 "range"("ub" - "lb" + 1)를 인코딩하는 데 필요한 최소 비트 
			길이로 인코딩 됩니다. 단, "range"가 1인 경우(고정길이)에는 길이를 인코딩 하지 않습니다.

			If "n" is non-zero this shall be followed by an associated field or list of fields, completing these procedures. 
			If "n" is zero there shall be no further addition to the field-list, completing these procedures.
			만약 길이 n 이 0이 아니면 연관 필드나 필드 리스트를 추가하고 본 절차를 종료합니다. 만약 n 이 0이면 연관 필드 데이터를 
			저장하지 않고 본 절차를 종료합니다.
			NOTE -	If "range" satisfies the inequality 2^m < "range" <= 2^(m + 1), then the number of bits in 
			the length determinant is m + 1.
			range 가 2^m < "range" <= 2^(m + 1)을 만족하는 경우, m + 1 값이 n range를 저장하는데 필요한 비트 길이로 사용됩니다. */
			Dz1Asn1PerIntInfo tgt = Dz1Asn1PerIntInfo_NULL;
			if (Dz1Asn1CodecPer_mk_cwn_unaligned(&tgt, (u64_t)(len - lb), range, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, (s32_t)tgt.size.x.bits, errp) == FALSE) ERR_OUT(errp);
			else
			{
				ret = (ssize_t)len;
				Dz1Error_set(errp, 0);
			}
		}
		else
		{	/* 11.9.4.2	
			If the length determinant "n" to be encoded is a normally small length, or a constrained whole number 
			with "ub" greater than or equal to 64K, or is a semi-constrained whole number, then "n" shall be encoded 
			as specified in 11.9.3.4 to 11.9.3.8.4.
			인코딩할 길이 결정자 "n"이 normally-small-length 이거나 "ub"가 64K보다 같거나 큰 constrained-whole-number 이거나 
			semi-constrained-whole-number 인 경우 "n "는 11.9.3.4~11.9.3.8.4에 지정된 대로 인코딩 되어야 합니다.

			NOTE -	Thus, if "ub" is greater than or equal to 64K, the encoding of the length determinant is the same 
					as it would be if the length were unconstrained.
					따라서 ub 가 64K이상인 경우 길이 결정자는 길이가 제약 없는(unconstrained)경우의 길이 결정자와 동일합니다. */
			if ((ret = _length_enc_no_cons(dst, len, Dz1Asn1PerMode_unaligned, errp)) < 0) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{	/*	11.9.4.2
		If the length determinant "n" to be encoded is a normally small length, or a constrained whole number 
		with "ub" greater than or equal to 64K, or is a semi-constrained whole number, then "n" shall be encoded 
		as specified in 11.9.3.4 to 11.9.3.8.4.
		인코딩할 길이 결정자 "n"이 normally-small-length 이거나 "ub"가 64K보다 같거나 큰 constrained-whole-number 이거나 
		semi-constrained-whole-number 인 경우 "n "는 11.9.3.4~11.9.3.8.4에 지정된 대로 인코딩 되어야 합니다.

		NOTE -	Thus, if "ub" is greater than or equal to 64K, the encoding of the length determinant is the same 
				as it would be if the length were unconstrained.
				따라서 ub 가 64K이상인 경우 길이 결정자는 길이가 제약 없는(unconstrained)경우의 길이 결정자와 동일합니다. */
		if ((ret = _length_enc_no_cons(dst, len, Dz1Asn1PerMode_unaligned, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

static ssize_t _length_dec_unalign(Dz1Asn1Stream *src, u64_t lb, u64_t *_ub, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (_ub != NULL)
	{	// may constrained
		s64_t ub = *_ub;
		u64_t range = (ub - lb + 1);
		if (range == 1)
		{	/* 11.9.1
			This subclause is not invoked if, in accordance with the specification of later clauses, 
			the value of the length determinant, "n", is fixed by the type definition (constrained by 
			PER-visible constraints) to a value less than 64K.
			후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
			본 절차가 호출되지 않습니다. */
			ret = (ssize_t)lb;
			Dz1Error_set(errp, 0);
		}
		else if (ub <= 65535)
		{	/* 11.9.4.1
			If the length determinant "n" to be encoded is a constrained whole number with "ub" less than 64K, 
			then ("n"-"lb") shall be encoded as a non-negative-binary-integer (as specified in 11.3) using the 
			minimum number of bits necessary to encode the "range" ("ub" - "lb" + 1), unless "range" is 1, in 
			which case there shall be no length encoding. 
			인코딩할 길이 결정자 "n"이 "ub"가 64K 미만인 constrained-whole-number 인 경우 v("n"-"lb")는 non-negative-
			binary-integer (11.3에 지정된 대로)로 변환하여 "range"("ub" - "lb" + 1)를 인코딩하는 데 필요한 최소 비트 
			길이로 인코딩 됩니다. 단, "range"가 1인 경우(고정길이)에는 길이를 인코딩 하지 않습니다.

			If "n" is non-zero this shall be followed by an associated field or list of fields, completing these procedures. 
			If "n" is zero there shall be no further addition to the field-list, completing these procedures.
			만약 길이 n 이 0이 아니면 연관 필드나 필드 리스트를 추가하고 본 절차를 종료합니다. 만약 n 이 0이면 연관 필드 데이터를 
			저장하지 않고 본 절차를 종료합니다.
			NOTE -	If "range" satisfies the inequality 2^m < "range" <= 2^(m + 1), then the number of bits in 
			the length determinant is m + 1.
			range 가 2^m < "range" <= 2^(m + 1)을 만족하는 경우, m + 1 값이 n range를 저장하는데 필요한 비트 길이로 사용됩니다. */
			u64_t len = 0;
			ssize_t bit_sz = _get_bits_width(range);
			if (Dz1Asn1Stream_popBitsI64(src, &len, bit_sz, errp) == FALSE) ERR_OUT(errp);
			else
			{
				ret = (ssize_t)(len + lb);
				Dz1Error_set(errp, 0);
			}
		}
		else 
		{	/* 11.9.4.2	
			If the length determinant "n" to be encoded is a normally small length, or a constrained whole number 
			with "ub" greater than or equal to 64K, or is a semi-constrained whole number, then "n" shall be encoded 
			as specified in 11.9.3.4 to 11.9.3.8.4.
			인코딩할 길이 결정자 "n"이 normally-small-length 이거나 "ub"가 64K보다 같거나 큰 constrained-whole-number 이거나 
			semi-constrained-whole-number 인 경우 "n "는 11.9.3.4~11.9.3.8.4에 지정된 대로 인코딩 되어야 합니다.

			NOTE -	Thus, if "ub" is greater than or equal to 64K, the encoding of the length determinant is the same 
					as it would be if the length were unconstrained.
					따라서 ub 가 64K이상인 경우 길이 결정자는 길이가 제약 없는(unconstrained)경우의 길이 결정자와 동일합니다. */
			if ((ret = _length_dec_no_cons(src, Dz1Asn1PerMode_unaligned, errp)) < 0) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.4.2
		If the length determinant "n" to be encoded is a normally small length, or a constrained whole number 
		with "ub" greater than or equal to 64K, or is a semi-constrained whole number, then "n" shall be encoded 
		as specified in 11.9.3.4 to 11.9.3.8.4.
		인코딩할 길이 결정자 "n"이 normally-small-length 이거나 "ub"가 64K보다 같거나 큰 constrained-whole-number 이거나 
		semi-constrained-whole-number 인 경우 "n "는 11.9.3.4~11.9.3.8.4에 지정된 대로 인코딩 되어야 합니다.

		NOTE -	Thus, if "ub" is greater than or equal to 64K, the encoding of the length determinant is the same 
				as it would be if the length were unconstrained.
				따라서 ub 가 64K이상인 경우 길이 결정자는 길이가 제약 없는(unconstrained)경우의 길이 결정자와 동일합니다. */
		if ((ret = _length_dec_no_cons(src, Dz1Asn1PerMode_unaligned, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

static ssize_t _length_enc_align(Dz1Asn1Stream *dst, u64_t len, u64_t lb, u64_t *_ub, Dz1Error *errp)
{
	ssize_t ret = 0;

	u64_t v = (u64_t)(len - lb);
	if (_ub != NULL)
	{	// may constrained
		s64_t ub = *_ub;
		if ((ub - lb + 1) == 1)
		{	/* 11.9.1
			This subclause is not invoked if, in accordance with the specification of later clauses, 
			the value of the length determinant, "n", is fixed by the type definition (constrained by 
			PER-visible constraints) to a value less than 64K.
			후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
			본 절차가 호출되지 않습니다. */
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
		else if (ub <= 65535)
		{	/* 11.9.3.3
			Where the length determinant is a constrained whole number with "ub" less than 64K, 
			then the field-list shall have appended to it the encoding of the constrained whole 
			number for the length determinant as specified in 11.5. If "n" is non-zero, this 
			shall be followed by the associated field or list of fields, completing these procedures. 
			If "n" is zero there shall be no further addition to the field-list, completing these procedures.
			길이 결정자가 ub값이 64K미만으로 설정된 constrained whole number 인 경우, 11.5(constrained whole number)에 
			지정된 변환 절차로 인코딩 합니다. (쓸데없음)길이가 0이 아닌 경우 연관된 필드 또는 필드 리스트를 추가하고 본 절차를 
			종료합니다. 길이가 0이면 연관 필드 데이터 추가 없이 본 절차를 종료합니다.

			NOTE 1 - For example:
				A ::= IA5String (SIZE (3..6))			-- Length is encoded in a 2-bit bit-field.
				B ::= IA5String (SIZE (40000..40254))	-- Length is encoded in an 8-bit bit-field.
				C ::= IA5String (SIZE (0..32000))		-- Length is encoded in a 2-octet bit-field (octet-aligned in the ALIGNED variant).
				D ::= IA5String (SIZE (64000))			-- Length is not encoded.

			NOTE 2 - The effect of making no addition in the case of "n" equals zero is that padding to an octet 
						boundary does not occur when these procedures are invoked to add an octet-aligned-bit-field of zero 
						length, unless required by 11.5.
						길이 n 이 0일 때 아무것도 추가하지 않는다는 뜻은, ALIGNED방식에서 일어나는 정렬 Padding이 11.5에서 언급한 것처럼 
						별도로 요구하지 않는 한 일어나지 않는 것을 의미합니다.	*/
			Dz1Asn1PerIntInfo tgt = Dz1Asn1PerIntInfo_NULL;
			if (Dz1Asn1CodecPer_mk_cwn(&tgt, len, lb, ub, Dz1Asn1PerMode_aligned, errp) == FALSE) ERR_OUT(errp);
			else
			{
				switch(tgt.size.present)
				{
				case Dz1Asn1PerIntSizePresent_bits:
					if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, (s32_t)tgt.size.x.bits, errp) == FALSE) ERR_OUT(errp);
					else
					{
						ret = (ssize_t)len;
						Dz1Error_set(errp, 0);
					}
					break;
				case Dz1Asn1PerIntSizePresent_octet1:
					if (Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
					else if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, 8, errp) == FALSE) ERR_OUT(errp);
					else
					{
						ret = (ssize_t)len;
						Dz1Error_set(errp, 0);
					}
					break;
				case Dz1Asn1PerIntSizePresent_octet2:
					if (Dz1Asn1Stream_pushAlign(dst, errp) == FALSE) ERR_OUT(errp);
					else if (Dz1Asn1Stream_pushBitsI64(dst, tgt.value, 16, errp) == FALSE) ERR_OUT(errp);
					else
					{
						ret = (ssize_t)len;
						Dz1Error_set(errp, 0);
					}
					break;
				default: ERR_SET_OUT(errp, EFAULT); break;
				}
			}
		}
		else 
		{	/* 11.9.3.5	
			Otherwise (unconstrained length, or large "ub"), "n" is encoded and appended to the field-list 
			followed by the associated fields as specified below.
			그렇지 않은 경우(unconstrained-length 또는 큰 "ub") "n"이 아래에 지정된 대로(11.9.3.6 ~ 11.9.3.8.4에 따라)
			인코딩 되어 필드 목록에 추가되고 그 뒤에는 관련 필드가 추가됩니다.
			NOTE -	The lower bound, "lb", does not affect the length encodings specified in 11.9.3.6 to 11.9.3.8.4.
					최소값 lb 는 11.9.3.6에서 11.9.3.8.4의 절차에서 효력을 발휘하지 않습니다. */
			if ((ret = _length_enc_no_cons(dst, len, Dz1Asn1PerMode_aligned, errp)) < 0) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.3.5	
		Otherwise (unconstrained length, or large "ub"), "n" is encoded and appended to the field-list 
		followed by the associated fields as specified below.
		그렇지 않은 경우(unconstrained-length 또는 큰 "ub") "n"이 아래에 지정된 대로(11.9.3.6~11.9.3.8.4에 따라)
		인코딩 되어 필드 목록에 추가되고 그 뒤에는 관련 필드가 추가됩니다.
		NOTE -	The lower bound, "lb", does not affect the length encodings specified in 11.9.3.6 to 11.9.3.8.4.
				최소값 lb 는 11.9.3.6에서 11.9.3.8.4의 절차에서 효력을 발휘하지 않습니다. */
		if ((ret = _length_enc_no_cons(dst, len, Dz1Asn1PerMode_aligned, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

static ssize_t _length_dec_align(Dz1Asn1Stream *src, u64_t lb, u64_t *_ub, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (_ub != NULL)
	{	// may constrained
		s64_t ub = *_ub;
		if ((ub - lb + 1) == 1)
		{	/* 11.9.1
			This subclause is not invoked if, in accordance with the specification of later clauses, 
			the value of the length determinant, "n", is fixed by the type definition (constrained by 
			PER-visible constraints) to a value less than 64K.
			후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
			본 절차가 호출되지 않습니다. */
			ret = (ssize_t)lb;
			Dz1Error_set(errp, 0);
		}
		else if (ub <= 65535)
		{	/* 11.9.3.3
			Where the length determinant is a constrained whole number with "ub" less than 64K, 
			then the field-list shall have appended to it the encoding of the constrained whole 
			number for the length determinant as specified in 11.5. If "n" is non-zero, this 
			shall be followed by the associated field or list of fields, completing these procedures. 
			If "n" is zero there shall be no further addition to the field-list, completing these procedures.
			길이 결정자가 ub값이 64K미만으로 설정된 constrained whole number인 경우, 11.5(constrained whole number)에 
			지정된 변환 절차로 인코딩 합니다. (쓸데없음)길이가 0이 아닌 경우 연관된 필드 또는 필드 리스트를 추가하고 본 절차를 
			종료합니다. 길이가 0이면 연관 필드 데이터 추가 없이 본 절차를 종료합니다.

			NOTE 1 - For example:
				A ::= IA5String (SIZE (3..6))			-- Length is encoded in a 2-bit bit-field.
				B ::= IA5String (SIZE (40000..40254))	-- Length is encoded in an 8-bit bit-field.
				C ::= IA5String (SIZE (0..32000))		-- Length is encoded in a 2-octet bit-field (octet-aligned in the ALIGNED variant).
				D ::= IA5String (SIZE (64000))			-- Length is not encoded.

			NOTE 2 - The effect of making no addition in the case of "n" equals zero is that padding to an octet 
						boundary does not occur when these procedures are invoked to add an octet-aligned-bit-field of zero 
						length, unless required by 11.5.
						길이 n이 0일 때 아무것도 추가하지 않는다는 뜻은, ALIGNED방식에서 일어나는 정렬 Padding 이 11.5에서 언급한 것처럼 
						별도로 요구하지 않는 한 일어나지 않는 것을 의미합니다.	*/
			Dz1Asn1PerIntInfo tgt = Dz1Asn1PerIntInfo_NULL;
			if (Dz1Asn1CodecPer_mk_cwn(&tgt, lb, lb, ub, Dz1Asn1PerMode_aligned, errp) == FALSE) ERR_OUT(errp);
			else
			{
				u64_t mask = 1;
				switch(tgt.size.present)
				{
				case Dz1Asn1PerIntSizePresent_bits:
					if (Dz1Asn1Stream_popBitsI64(src, &tgt.value, (s32_t)tgt.size.x.bits, errp) == FALSE) ERR_OUT(errp);
					else
					{
						mask = (mask << tgt.size.x.bits) - 1;
						ret = (ssize_t)((tgt.value & mask) + lb);
						Dz1Error_set(errp, 0);
					}
					break;
				case Dz1Asn1PerIntSizePresent_octet1:
					if (Dz1Asn1Stream_popAlign(src, errp) == FALSE) ERR_OUT(errp);
					else if (Dz1Asn1Stream_popBitsI64(src, &tgt.value, 8, errp) == FALSE) ERR_OUT(errp);
					else
					{
						ret = (ssize_t)((tgt.value & 0xFF) + lb);
						Dz1Error_set(errp, 0);
					}
					break;
				case Dz1Asn1PerIntSizePresent_octet2:
					if (Dz1Asn1Stream_popAlign(src, errp) == FALSE) ERR_OUT(errp);
					else if (Dz1Asn1Stream_popBitsI64(src, &tgt.value, 16, errp) == FALSE) ERR_OUT(errp);
					else
					{
						ret = (ssize_t)((tgt.value & 0xFFFF) + lb);
						Dz1Error_set(errp, 0);
					}
					break;
				default: ERR_SET_OUT(errp, EFAULT); break;
				}
			}
		}
		else
		{	/* 11.9.3.5	
			Otherwise (unconstrained length, or large "ub"), "n" is encoded and appended to the field-list 
			followed by the associated fields as specified below.
			그렇지 않은 경우(unconstrained-length 또는 큰 "ub") "n"이 아래에 지정된 대로(11.9.3.6 ~ 11.9.3.8.4에 따라)
			인코딩 되어 필드 목록에 추가되고 그 뒤에는 관련 필드가 추가됩니다.
			NOTE -	The lower bound, "lb", does not affect the length encodings specified in 11.9.3.6 to 11.9.3.8.4.
					최소값 lb는 11.9.3.6에서 11.9.3.8.4의 절차에서 효력을 발휘하지 않습니다.	*/
			if ((ret = _length_dec_no_cons(src, Dz1Asn1PerMode_aligned, errp)) < 0) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.3.5	
		Otherwise (unconstrained length, or large "ub"), "n" is encoded and appended to the field-list 
		followed by the associated fields as specified below.
		그렇지 않은 경우(unconstrained-length 또는 큰 "ub") "n"이 아래에 지정된 대로(11.9.3.6 ~ 11.9.3.8.4에 따라)
		인코딩 되어 필드 목록에 추가되고 그 뒤에는 관련 필드가 추가됩니다.
		NOTE -	The lower bound, "lb", does not affect the length encodings specified in 11.9.3.6 to 11.9.3.8.4.
				최소값 lb 는 11.9.3.6에서 11.9.3.8.4의 절차에서 효력을 발휘하지 않습니다.	*/
		if ((ret = _length_dec_no_cons(src, Dz1Asn1PerMode_aligned, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}


ssize_t Dz1Asn1CodecPer_length_enc(Dz1Asn1Stream *dst, u64_t len, u64_t lb, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	switch(mode)
	{
	case Dz1Asn1PerMode_aligned:
		if ((ret = _length_enc_align(dst, len, lb, _ub, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1PerMode_unaligned:
		if ((ret = _length_enc_unalign(dst, len, lb, _ub, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EINVAL); break;
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

ssize_t Dz1Asn1CodecPer_length_dec(Dz1Asn1Stream *src, u64_t lb, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	switch(mode)
	{
	case Dz1Asn1PerMode_aligned:
		if ((ret = _length_dec_align(src, lb, _ub, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1PerMode_unaligned:
		if ((ret = _length_dec_unalign(src, lb, _ub, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EINVAL); break;
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

/* 11.9.3.4	
	NOTE -	Normally small lengths are only used to indicate the length of the bitmap that prefixes the 
			extension addition values of a set or sequence type.
			Normally-Small-Lengths는 SET이나 SEQUENCE의 Extension-Addition 값 앞쪽에 붙이는 bitmap의 length를 
			표현할 때만 사용합니다. */

ssize_t Dz1Asn1CodecPer_NS_length_enc(Dz1Asn1Stream *dst, u64_t len, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (_ub != NULL && *_ub == 1)
	{	/* 11.9.1
		This subclause is not invoked if, in accordance with the specification of later clauses, 
		the value of the length determinant, "n", is fixed by the type definition (constrained by 
		PER-visible constraints) to a value less than 64K.
		후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
		본 절차가 호출되지 않습니다. */
		ret = (ssize_t)len;
		Dz1Error_set(errp, 0);
	}
	else if (len <= 64)
	{	/* 11.9.3.4	
		Where the length determinant is a normally small length and "n" is less than or equal to 64, 
		a single-bit bit-field shall be appended to the field-list with the bit set to 0, and the 
		value "n-1" shall be encoded as a non-negative-binary-integer into a 6-bit bit-field. 
		길이 결정자가 Normal-Small-Length로 결정되고 "n"이 64보다 작거나 같은 경우 1 비트 길이의 0값이 필드 
		목록에 추가되고 6비트 길이의 값 "n - 1"이 Non-Negative-Binary-Integer로 인코딩 됩니다.

		This shall be followed by the associated field, completing these procedures. 
		(쓸데없음)그 뒤에는 관련 필드(이 길이에 대한 Data) 추가하여 이 절차를 완료해야 합니다. */
		u8_t v = (u16_t)((len - 1) & 0x3F);	// 0x00 | 0x3F
		if (Dz1Asn1Stream_pushBits(dst, &v, 7, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.3.4	
		If "n" is greater than 64, a single-bit bit-field shall be appended to the field-list with the 
		bit set to 1, followed by the encoding of "n" as an unconstrained length determinant followed 
		by the associated field, according to the procedures of 11.9.3.5 to 11.9.3.8.4.
		"n"이 64보다 큰 경우 비트가 1로 설정된 한 비트 길이의 값이 필드 목록에 추가되어야 하며, 이어서 "n"을 
		11.9.3.5부터 11.9.3.8.4에 지정된 unconstrained-length 결정자로 인코딩하고 관련 필드(이 길이에 대한 
		Data)가 이어집니다. */
		if (Dz1Asn1Stream_pushBit1(dst, TRUE, errp) == FALSE) ERR_OUT(errp);
		else if ((ret = _length_enc_no_cons(dst, len, mode, errp)) < 0) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)len;
			Dz1Error_set(errp, 0);
		}
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

ssize_t Dz1Asn1CodecPer_NS_length_dec(Dz1Asn1Stream *src, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	bool_t is_big = FALSE;
	if (_ub != NULL && *_ub == 1)
	{	/* 11.9.1
		This subclause is not invoked if, in accordance with the specification of later clauses, 
		the value of the length determinant, "n", is fixed by the type definition (constrained by 
		PER-visible constraints) to a value less than 64K.
		후행 절에 의하여 길이 결정자 “n”이 (PER-Visible 제약 조건에 의해) 64K미만의 고정길이를 가지는 경우에는 
		본 절차가 호출되지 않습니다. */
		ret = (ssize_t)1;
		Dz1Error_set(errp, 0);
	}
	else if (Dz1Asn1Stream_popBit1(src, &is_big, errp) == FALSE) ERR_OUT(errp);
	else if (is_big == FALSE)
	{	/* 11.9.3.4	
		Where the length determinant is a normally small length and "n" is less than or equal to 64, 
		a single-bit bit-field shall be appended to the field-list with the bit set to 0, and the 
		value "n-1" shall be encoded as a non-negative-binary-integer into a 6-bit bit-field. 
		길이 결정자가 Normal-Small-Length로 결정되고 "n"이 64보다 작거나 같은 경우 1 비트 길이의 0값이 필드 
		목록에 추가되고 6비트 길이의 값 "n - 1"이 Non-Negative-Binary-Integer로 인코딩 됩니다.

		This shall be followed by the associated field, completing these procedures. 
		(쓸데없음)그 뒤에는 관련 필드(이 길이에 대한 Data) 추가하여 이 절차를 완료해야 합니다. */
		u8_t v = 0;
		if (Dz1Asn1Stream_popBitsI8(src, &v, 6, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)v & 0x3F;
			Dz1Error_set(errp, 0);
		}
	}
	else
	{	/* 11.9.3.4	
		If "n" is greater than 64, a single-bit bit-field shall be appended to the field-list with the 
		bit set to 1, followed by the encoding of "n" as an unconstrained length determinant followed 
		by the associated field, according to the procedures of 11.9.3.5 to 11.9.3.8.4.
		"n"이 64보다 큰 경우 비트가 1로 설정된 한 비트 길이의 값이 필드 목록에 추가되어야 하며, 이어서 "n"을 
		11.9.3.5부터 11.9.3.8.4에 지정된 unconstrained-length 결정자로 인코딩하고 관련 필드(이 길이에 대한 
		Data)가 이어집니다. */
		if ((ret = _length_dec_no_cons(src, mode, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return SELECT_BY_ERR(errp, ret, -1);
}
