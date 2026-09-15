#include "dz1_asn1_codec_ber.h"

/*
### X.681
A.1		This annex specifies a useful information object class, with class reference TYPE-IDENTIFIER. 
		이 부록은 참조 클래스 “TYPE-IDENTIFIER”라는 유용한 정보 객체 클래스를 지정합니다.

		NOTE -	This information object class is the simplest useful class, having just two fields, an identifier field of type OBJECT IDENTIFIER, 
				and a type field which defines the ASN.1 type for carrying all information concerning any particular object in the class. 
				이 정보 객체 클래스는 2개의 필드, OBJECT IDENTIFIER 유형의 식별자 필드 및 클래스의 특정 객체에 관한 모든 정보를 전달하기 위한 
				ASN.1 유형을 정의하는 유형 필드가 있는 가장 간단한 유용한 클래스입니다.

				It is defined in this Recommendation | International Standard because of the widespread use of information objects of this form.
				이 형식의 정보 객체가 널리 사용되기 때문에 이 표준에서 정의됩니다.

A.2		The TYPE-IDENTIFIER information object class is defined as:

		TYPE-IDENTIFIER ::= CLASS
		{
			&id		OBJECT IDENTIFIER	UNIQUE,
			&Type
		}
		WITH SYNTAX {&Type IDENTIFIED BY &id}

A.3		This class is defined as a "useful" information object class, and is available in any module without the necessity for importing it.
		이 클래스는 "유용한" 정보 개체 클래스로 정의되며 IMPORT할 필요 없이 모든 모듈에서 사용할 수 있습니다.

C.7	The associated sequence type shall be:
	SEQUENCE {
		type-id					<DefinedObjectClass>.&id,
		value			[0] 	<DefinedObjectClass>.&Type
	}
	where "<DefinedObjectClass>" is replaced by the particular "DefinedObjectClass" used in the "InstanceOfType" notation.

### X.690
8.16	Encoding of an instance-of value

8.16.1	The encoding of the instance-of type shall be the BER encoding of the following sequence type with the value as specified in 8.16.2:
		instance-of 유형의 인코딩은 8.16.2에 명시된 값을 갖는 SEQUENCE 유형의 BER 인코딩이어야 합니다.

		[UNIVERSAL 8] IMPLICIT SEQUENCE 
		{
			type-id	<DefinedObjectClass>.&id,
			value	[0] EXPLICIT <DefinedObjectClass>.&Type
		}

		where "<DefinedObjectClass>" is replaced by the particular "DefinedObjectClass" used in the "InstanceOfType" notation.
		여기서 "<DefinedObjectClass>"는 "InstanceOfType" 표기법에 사용된 특정 "DefinedObjectClass"로 대체됩니다.

		NOTE -	When the value is a value of a single ASN.1 type and BER encoding is used for it, 
				the encoding of this type is identical to an encoding of a corresponding value of the external type, 
				where the syntax alternative is in use for representing the abstract value.
				value 가 단일 ASN.1 유형의 값이고 이에 대해 BER 인코딩이 사용되는 경우 
				이 유형의 인코딩은 external type 의 해당 값 인코딩과 동일합니다. 
				여기서 syntax 대안은 abstract value 를 나타내는 데 사용됩니다.

8.16.2	The value of the components of the sequence type in 8.16.1 shall be the same as the values of the corresponding components of 
		the associated type in Rec. ITU-T X.681 | ISO/IEC 8824 2, C.7.
		8.16.1에 있는 시퀀스 유형의 구성 요소 값은 X.681, C.7에 있는 관련 유형의 해당 구성 요소 값과 동일해야 합니다.

*/

/*
InstanceOfModule DEFINITIONS EXPLICIT TAGS ::= BEGIN
TYPE-IDENTIFIER ::= CLASS
{
	&id		OBJECT IDENTIFIER	UNIQUE,
	&Type
}
WITH SYNTAX { &Type IDENTIFIED BY &id }

[UNIVERSAL 8] IMPLICIT SEQUENCE {
	type-id								<DefinedObjectClass>.&id,
	value			[0] 	EXPLICIT	<DefinedObjectClass>.&Type
}

-- Identical with above ===========================================

[UNIVERSAL 8] IMPLICIT SEQUENCE {
	type-id								OBJECT IDENTIFIER		[void]	EXPLICIT
	value			[0] 	EXPLICIT	OpenType				[CTX 0]	EXPLICIT
}
END
*/

int _avoid_warning_no_symbol_instance_of_ = 0;