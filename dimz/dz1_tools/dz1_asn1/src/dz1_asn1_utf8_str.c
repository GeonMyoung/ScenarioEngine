#include "dz1_asn1_codec.h"

/*
7.3			Alternative encodings are permitted by the basic encoding rules as a sender's option. 
			발신자의 옵션으로 기본 인코딩 규칙에 따라 대체 인코딩이 허용됩니다.

			Receivers who claim conformance to the basic encoding rules shall support all alternatives.
			기본 인코딩 규칙을 준수한다고 주장하는 수신기는 모든 대안을 지원해야 합니다.

8.23		Encoding for values of the restricted character string types

8.23.1		The data value consists of a string of characters from the character set specified in the ASN.1 type definition. 
			데이터 값은 ASN.1 유형 정의에 지정된 문자 집합의 문자열로 구성됩니다.

8.23.2 	    Each data value shall be encoded independently of other data values of the same type. 
			각 데이터 값은 동일한 유형의 다른 데이터 값과 독립적으로 인코딩되어야 합니다.

8.23.3		Each character string type shall be encoded as if it had been declared: 
			각 문자열 유형은 다음과 같이 선언된 것처럼 인코딩됩니다:

			[UNIVERSAL x] IMPLICIT OCTET STRING

			where x is the number of the universal class tag assigned to the character string type in Rec. ITU-T X.680 | ISO/IEC 8824-1. 
			여기서 x는 "Rec. ITU-T X.680 | ISO/IEC 8824-1"에서 문자열 유형에 할당된 범용 클래스 태그의 번호입니다.

			The value of the octet string is specified in 8.23.4 and 8.23.5.
			옥텟 문자열의 값은 8.23.4 및 8.23.5에 지정되어 있습니다.

8.23.4		Where a character string type is specified in X.680 by direct reference to an enumerating table (NumericString and PrintableString),
			the value of the octet string shall be that specified in 8.23.5 for a VisibleString type with the same character string value.
			문자열 유형이 열거 테이블(NumericString 및 PrintableString)에 대한 직접 참조에 의해 X.680에 지정된 경우 
			옥텟 문자열의 값은 동일한 문자열 값을 갖는 VisibleString 유형에 대해 8.23.5에 지정된 값이어야 합니다.

8.23.5		For restricted character strings apart from UniversalString, UTF8String and BMPString, the octet string shall contain the octets specified 
			in ISO/IEC 2022 for encodings in an 8-bit environment, using the escape sequence and character codings registered in accordance with ISO/IEC 2375.
			UniversalString, UTF8String, BMPString을 제외한 제한된 문자열의 경우, octet string 은 ISO/IEC 2375에 따라 등록된 이스케이프 시퀀스 및 문자 코딩을 
			사용하여 8비트 환경의 인코딩에 대해 ISO/IEC 2022에 지정된 옥텟을 포함해야 합니다.

8.23.5.1	An escape sequence shall not be used unless it is one of those specified by one of the registration numbers used to define the character string type in X.680.
			이스케이프 시퀀스는 X.680에서 문자열 유형을 정의하는 데 사용되는 등록 번호 중 하나로 지정된 경우가 아니면 사용되지 않습니다.

8.23.5.2	At the start of each string, certain registration numbers shall be assumed to be designated as G0 and/or C0 and/or C1, and invoked (using the terminology of ISO/IEC 2022).
			각 문자열의 시작 부분에서 특정 등록 번호는 G0 및/또는 C0 및/또는 C1으로 지정되고 호출되는 것으로 가정해야 합니다.

8.23.5.3	Certain character string types shall not contain explicit escape sequences in their encodings; in all other cases, 
			any escape sequence allowed by 8.23.5.1 can appear at any time, including at the start of the encoding.
			특정 문자열 유형은 인코딩에 명시적 이스케이프 시퀀스를 포함하지 않아야 합니다. 다른 모든 경우에 8.23.5.1에서 허용하는 
			모든 이스케이프 시퀀스는 인코딩 시작을 포함하여 언제든지 나타날 수 있습니다.

			Table 3 lists the types for which explicit escape sequences are allowed.
			표 3은 명시적 이스케이프 시퀀스가 허용되는 유형을 나열합니다.

8.23.5.4	Announcers shall not be used unless explicitly permitted by the user of ASN.1.
			ASN.1의 사용자가 명시적으로 허용하지 않는 한 아나운서는 사용되지 않습니다.

			NOTE –	The choice of ASN.1 type provides a limited form of announcer functionality. 
					ASN.1의 CHOICE Type 은 제한된 형태의 아나운서 기능을 제공합니다.
					Specific application protocols may choose to carry announcers in other protocol elements, or to specify in detail the manner of use of announcers.
					특정 응용 프로토콜은 다른 프로토콜 요소에 아나운서를 포함하거나 아나운서 사용 방식을 자세히 지정하도록 선택할 수 있습니다.

8.23.6		The above example illustrates three of the (many) possible forms available as a sender's option.
			위의 예는 발신자의 옵션으로 사용할 수 있는 가능한 세 가지 (다양한) 양식을 보여줍니다.
			Receivers are required to handle all permitted forms (see 7.3).
			수신자는 모든 허용된 양식을 처리해야 합니다(7.3 참조).

8.23.9		The C0 and C1 control functions of ISO/IEC 6429 may be used with the following exceptions.
			ISO/IEC 6429의 C0 및 C1 제어 기능은 다음을 제외하고 사용할 수 있습니다.

			NOTE 1 –	The effect of this sub clause is to allow the useful control functions such as LF, CR, TAB, etc., while forbidding the use of escapes to other character sets.
						이 하위 절의 효과는 LF, CR, TAB 등과 같은 유용한 제어 기능을 허용하면서 다른 문자 집합에 대한 이스케이프 사용을 금지하는 것입니다.

			NOTE 2 –	The C0 and C1 control functions are each encoded in two octets for BMPString and four for UniversalString.
						C0 및 C1 제어 기능은 각각 BMPString의 경우 2개의 옥텟으로 인코딩되고 UniversalString의 경우 4개의 옥텟으로 인코딩됩니다.

			a)	Announcer escape sequences defined in ISO/IEC 2022 shall not be used.
				ISO/IEC 2022에 정의된 아나운서 이스케이프 시퀀스는 사용되지 않습니다.

				NOTE 3 –	The assumed character coding environment is ISO/IEC 10646.
							가정된 문자 코딩 환경은 ISO/IEC 10646입니다.

			b)	Designating or identifying escape sequences defined in ISO/IEC 2022 shall not be used, including the identifying escape sequences permitted by ISO/IEC 10646, 17.2 and 17.4.
				ISO/IEC 10646, 17.2 및 17.4에서 허용하는 식별 이스케이프 시퀀스를 포함하여 ISO/IEC 2022에 정의된 이스케이프 시퀀스를 지정하거나 식별하는 것은 사용하지 않아야 합니다.

				NOTE 4 –	ASN.1 allows the use of the PermittedAlphabet subtype notation to select the set of allowed characters. 
							ASN.1은 허용된 문자 집합을 선택하기 위해 PermittedAlphabet 하위 유형 표기법의 사용을 허용합니다.

							PermittedAlphabet is also used to select the level of implementation of ISO/IEC 10646.
							PermittedAlphabet은 ISO/IEC 10646의 구현 수준을 선택하는 데에도 사용됩니다.

							BMPString is always used for the two-octet form and UniversalString for the four-octet form.
							BMPString은 항상 2옥텟 형식에 사용되며 UniversalString은 4옥텟 형식에 사용됩니다.

			c)	Invoking escape sequence or control sequences of ISO/IEC 2022 shall not be used, such as SHIFT IN (SI), SHIFT OUT (SO), or LOCKING SHIFT FOR G3 (SS3)
				SHIFT IN(SI), SHIFT OUT(SO) 또는 LOCKING SHIFT FOR G3(SS3)와 같은 ISO/IEC 2022의 이스케이프 시퀀스 또는 제어 시퀀스를 호출하는 것은 사용되지 않습니다.

			d)	The coding shall conform to ISO/IEC 10646 and remain in that code set.
				코딩은 ISO/IEC 10646을 준수해야 하며 해당 코드 세트에 남아 있어야 합니다.

			e)	Control sequences for identifying subsets of graphic characters according to ISO/IEC 10646, 16.3, shall not be used.
				ISO/IEC 10646, 16.3에 따라 그래픽 문자의 하위 집합을 식별하기 위한 제어 시퀀스는 사용되지 않습니다.

				NOTE 5 –	ASN.1 applications use subtyping to indicate subsets of the graphic characters of ISO/IEC 10646 and 
							to select the ISO/IEC 10646 cells that correspond to the control characters of ISO/IEC 6429.
							ASN.1 응용 프로그램은 ISO/IEC 10646의 그래픽 문자의 하위 집합을 나타내고 ISO/IEC 6429의 제어 문자에 해당하는 
							ISO/IEC 10646 셀을 선택하기 위해 하위 유형 지정을 사용합니다.

			f)	The escape sequences of ISO/IEC 10646, 16.5, shall not be used to switch to ISO/IEC 2022 codes.
				ISO/IEC 10646, 16.5의 이스케이프 시퀀스는 ISO/IEC 2022 코드로 전환하는 데 사용되지 않습니다.


9			Canonical encoding rules
9.2			String encoding forms
			Bitstring, octetstring, and restricted character string values shall be encoded with a primitive encoding if they would require no more than 1000 contents octets, 
			and as a constructed encoding otherwise. 
			비트스트링, 옥텟스트링 및 제한된 문자열 값은 1000개 이하의 콘텐츠 옥텟이 필요한 경우 "PRIMITIVE"로 인코딩되고 그렇지 않은 경우 "CONSTRUCTED"로 인코딩됩니다.

			The string fragments contained in the constructed encoding shall be encoded with a primitive encoding. 
			구성된 인코딩에 포함된 문자열 조각은 "PRIMITIVE"로 인코딩되어야 합니다.

			The encoding of each fragment, except possibly the last, shall have 1000 contents octets. (Contrast with 8.23.6.)  
			마지막을 제외한 각 조각의 인코딩은 1000 개의 목차 옥제를 가져야합니다. (8.23.6과 대조)

			The last fragment shall have at least one, and no more than 1000, contents octets.
			마지막 프래그먼트는 1개 이상 1000개 이하의 콘텐츠 옥텟을 가져야 합니다.

10			Distinguished encoding rules
10.2		String encoding forms
			For bitstring, octetstring and restricted character string types, the constructed form of encoding shall not be used. (Contrast with 8.23.6.)
			비트스트링, 옥텟스트링 및 제한된 문자열 유형의 경우 "CONSTRUCTED" 형식의 인코딩이 사용되지 않습니다. (8.23.6과 대조)

*/

