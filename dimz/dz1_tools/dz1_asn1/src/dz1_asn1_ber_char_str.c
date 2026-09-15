#include "dz1_asn1_codec_ber.h"

/*
### X.680
44		Definition of unrestricted character string types
		This clause defines a type whose values are the values of any character abstract syntax.
		이 절은 값이 모든 문자 추상 구문의 값을 가지는 유형을 정의합니다.

		In an OSI environment, this abstract syntax may be part of the OSI defined context set.
		OSI 환경에서 이 추상 구문은 OSI 정의 컨텍스트 세트의 일부일 수 있습니다.

		Otherwise, it is referenced directly for each instance of use of the unrestricted character string type.
		그렇지 않으면 Unrestricted-Character-String 유형이 사용하는 각 인스턴스를 직접 참조합니다.

		NOTE 1 -	A character abstract syntax (and one or more corresponding character transfer syntaxes) 
					can be defined by any organization able to allocate ASN.1 OBJECT IDENTIFIERs.
					문자 추상 구문(및 하나 이상의 해당 문자 전송 구문)은 ASN.1 OBJECT IDENTIFIER를 
					할당할 수 있는 조직에서 정의할 수 있습니다.

		NOTE 2 -	Profiles produced by a community of interest will normally determine the character abstract syntaxes and character transfer syntaxes 
					that are to be supported for specific instances or groups of instances of CHARACTER STRING.
					관심 커뮤니티(프로필 생성기관)에서 생성한 프로필은 일반적으로 CHARACTER STRING의 특정 인스턴스 
					또는 인스턴스 그룹에 대해 지원되는 문자에 대해 abstract syntaxes 및 transfer syntaxes 를 결정합니다.

		It will be usual in OSI applications to include reference to supported syntaxes in an OSI Protocol Implementation Conformance Statement.
		OSI 응용 프로그램에서 OSI Protocol Implementation Conformance Statement 에 지원되는 구문에 대한 참조를 포함하는 것이 일반적입니다.

44.1	The unrestricted character string type (see 3.8.89) shall be referenced by the notation "UnrestrictedCharacterStringType":
		unrestricted character string 유형(3.8.89 참조)은 "UnrestrictedCharacterStringType" 표기법으로 참조됩니다.

		UnrestrictedCharacterStringType ::= CHARACTER STRING

44.2	This type has a tag which is universal class, number 29.
		이 유형에는 UNIVERSAL 29인 태그를 사용합니다.

44.3	The type consists of values representing:
		유형은 다음을 나타내는 값으로 구성됩니다.

		a)	a character string value that may, but need not, be the value of an ASN.1 character string type; and
			ASN.1 문자열 유형의 값일 수 있지만 반드시 그럴 필요는 없는 문자열 값

		b)	identification (separately or together) of:
			1)	a character abstract syntax; and
				문자 추상 구문의 식별(별도 또는 함께)

			2)	the character transfer syntax.
				문자 전송 구문의 식별(별도 또는 함께).

44.4	The unrestricted character string type has an associated type. 
		Unrestricted Character String 유형에는 연결된 유형이 있습니다.

		This associated type is used to support its value and subtype notations.
		이 연관된 유형은 값 및 하위 유형 표기법을 지원하는 데 사용됩니다.

44.5	The associated type for value definition and sub-typing, assuming an automatic tagging environment, is (with normative comments):
		자동 태깅 환경을 가정할 때 값 정의 및 하위 유형 지정에 대한 관련 유형은 다음과 같습니다(표준 주석 포함).

		SEQUENCE {
			identification				CHOICE {
				syntaxes					SEQUENCE {					--  Abstract and transfer syntax object identifiers
					abstract					OBJECT IDENTIFIER,
					transfer					OBJECT IDENTIFIER 
				},
				syntax						OBJECT IDENTIFIER,			-- A single object identifier for identification of the abstract and transfer syntaxes
				presentation-context-id		INTEGER,					-- (Applicable only to OSI environments)
																				-- The negotiated OSI presentation context identifies the
																				-- abstract and transfer syntaxes
				context-negotiation			SEQUENCE 
				{																-- (Applicable only to OSI environments)
					presentation-context-id		INTEGER,				-- Context-negotiation in progress, presentation-context-id identifies only the  abstract-syntax,
					transfer-syntax				OBJECT IDENTIFIER		-- so the transfer syntax shall be specified
				},
				transfer-syntax				OBJECT IDENTIFIER,			-- The type of the value (for example, specification that it is the value of an ASN.1 type) 
																		-- is fixed by the application designer (and hence known to both sender and receiver).
																		-- This case is provided primarily to support selective-field-encryption (or other encoding transformations)
																		-- of an ASN.1 type
				fixed						NULL						-- The data value is the value of a fixed ASN.1 type (and hence known to both sender and receiver)
				
			},
			data-value-descriptor		ObjectDescriptor  OPTIONAL,		-- This provides human-readable identification of the class of the value
			string-value				OCTET STRING 
		}
		(WITH COMPONENTS {
			... ,
			data-value-descriptor  ABSENT
		})

		NOTE -	The unrestricted character string type does not allow the inclusion of a data-value-descriptor value together with the identification. 
				Unrestricted Character String 유형은 ID와 함께 data-value-descriptor 값을 포함하는 것을 허용하지 않습니다.

				However, the definition of the associated type provided here underlies the commonalities which exist between the Embedded-PDV type, 
				the External type and the unrestricted character string type.
				그러나 여기에 제공된 관련 유형의 정의는 Embedded-PDV 유형, External 유형 및 Unrestricted Character String 유형 사이에 존재하는 공통점의 기초가 됩니다.

44.6	The text of 36.6 and 36.7 also applies to the unrestricted character string type.
		36.6 및 36.7의 텍스트는 Unrestricted Character String 유형에도 적용됩니다.

44.7	The value notation shall be the value notation for the associated type defined in 44.5, where the value of the string-value component 
		of type OCTET STRING represents an encoding using the transfer syntax specified in identification.
		값 표기법은 44.5에 정의된 관련 유형에 대한 값 표기법이어야 하며, 여기서 OCTET STRING 유형의 string-value 구성 요소 값은 
		identification 에 지정된 transfer-syntax 를 사용하는 인코딩을 나타냅니다.

### X.690
8.24	Encoding for values of the unrestricted character string type
8.24.1	The encoding of a value of the unrestricted character string type shall be the BER encoding of the type as defined in 44.5 of Rec. ITU-T X.680 | ISO/IEC 8824-1.
		UnrestrictedCharacterString 유형 값의 인코딩은 X.680의 44.5에 정의된 유형의 BER 인코딩이어야 합니다.

8.24.2	The contents of the string-value OCTET STRING shall be the encoding of the abstract character string value of 
		the unrestricted character string type [see 44.3 a) of Rec. ITU-T X.680 | ISO/IEC 8824-1] using the identified character transfer syntax, 
		and the value of all other fields shall be the same as the values appearing in the abstract value.
		string-value OCTET STRING의 내용은 식별된 문자 transfer-syntax 를 사용하는 Unrestricted-Character-String 유형[X.680의 44.3 a) 참조]의 
		추상 문자열 값의 인코딩이어야 하며 다른 모든 필드의 값은 추상 값에 나타나는 값과 동일해야 합니다.
*/

/*
AUTOMATIC TAGS
SEQUENCE {
	identification				CHOICE {						[CTX 0] EXPLICIT
		syntaxes					SEQUENCE {						[CTX 0] IMPLICIT
			abstract					OBJECT IDENTIFIER,				[CTX 0] IMPLICIT
			transfer					OBJECT IDENTIFIER				[CTX 1] IMPLICIT
		},
		syntax						OBJECT IDENTIFIER,				[CTX 1] IMPLICIT
		presentation-context-id		INTEGER,						[CTX 2] IMPLICIT
		context-negotiation			SEQUENCE {						[CTX 3] IMPLICIT
			presentation-context-id		INTEGER,						[CTX 0] IMPLICIT
			transfer-syntax				OBJECT IDENTIFIER				[CTX 1] IMPLICIT
		},
		transfer-syntax				OBJECT IDENTIFIER,				[CTX 4] IMPLICIT
		fixed						NULL							[CTX 5] IMPLICIT
	},
	data-value-descriptor		ObjectDescriptor  OPTIONAL,		[CTX 1] IMPLICIT
	string-value				OCTET STRING					[CTX 2] IMPLICIT
}
(WITH COMPONENTS {
	... ,
	data-value-descriptor  ABSENT
})
*/

/*
syntaxes					SEQUENCE
{
	abstract					OBJECT IDENTIFIER,
	transfer					OBJECT IDENTIFIER 
},
*/

/*
context-negotiation			SEQUENCE
{
	presentation-context-id		INTEGER,
	transfer-syntax				OBJECT IDENTIFIER
},
*/

/*
identification				CHOICE
{
	syntaxes					SEQUENCE	{ ... },
	syntax						OBJECT IDENTIFIER,
	presentation-context-id		INTEGER,
	context-negotiation			SEQUENCE	{ ... },
	transfer-syntax				OBJECT IDENTIFIER,
	fixed						NULL
},
*/

int _avoid_warnint_no_symbol_char_str_ = 0;