#include "dz1_asn1_codec_ber.h"

/*
### X.680
36		Notation for the embedded-pdv type
36.5	The associated type for value definition and subtyping, assuming an automatic tagging environment, is (with normative comments):
		자동 태깅 환경을 가정할 때 값 정의 및 하위 유형 지정에 대한 관련 유형은 다음과 같습니다(표준 주석 포함).
	SEQUENCE
	{
		identification				CHOICE
		{
			syntaxes					SEQUENCE				-- Abstract and transfer syntax object identifiers
			{
				abstract					OBJECT IDENTIFIER,
				transfer					OBJECT IDENTIFIER 
			},
			syntax						OBJECT IDENTIFIER,		-- A single object identifier for identification of the abstract and transfer syntaxes
			presentation-context-id		INTEGER,				-- (Applicable only to OSI environments) The negotiated OSI presentation context identifies the abstract and transfer syntaxes
			context-negotiation			SEQUENCE
			{													-- (Applicable only to OSI environments)				
				presentation-context-id		INTEGER,			-- Context-negotiation in progress, presentation-context-id identifies only the abstract syntax
				transfer-syntax				OBJECT IDENTIFIER	-- so the transfer syntax shall be specified
			},
			transfer-syntax				OBJECT IDENTIFIER,		-- The type of the value (for example, specification that it is the value of an ASN.1 type) is fixed 
																-- by the application designer (and hence known to both sender and receiver)
																-- This case is provided primarily to support selective-field-encryption 
																-- (or other encoding transformations) of an ASN.1 type
			fixed						NULL					-- The data value is the value of a fixed ASN.1 type (and hence known to both sender and receiver)
		},
		data-value-descriptor		ObjectDescriptor  OPTIONAL,	-- This provides human-readable identification of the class of the value 
		data-value					OCTET STRING
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
8.17	Encoding of a value of the embedded-PDV type
8.17.1	The encoding of a value of the embedded-PDV type shall be the BER encoding of the type as defined in 36.5 of Rec. ITU-T X.680 | ISO/IEC 8824-1.
		Embedded-PDV 유형 값의 인코딩은 X.680의 36.5에 정의된 유형의 BER 인코딩이어야 합니다.

8.17.2	The contents of the data-value OCTET STRING shall be the encoding of the abstract data value of the embedded-pdv type [see 36.3 a) in Rec. ITU-T X.680 | ISO/IEC 8824-1]
		using the identified transfer syntax, and the value of all other fields shall be the same as the values appearing in the abstract value.
		data-value OCTET STRING의 내용은 식별된 transfer syntax 를 사용하여 Embedded-PDV 유형[X.680의 36.3 a) 참조]의 추상 데이터 값의 인코딩이어야 하며,
		다른 모든 필드의 값은 추상 값에 나타나는 값과 같아야 합니다. 
*/

/*
EmbeddedPdvModule DEFINITIONS AUTOMATIC TAGS ::= BEGIN
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
	data-value					OCTET STRING					[CTX 2] IMPLICIT
}
(WITH COMPONENTS
	{
	... ,
	data-value-descriptor  ABSENT
	}
)
END
*/

int _avoid_warning_no_symbol_emb_pdv_ = 0;