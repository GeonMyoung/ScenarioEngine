#include "dz1_asn1_codec_ber.h"

/*
### X.680
36		Notation for the embedded-pdv type
36.5	The associated type for value definition and subtyping, assuming an automatic tagging environment, is (with normative comments):
		자동 태깅 환경을 가정할 때 값 정의 및 하위 유형 지정에 대한 관련 유형은 다음과 같습니다(표준 주석 포함).
	SEQUENCE
	{
		identification				CHOICE						-> {Tag:0}{L}{Data of CHOICE}
		{
			syntaxes					SEQUENCE					-> {Tag:0}{L}{Data of SEQUENCE} or	-- Abstract and transfer syntax object identifiers
			{
				abstract					OBJECT IDENTIFIER,			-> {Tag:0}{L}{Data of OID}
				transfer					OBJECT IDENTIFIER			-> {Tag:1}{L}{Data of OID}
			},
			syntax						OBJECT IDENTIFIER,			-> {Tag:1}{L}{Data of OID}		or	-- A single object identifier for identification of the abstract and transfer syntaxes
			presentation-context-id		INTEGER,					-> {Tag:2}{L}{Data of INTEGER}	or	-- (Applicable only to OSI environments) The negotiated OSI presentation context identifies the abstract and transfer syntaxes
			context-negotiation			SEQUENCE					-> {Tag:3}{L}PData of SEQUENCE}	or
			{																							-- (Applicable only to OSI environments)				
				presentation-context-id		INTEGER,					-> {Tag:0}{L}{Data of INTEGER}	-- Context-negotiation in progress, presentation-context-id identifies only the abstract syntax
				transfer-syntax				OBJECT IDENTIFIER			-> {Tag:1}{L}{Data if OID}		-- so the transfer syntax shall be specified
			},
			transfer-syntax				OBJECT IDENTIFIER,			-> {Tag:4}{L}{Data of OID}		or	-- The type of the value (for example, specification that it is the value of an ASN.1 type) is fixed 
																										-- by the application designer (and hence known to both sender and receiver)
																										-- This case is provided primarily to support selective-field-encryption 
																										-- (or other encoding transformations) of an ASN.1 type
			fixed						NULL						-> {Tag:5}{L}{Data of NULL}			-- The data value is the value of a fixed ASN.1 type (and hence known to both sender and receiver)
		},
		data-value-descriptor		ObjectDescriptor  OPTIONAL,	-> [{Tag:1}{L}{Data of ObjDescr}]		-- This provides human-readable identification of the class of the value 
		data-value					OCTET STRING				-> {Tag:2}{L}{Data of OCTET STRING}
	}
	(WITH COMPONENTS
		{
		... ,
		data-value-descriptor  ABSENT
		}
	)
		NOTE -	The embedded-pdv type does not allow the inclusion of a data-value-descriptor value. 
				Embedded-pdv 유형은 데이터 값 설명자 값의 포함을 허용하지 않습니다.

				However, the definition of the associated type provided here underlies the commonalities which exist between the embedded-pdv type, 
				the external type and the unrestricted character string type.
				그러나 여기에 제공된 관련 유형의 정의는 Embedded-PDV 유형, EXTERNAL 유형 및 Unrestricted Character String 유형 사이에 존재하는 공통점의 기초가 됩니다.


### X.690
8.18		Encoding of a value of the external type

8.18.1		The encoding of a value of the external type shall be the BER encoding of the following sequence type, assumed to be defined in an environment of 
			EXPLICIT TAGS, with a value as specified in the subclauses below:
			external type 값의 인코딩은 EXPLICIT TAGS 환경에서 정의된다고 가정하고 아래 하위 절에 지정된 값을 갖는 다음 시퀀스 유형의 BER 인코딩이어야 합니다.

			[UNIVERSAL 8] IMPLICIT SEQUENCE								-> {Tag:U8}{Length}{Contents Data of SEQUENCE}
			{
				direct-reference		OBJECT IDENTIFIER OPTIONAL,		-> [{Tag:OID}{L}{Data}]
				indirect-reference		INTEGER OPTIONAL,				-> [{Tag:INT}{L}{Data}]
				data-value-descriptor	ObjectDescriptor OPTIONAL,		-> [{Tag:ObjDescr}{L}{Data}]
				encoding				CHOICE 
				{
					single-ASN1-type		[0] ABSTRACT-SYNTAX.&Type,	-> {Tag:0}{L}{Complete BER Stream of Type}  or
					octet-aligned			[1] IMPLICIT OCTET STRING,	-> {Tag:1}{L}{Data of OCTET STRING}			or
					arbitrary				[2] IMPLICIT BIT STRING		-> {Tag:2}{L}{Data of BIT STRING}
				}
			}
			NOTE -	This sequence type differs from that in X.680 for historical reasons.
					이 시퀀스 유형은 역사적 이유로 X.680과 다릅니다.

8.18.2		The value of the fields depends on the abstract value being transmitted, which is a value of the type specified in 36.5 of X.680
			필드 값은 X.680의 36.5에 지정된 유형 값에 따라 (변환되어) 전송되는 추상 값에 따라 다릅니다.

8.18.3		The data-value-descriptor above shall be present if and only if the data value descriptor is present in the abstract value, and shall have the same value.
			위의 data-value-descriptor 는 data-value-descriptor 가 추상 값에 있는 경우에만 존재해야 하며 동일한 값을 가져야 합니다.

8.18.4		Values of direct-reference and indirect-reference above shall be present or absent in accordance with Table 2. 
			위의 DirectReference 및 IndirectReference의 값은 표 2에 따라 존재하거나 존재하지 않습니다.

			Table 2 maps the external type alternatives of identification defined in X.680, 36.5, to the external type components direct-reference and indirect-reference defined in 8.18.1.
			표 2는 X.680, 36.5에 정의된 identification 의 External Type 대안을 8.18.1에 정의된 External Type 구성 요소 direct-reference 및 indirect-reference 에 매핑합니다.

			identification				direct-reference			indirect-reference
			syntaxes					---------------------------------------------------
			syntax						syntax						-
			presentation-context-id		-							presentation-context-id
			context-negotiation			transfer-syntax				presentation-context-id
			transfer-syntax				---------------------------------------------------
			fixed						---------------------------------------------------

8.18.5		The data value shall be encoded according to the transfer syntax identified by the encoding, and shall be placed in an alternative of the encoding choice as specified below.
			데이터 값은 encoding에 의해 식별된 전송 구문에 따라 인코딩 되어야 하며 아래에 지정된 인코딩 선택의 대안으로 배치되어야 합니다.

8.18.6		If the data value is the value of a single ASN.1 data type, and if the encoding rules for this data value are one of those specified in this Recommendation,
			then the sending implementation shall use any of the encoding choices:
			데이터 값이 단일 ASN.1 데이터 유형의 값이고 이 데이터 값에 대한 인코딩 규칙이 이 권고에 지정된 규칙 중 하나인 경우 전송 구현은 아래 중 하나를 사용해야 합니다.
			-	single-ASN1-type;
			-	octet-aligned;
			-	arbitrary.
			as an implementation option.

8.18.7		If the encoding of the data value, using the agreed or negotiated encoding, is an integral number of octets, 
			then the sending implementation shall use any of the encoding choices:
			합의되거나 협상된 인코딩을 사용하는 데이터 값의 인코딩이 정수 길이 옥텟인 경우 전송 구현은 아래 중 하나를 사용해야 합니다.
			-	octet-aligned;
			-	arbitrary.
			as an implementation option.

			NOTE -	A data value which is a series of ASN.1 types, and 
					for which the transfer syntax specifies simple concatenation of the octet strings 
					produced by applying the ASN.1 Basic Encoding Rules to each ASN.1 type, 
					falls into this category, not that of 8.18.6.
					데이터 값이 일련의 ASN.1 유형이고 전송 구문이 각 ASN.1 유형에 ASN.1 BER을 적용하여 
					생성된 옥텟 문자열의 단순 연결을 지정하는 경우 8.18.6이 아니라 이 범주에 속합니다.

8.18.8		If the encoding of the data value, using the agreed or negotiated encoding, is not an integral number of octets, the encoding choice shall be:
			합의되거나 협상된 인코딩을 사용하는 데이터 값의 인코딩이 정수 옥텟 수가 아닌 경우 인코딩 선택은 다음과 같아야 합니다.
			-	arbitrary.

8.18.9		If the encoding choice is chosen as single-ASN1-type, then the ASN.1 type shall replace the open type, with a value equal to the data value to be encoded.
			encoding 이 single-ASN1-type 으로 선택되면 ASN.1 유형은 인코딩될 데이터 값과 동일한 값을 저장한 Open Type 으로 대체해야 합니다.

			NOTE -	The range of values which might occur in the open type is determined by the registration of the object identifier value associated with the direct-reference, and/or the integer value associated with the indirect reference.
					Open Type 에서 발생할 수 있는 값의 범위는 direct-reference 와 관련된 OID 값 및/또는 indirect-reference 와 관련된 정수 값의 등록에 의해 결정됩니다.

8.18.10		If the encoding choice is chosen as octet-aligned, then the data value shall be encoded according to the agreed or negotiated transfer syntax, 
			and the resulting octets shall form the value of the octet-string.
			encoding 이 octet-aligned 로 선택되면 데이터 값은 합의되거나 협상된 전송 구문에 따라 인코딩 되어야 하며 결과 옥텟은 OCTET STRING 값을 형성해야 합니다.

8.18.11		If the encoding choice is chosen as arbitrary, then the data value shall be encoded according to the agreed or negotiated transfer syntax, and the result shall form the value of the bitstring.
			encoding 이 arbitrary 로 선택되면 데이터 값은 합의되거나 협상된 전송 구문에 따라 인코딩 되어야 하며 결과는 BIT STRING 값을 형성해야 합니다.
*/

/*
ExternalModule DEFINITIONS EXPLICIT TAGS ::= BEGIN
[UNIVERSAL 8] IMPLICIT SEQUENCE
{
	direct-reference		OBJECT IDENTIFIER	OPTIONAL,				[void] EXPLICIT
	indirect-reference		INTEGER				OPTIONAL,				[void] EXPLICIT
	data-value-descriptor	ObjectDescriptor	OPTIONAL,				[void] EXPLICIT
	encoding				CHOICE										[void] IMPLICIT
	{
		single-ASN1-type		[0]				ABSTRACT-SYNTAX.&Type,		[CTX 0] EXPLICIT
		octet-aligned			[1] IMPLICIT	OCTET STRING,				[CTX 1]	IMPLICIT
		arbitrary				[2] IMPLICIT	BIT STRING					[CTX 2] IMPLICIT
	}
}
END
*/

int __avoid_no_symbol_warning_external_ = 0;