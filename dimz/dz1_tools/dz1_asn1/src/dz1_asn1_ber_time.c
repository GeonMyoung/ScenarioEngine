#include "dz1_asn1_codec_ber.h"

bool_t Dz1Asn1PrimitiveStr_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OctetStr *src = (Dz1Asn1OctetStr *)_src;

	if (0) { }
	else if (_Dz1ElasticBuf_push(dst, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1PrimitiveStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)		ERR_SET_OUT(errp, EPERM);	// don't use constructed encoding
	else if (stk->len == Dz1Asn1BerLength_soc)			ERR_SET_OUT(errp, EPERM);	// don't use indefinite size
	else if (stk->len == 0)								ERR_SET_OUT(errp, EPERM);	// don't be 0 size
	else
	{
		ssize_t sz;
		u8_t buf[16];
		bool_t done = FALSE;
		Dz1Asn1WipValue *wip = NULL;
		Dz1ElasticBuf *wip_tim = NULL;

		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if (0) { }
				// initialize destination data struct
				else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_octet_str, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((wip_tim = wip->x.octet_str = Dz1ElasticBuf_new(32, FALSE, errp)) == NULL) ERR_OUT(errp);
				else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				if (0) { }
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((wip_tim = wip->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
				// read from STREAM
//				else if ((sz = Dz1Stream_read(src, buf, 16, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else if ((sz = Dz1Asn1Stream_popOctets(src, buf, 16, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				// apply buffer to destination data struct
				else
				{
					ret += sz;
					dst->u64data += sz;

					if (_Dz1ElasticBuf_push(wip_tim, buf, sz, errp) == FALSE) ERR_OUT(errp);
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
	}
	return errp->code == 0 ? ret : -1;
}

/*
8.26.1	Encoding for values of the TIME type
		NOTE -	The defined time types are subtypes of the TIME type, with the same tag, and have the same encoding as the TIME type.
				정의된 시간 유형은 TIME 유형의 하위 유형으로 태그가 동일하고 TIME 유형과 인코딩이 동일합니다.

8.26.1.1	The encoding of the TIME type shall be primitive.
			TIME 유형의 인코딩은 PRIMITIVE이어야 합니다.

8.26.1.2	The contents octets shall be the UTF-8 encoding of the value notation, after the removal of initial and final QUOTATION MARK (34) characters.
			내용 옥텟은 초기 및 최종 QUOTATION-MARK(34) 문자를 제거한 후 값 표기법의 UTF-8 인코딩이어야 합니다.
*/

/*
8.26.2		Encoding for values of the DATE type
8.26.2.1	The encoding of the DATE type shall be primitive.
8.26.2.2	The contents octets shall be the UTF-8 encoding of the value notation, after the removal of 
			initial and final QUOTATION MARK (34) characters and all HYPHEN-MINUS (45) characters.
*/
/*
8.26.3		Encoding for values of the TIME-OF-DAY type
8.26.3.1	The encoding of the TIME-OF-DAY type shall be primitive.
8.26.3.2	The contents octets shall be the UTF-8 encoding of the value notation, after the removal of 
			initial and final QUOTATION MARK (34) characters and all COLON (58) characters.
*/
/*
8.26.4		Encoding for values of the DATE-TIME type
8.26.4.1	The encoding of the DATE-TIME type shall be primitive.
8.26.4.2	The contents octets shall be the UTF-8 encoding of the value notation, after the removal of 
			initial and final QUOTATION MARK (34) characters, all HYPHEN-MINUS (45) characters, 
			all COLON (58) characters, and the LATIN CAPITAL LETTER T character. 
*/
/*
8.26.5		Encoding for values of the DURATION type
8.26.5.1	The encoding of the DURATION type shall be primitive.
8.26.5.2	The contents octets shall be the UTF-8 encoding of the value notation, after the removal of 
			initial and final QUOTATION MARK (34) characters and the LATIN CAPITAL LETTER P character.
*/
/*
### X.680
47.3	The type is defined, using ASN.1, as follows:
			UTCTime ::= [UNIVERSAL 23] IMPLICIT VisibleString
	with the values of the VisibleString restricted to strings of characters which are the juxtaposition of:
	VisibleString의 문자를 사용하는 UTCTime은 다음의 형식으로 제한됩니다.

	a)	the six digits YYMMDD where YY is the two low-order digits of the Christian year, MM is the month (counting January as 01), and DD is the day of the month (01 to 31); and
		6자리 YYMMDD, 여기서 YY는 연도의 하위 2자리, MM은 월(1월을 01로 계산), DD는 해당 월의 일(01~31)입니다.
		그리고

	b)	either:
		1)	the four digits hhmm where hh is hour (00 to 23) and mm is minutes (00 to 59); or
			네 자리 hhmm (여기서 hh는 시간(00~23)이고 mm은 분(00~59)입니다.) 또는
		2)	the six digits hhmmss where hh and mm are as in 1) above, and ss is seconds (00 to 59); and
			6자리 hhmmss (여기서 hh 및 mm는 위의 1)과 같고 ss는 초(00~59) 입니다.)
		그리고
	c)	either:
		1)	the character Z; or
			문자 Z를 쓰거나,
		2)	one of the characters + or -, followed by hhmm, where hh is hour and mm is minutes.
			+ 또는 - 문자 다음에 hhmm가 옵니다. 여기서 hh는 시간이고 mm는 분입니다.

	The alternatives in b) above allow varying precisions in the specification of the time.
	위 b)의 대안은 시간 지정의 다양한 정밀도를 허용합니다.

	In alternative c) 1), the time is coordinated universal time. In alternative c) 2), the time (t1) specified by a) and b) above is the local time; 
	the time differential (t2) specified by c) 2) above enables the coordinated universal time to be determined as follows:
		Coordinated universal time is t1 - t2
	c)의 1) 형식을 사용하면 시간 값이 협정 세계시임을 의미합니다. c)의 2)형식을 사용하면 시간값이 현지 시간임을 의미합니다. 
	이때 시간값을 t1, 현지 시간차 값을 t2라고 하면 협정 세계시를 계산하는 공식은 t1 - t2 입니다.

	EXAMPLE 1 - If local time is 7am on 2 January 1982 and coordinated universal time is 12 noon on 2 January 1982, the value of UTCTime is either of:
		현지 시간이 1982년 1월 2일 오전 7시이고 협정 세계시가 1982년 1월 2일 정오 12시인 경우 UTCTime의 값은 다음 중 하나입니다.
		-	"8201021200Z"; or
		-	"8201020700-0500".
	EXAMPLE 2 - If local time is 7am on 2 January 2001 and coordinated universal time is 12 noon on 2 January 2001, the value of UTCTime is either of:
		현지 시간이 2001년 1월 2일 오전 7시이고 협정 세계시가 2001년 1월 2일 정오인 경우 UTCTime의 값은 다음 중 하나입니다.
		-	"0101021200Z"; or
		-	"0101020700-0500".

47.4	The tag shall be as defined in 47.3.
		태그는 47.3에 정의된 대로여야 합니다.

47.5	The value notation shall be the value notation for the VisibleString defined in 47.3.
		값 표기법은 47.3에 정의된 VisibleString에 대한 값 표기법이어야 합니다.

### X.690

8.25	Encoding for values of the useful types
		The following "useful types" shall be encoded as if they had been replaced by their definitions given in clauses 46-48 of Rec. ITU-T X.680 | ISO/IEC 8824-1:
		다음 "유용한 유형"은 X.680의 46-48절에 제공된 정의로 대체된 것처럼 인코딩됩니다.
		-	generalized time; 	[UNIVERSAL 24] 	IMPLICIT VisibleString
		-	universal time; 	[UNIVERSAL 23] 	IMPLICIT VisibleString
		-	object descriptor.	[UNIVERSAL 7] 	IMPLICIT GraphicString

11.8	UTCTime
11.8.1	The encoding shall terminate with "Z", as described in the ITU-T X.680 | ISO/IEC 8824-1 clause on UTCTime.
		인코딩은 X.680의 UTCTime 절에 설명된 대로 "Z"로 종료해야 합니다.

11.8.2	The seconds element shall always be present.
		초 요소는 항상 존재해야 합니다.

11.8.3	Midnight (GMT) shall be represented in the form:
		자정(GMT)은 다음 형식으로 표시됩니다.

			"YYMMDD000000Z"

		where "YYMMDD" represents the day following the midnight in question.
		여기서 "YYMMDD"는 해당 자정 다음 날을 나타냅니다.
		-> "YYMMDD000000Z"는 해당 날의 시작을 의미합니다.

11.8.4	Examples of valid representations
			"920521000000Z"
			"920622123421Z"
			"920722132100Z"
11.8.5	Examples of invalid representations
			"920520240000Z"	(midnight represented incorrectly)
			"9207221321Z"	(seconds of "00" omitted)
*/
/*
###############################################################################
### X.680
###############################################################################

46		Generalized time
		NOTE 1 - Earlier versions of this Recommendation | International Standard used different text (due to the evolution of the ISO time standards), 
		but the technical content is unchanged from the first version of this Recommendation | International Standard.
		이 권장 표준의 이전 버전은 다른 텍스트를 사용했지만(ISO 시간 표준의 발전으로 인해) 기술적 내용은 이 권장 표준의 첫 번째 버전에서 변경되지 않았습니다.

		NOTE 2 - The time type (see clause 38) gives more flexibility and should be preferred.
		시간 유형(38절 참조)은 더 많은 유연성을 제공하며 선호되어야 합니다.

46.1	This type shall be referenced by the name:
			GeneralizedTime
46.2	The type consists of a calendar date, together with:
		유형은 다음과 함께 달력 날짜로 구성됩니다.

		a)	a local time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to an accuracy of:
			하루 중 현지 시간(하루 시작의 자정 포함, 하루 종료의 자정 제외)의 정확도:

			1)	hours, minutes, and seconds (or seconds and fractions of a second to any number of decimal places); or
				시, 분, 초(또는 소수 자릿수까지의 초 및 분수);
			또는
			2)	hours and minutes (or minutes and fractions of a minute to any number of decimal places); or
				시간 및 분(또는 소수점 이하 자릿수까지의 분 및 분수);
			또는
			3)	hours (or hours and fractions of an hour to any number of decimal places); or
				시간(또는 소수점 이하 자릿수까지의 시간 및 분수);
		또는
		b)	a UTC time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to any of the accuracies listed in a) above; or
			하루 중 UTC 시간(하루 시작의 자정 포함, 하루 종료의 자정 제외), 위의 a)에 나열된 정확도;
		또는
		c)	a local time of day as specified in a) above, together with the difference between local time and UTC.
			현지 시간과 UTC의 차이와 함께 위의 a)에 지정된 현지 시간.

			NOTE - The time difference component is positive if the local time is ahead of UTC.
			현지 시간이 UTC보다 빠르면 시차 성분이 양수입니다.

46.3	The type is defined, using ASN.1, as follows:
		유형은 다음과 같이 ASN.1을 사용하여 정의됩니다.

			GeneralizedTime ::= [UNIVERSAL 24] IMPLICIT VisibleString

		with the values of the VisibleString restricted to strings of characters which are either:
		VisibleString의 값은 다음 중 하나인 문자열로 제한됩니다.

		a)	a specification of a calendar date followed by a local time, consisting of: 
			다음으로 구성된 달력 날짜와 현지 시간 지정:

			1)	a string representing the calendar date, (as specified in ISO 8601, 4.1.2.2 - Basic format); followed by:
				달력 날짜를 나타내는 문자열(ISO 8601, 4.1.2.2 - 기본 형식에 지정됨)  -> YYYYMMDD
				NOTE 1 - This specifies a four-digit representation of the year, a two-digit representation of the month 
				and a two-digit representation of the day, without use of separators.
				구분 기호를 사용하지 않고 연도의 네 자리 표시, 월의 두 자리 표시 및 일의 두 자리 표시를 지정합니다.
			다음에:

			2)	a string representing the time of day to an accuracy of one hour, one minute, one second, or fractions of a second (to any degree of accuracy), 
				using either comma or full stop as the decimal sign (as specified in ISO 8601, 4.2.2.2 and 4.2.2.3 - Basic format); optionally followed by:
				쉼표 또는 마침표를 소수점 기호로 사용하여 1시간, 1분, 1초 또는 1초의 소수부(정확도에 관계없이)의 정확도로 시간을 나타내는 문자열
				(ISO 8601, 4.2.2.2 및 4.2.2.3 - 기본 형식) 
				-> HH[MM[SS]]]
			선택적으로:

			3)	a decimal fraction of a minute if seconds are omitted, or a decimal fraction of an hour if minutes and seconds are omitted (as specified in ISO 8601, 4.2.2.4); or
				초가 생략된 경우 분의 소수점 이하 자릿수, 분과 초가 생략된 경우 시간의 소수점 이하 자릿수(ISO 8601, 4.2.2.4에 명시된 대로)
				-> [.ffffff…]

				NOTE 2 - ISO 8601 specifies the use of either a comma or a full stop as the decimal sign. There are no other separators present. 
				It is recommended that in any given ASN.1 specification, either comma or full stop be consistently used as the decimal sign.
				ISO 8601은 쉼표 또는 마침표를 소수점 기호로 사용하도록 지정합니다. 다른 구분 기호가 없습니다. 
				주어진 ASN.1 사양에서 쉼표 또는 마침표를 소수점 기호로 일관되게 사용하는 것이 좋습니다.
		또는
		b)	a specification of a calendar date and a UTC time consisting of the characters in a) above followed by an upper-case letter Z; or
			위의 a) 문자와 대문자 Z로 구성된 달력 날짜 및 UTC 시간 지정
			-> YYYYMMDDHH[MM[SS]]][.fffff…]Z
		또는
		c)	a specification of a calendar date, the local time, and the exact difference between local time and UTC as specified in ISO 8601, 
			with the minutes component optionally omitted if the difference is an integral number of hours.
			ISO 8601에 명시된 대로 달력 날짜, 현지 시간 및 현지 시간과 UTC 간의 정확한 차이를 지정하고, 차이가 정수 시간인 경우 분 구성요소는 선택적으로 생략됩니다.

			NOTE 3 - Early work on ASN.1 canonical encoding rules assumed that there was no actual concept of accuracy, so that an abstract value 
			that might be represented with a seconds component of 3.000 was regarded as the same abstract value as one that was represented with a seconds component of 3, 
			and forbade the use of trailing zeros in canonical encoding fractional parts, and forbade the omission of seconds or minutes and seconds.
			ASN.1 표준 인코딩 규칙에 대한 초기 작업에서는 정확도에 대한 실제 개념이 없다고 가정했으며, 3.000으로 표현한 초 값과 3으로 표현되는 초 값이 동일한 값으로 간주됩니다. 
			표준 인코딩 분수 부분에서 후행 0의 사용을 금지하고 초 또는 분 및 초 생략을 금지합니다.

			It also supported only the use of UTC time, not local time or local time with a time difference component. 
			This has not been changed in later editions of the ASN.1 standards, for backwards compatibility. 
			또한 현지 시간 또는 시차 구성 요소가 있는 현지 시간이 아닌 UTC 시간만 사용하도록 지원했습니다.
			이것은 이전 버전과의 호환성을 위해 ASN.1 표준의 이후 버전에서 변경되지 않았습니다.

			The TIME type (introduced into ASN.1 in 2004) recognizes that abstract values can have an associated accuracy, and that (e.g.) 
			the representations of seconds as 3.000 and 3 produces different abstract values, and that local time and UTC specifications represent different abstract values. 
			TIME 유형은 추상 값이 관련 정확도를 가질 수 있다는 것과 (예를 들어) 초를 3.000 및 3으로 표현하는 것이 서로 다른 추상 값을 생성하고
			현지 시간 및 UTC 사양이 서로 다른 추상 값을 나타낸다는 것을 인식합니다.

			The canonical encoding rules for TIME encode the full range of its abstract values, so use of TIME may be preferred in new specifications to the use of GeneralizedTime.
			TIME에 대한 "표준 인코딩 규칙"은 추상 값의 전체 범위를 인코딩하므로 새 사양에서는 GeneralizedTime을 사용하는 것보다 TIME을 사용하는 것이 더 좋습니다.

		In case c), the part of the string formed as in case a) represents the local time (t1), and the (signed) time difference (t2) enables UTC to be determined. 
		If t2 is positive, local time is ahead of UTC. We can thus determine UTC as:
		c)의 경우, a)와 같이 형성된 문자열의 일부는 현지 시간(t1)을 나타내고, (부호가 붙은) 시간 차이(t2)는 UTC가 결정될 수 있도록 합니다. 
		t2가 양수이면 현지 시간이 UTC보다 빠릅니다. 따라서 UTC를 다음과 같이 결정할 수 있습니다.

			UTC is t1 - t2

		EXAMPLES
			Case a)
			"19851106210627.3"
			Local time 6 minutes, 27.3 seconds after 9 pm on 6 November 1985.
			현지 시간 1985년 11월 6일 오후 9시 이후 6분 27.3초.
			-> 1985-11-06 21:06:27.3

			Case b)
			"19851106210627.3Z"
			Coordinated universal time as above.
			위와 같이 협정 세계시. 
			-> 1985-11-06 21:06:27.3

			Case c)
			"19851106210627.3-0500"
			Local time as in example a), with a coordinated universal time of 6 minutes, 27.3 seconds after 2 am on 7 November 1985.
			1985년 11월 7일 오전 2시 이후 6분 27.3초의 협정 세계시를 사용하는 예 a)와 같은 현지 시간.
			-> 1985-11-06 21:06:27.3 Local => t1 - (-05:00) = t1 + 05:00
			-> 1985-11-07 02:06:27.3 UTC

			Case d)
			"198511062106.456"
			Local time 6.456 minutes after 9 pm on 6 November 1985.
			1985년 11월 6일 오후 9시 이후 현지 시간 6.456분.
			-> 1985-11-06 21:6.456

			Case e)
			"1985110621.14159"
			Local time 0.14159 hours after 9 pm on 6 November 1985.
			현지 시간 1985년 11월 6일 오후 9시 이후 0.14159시간.
			-> 1985-11-06 21.14159

46.4	The tag shall be as defined in 46.3.
		태그는 46.3에 정의된 대로여야 합니다.

46.5	The value notation shall be the value notation for the VisibleString defined in 46.3.
		값 표기법은 46.3에 정의된 VisibleString에 대한 값 표기법이어야 합니다.

###############################################################################
### X.690
###############################################################################

8.25	Encoding for values of the useful types
		The following "useful types" shall be encoded as if they had been replaced by their definitions given in clauses 46-48 of Rec. ITU-T X.680 | ISO/IEC 8824-1:
		다음 "유용한 유형"은 X.680의 46-48절에 제공된 정의로 대체된 것처럼 인코딩됩니다.
		-	generalized time; 	[UNIVERSAL 24] 	IMPLICIT VisibleString
		-	universal time; 	[UNIVERSAL 23] 	IMPLICIT VisibleString
		-	object descriptor.	[UNIVERSAL 7] 	IMPLICIT GraphicString

11.7	GeneralizedTime
11.7.1	The encoding shall terminate with a "Z", as described in the Rec. ITU-T X.680 | ISO/IEC 8824-1 clause on GeneralizedTime.
		인코딩은 GeneralizedTime의 X.680 절에 설명된 대로 "Z"로 종료되어야 합니다.

11.7.2	The seconds element shall always be present.
		초 요소는 항상 존재해야 합니다.

11.7.3	The fractional-seconds elements, if present, shall omit all trailing zeros; if the elements correspond to 0, they shall be wholly omitted, 
		and the decimal point element also shall be omitted.
		fractional-seconds 요소가 있는 경우 모든 후행 0을 생략해야 합니다. 요소가 0에 해당하면 완전히 생략되고 소수점 요소도 생략됩니다.

	EXAMPLE
		A second element of "26.000" shall be represented as "26"; a seconds element of "26.5200" shall be represented as "26.52".
		"26.000"의 초 요소는 "26"으로 표시됩니다. "26.5200"의 초 요소는 "26.52"로 표시됩니다.

11.7.4	The decimal point element, if present, shall be the point option ".".
		소수점 요소가 있는 경우 소수점 옵션 "."을 사용해야 합니다.

11.7.5	Midnight (GMT) shall be represented in the form:
		자정(GMT)은 다음 형식으로 표시됩니다.

			"YYYYMMDD000000Z"

		where "YYYYMMDD" represents the day following the midnight in question.
		여기서 "YYYYMMDD"는 해당 자정 다음 날을 나타냅니다.
		-> “YYYYMMDD000000Z”는 해당일의 시작시간을 의미합니다.

	EXAMPLE
		Examples of valid representations:
			"19920521000000Z"
			"19920622123421Z"
			"19920722132100.3Z"
		Examples of invalid representations:
			"19920520240000Z"		(midnight represented incorrectly)
			"19920622123421.0Z"		(spurious trailing zeros)
			"19920722132100.30Z"	(spurious trailing zeros)
*/
int _avoid_warning_no_symbol_time_ = 0;