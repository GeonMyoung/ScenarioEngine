#include "dz1_asn1_codec_ber.h"

/*
### X.680
25		Notation for sequence types

25.2	For the purposes of the following clauses, a "PrefixedType" is defined to be a textually tagged type if either:
		다음에 열거한 경우에 "PrefixedType"은 텍스트로 태그가 지정된 유형으로 정의됩니다.

		a)	the "PrefixedType" is a "TaggedType"; or
			PrefixedType이 TaggedType인 경우

		b)	the "Type" in the "PrefixedType" is a textually tagged type.
			PrefixedType속의 Type 에 택스트로 태그가 지정된 경우

25.3	When the "ComponentTypeLists" production occurs within the definition of a module for which automatic tagging is selected (see 13.3), 
		and none of the occurrences of "NamedType" in any of the first three alternatives for "ComponentType" is a textually tagged type (see 25.2), 
		then the automatic tagging transformation is selected for the entire "ComponentTypeLists", otherwise it is not.
		AUTOMATIC TAGS가 선택된 모듈(13.3 참조)의 정의 내에서 “ComponentTypeLists” 생성이 발생하고 “ComponentType”에 대한 처음 세 가지 대안에서 
		NamedType이 텍스트로 태깅된 유형(25.2 참조)이 아닌 경우 전체 "ComponentTypeLists"에 대해 AUTOMATIC TAGS 변환이 선택되고 그렇지 않으면 선택되지 않습니다. 

		-> AUTOMATIC TAGS가 적용된 모듈 내에서, 단일 ComponentTypeLists에서 나타나는 모든 CompomentType이 처음 세가지 방법중 하나로 기술될 때 
		나타나는 NamedType에 텍스트로 지정한 테그가 없는 경우 AUTOMATIC TAGS가 적용 됩니다.

25.4	The decision to apply the automatic tagging transformation is taken individually for each occurrence of "ComponentTypeLists" and prior to the COMPONENTS OF
		transformation specified by 25.5.
		자동 태깅 변환을 적용하기로 한 결정은 "ComponentTypeLists"가 발생할 때마다 그리고 25.5에 명시된 COMPONENTS OF 변환 이전에 개별적으로 취해집니다.

		ComponentTypeLists ::=
		  (1st)	RootCompTypeList
		| (2nd)	RootCompTypeList "," "..." [ExceptionSpec] ExtensionAdditions [ "," "..." ]
		| (3rd)	RootCompTypeList "," "..." [ExceptionSpec] ExtensionAdditions   "," "..."   "," RootCompTypeList

		| (4th)						 "..." [ExceptionSpec] ExtensionAdditions   "," "..."   "," RootCompTypeList
		| (5th)						 "..." [ExceptionSpec] ExtensionAdditions [ "," "..." ]

		However, as specified in 25.8 to 25.10, the automatic tagging transformation (if applied) is applied after the COMPONENTS OF transformation.
		그러나 25.8 ~ 25.10(25.8:자동 변환 결정 및 적용시점, 25.9:자동변환 결정 방법, 25.10:자동변환 알고리즘)에 명시된 바와 같이 자동 태깅 변환(적용되는 경우)은 
		COMPONENTS OF 변환 이후에 적용됩니다.

		NOTE -	The effect of this is that the application of automatic tags is suppressed by tags textually present in the "ComponentTypeLists", 
				but not by tags present in the "Type" following COMPONENTS OF.
				이것의 효과는 "ComponentTypeLists"에 텍스트로 존재하는 태그에 의해 자동 태그의 적용이 억제되지만 COMPONENTS OF 다음에 오는 
				"Type"에 존재하는 태그에 의해 억제되지 않는다는 것입니다.

25.5	"Type" in the "COMPONENTS OF Type" notation shall be a sequence type.  
		"COMPONENTS OF Type" 표기법에서 "Type"은 시퀀스 유형이어야 합니다.

		The "COMPONENTS OF Type" notation shall be used to define the inclusion, at this point in the list of components, 
		of all the component types (of which there shall be at least one) of the referenced type, except for any extension marker 
		and extension additions that may be present in the "Type". (Only the "RootComponentTypeList" of the "Type" in the "COMPONENTS OF Type" is included; 
		extension markers and extension additions, if any, are ignored by the "COMPONENTS OF Type" notation.)  
		"COMPONENTS OF Type" 표기법은 참조된 "Type"(이 시점에서 구성 요소 목록)에 Extension Marker 및 Extension Addition 을 제외하고 존재할 수 있는 
		유형의 모든 구성요소 유형(하나라도 있어야 함)의 포함을 정의하는 데 사용됩니다. "COMPONENTS OF Type"에 있는 "Type"의 "RootComponentTypeList"만 포함됩니다. 
		확장 마커 이후 구성요소 및 확장 추가에 있는 구성요소(있는 경우)는 "COMPONENTS OF Type" 표기법에 의해 무시됩니다.

		-> COMPONENTS OF 구문 뒤에 있는 Type은 반드시 SEQUENCE 유형이어야 하며, Type에 해당하는 유형의 RootComponentsTypeList에 있는 
		모든 요소가 새롭게 정의하는 유형(SEQUENCE)에 삽입되게 합니다.

		Any subtype constraint applied to the referenced type is ignored by this transformation.
		참조된 유형에 적용된 모든 Subtype Constraint 는 이 변환에서 무시됩니다.

		NOTE -	This transformation is logically completed prior to the satisfaction of the requirements in the following subclauses.
				이 변환은 다음 하위 절의 요구 사항이 충족되기 전에 논리적으로 완료됩니다.

25.6	The following subclauses each identify a series of occurrences of "ComponentType" in either the root or the extension additions or both.
		The rule of 25.6.1 shall apply to all such series.
		다음 하위 절은 각각 root 또는 extension addition,  또는 둘 다에서 "ComponentType"의 일련의 발생을 식별합니다. 
		25.6.1의 규칙은 그러한 모든 시리즈에 적용됩니다.

25.6.1	Where there are one or more consecutive occurrences of "ComponentType" that are all marked OPTIONAL or DEFAULT, 
		the tags of those "ComponentType"s and of any immediately following component type in the series shall be distinct (see 31.2).
		모든 OPTIONAL 또는 DEFAULT로 표시된 "ComponentTyp	e"이 하나 이상 연속적으로 나타나는 경우 해당 "ComponentType"의 태그와 시리즈에서 
		바로 뒤따르는 구성요소 유형의 태그는 구별되어야 합니다(31.2 참조).

		-> OPTIONAL및 DEFAULT로 표시되어 생략 가능한 유형은 순서적으로 다음에 오는 유형과 구별할 수 있도록 TAG값이 각각 달라야 합니다.
  
		If automatic tagging was selected, the requirement that tags be distinct applies only after automatic tagging has been performed, and will always be satisfied.
		자동 태그 지정을 선택한 경우 태그 구별 요구 사항은 자동 태그 지정이 수행된 후에만 적용되며 항상 충족됩니다.

25.6.2	Subclause 25.6.1 shall apply to the series of "ComponentType"s in the root.
		25.6.1은 root "ComponentType" 시리즈(RootComponentTypeList )에 적용됩니다.
		-> 25.6.1은 RootComponentTypeList에 우선 적용해야 합니다.

25.6.3	Subclause 25.6.1 shall apply to the complete series of "ComponentType"s in the root or in the extension additions, 
		in the textual order of their occurrence in the type definition (ignoring all version brackets and ellipsis notation).(See also 52.7.)
		25.6.1은 유형 정의(모든 VersionBrackets 및 EllipsisNotation 무시)에서 root 또는 
		extension additions 에 있는 "ComponentType"의 전체 시리즈에 텍스트 순서에 따라 적용됩니다.(52.7 참조)

25.7	When the third or fourth alternative of "ComponentTypeLists" is used, all "ComponentType"s in extension additions shall have tags which are distinct 
		from the tags of the textually following "ComponentType"s  up to and including the first such "ComponentType" that is not marked OPTIONAL or DEFAULT 
		in the trailing "RootComponentTypeList", if any.  (See also 52.7.)
		ComponentTypeLists의 세 번째 또는 네 번째 대안이 사용되는 경우(후행 RootComponentTypeList가 있는 경우), ExtensionAdditions의 모든 ComponentType에는 
		기술 순서상 뒤따르는 ComponentType의 태그와 구별되는 태그가 있어야 합니다. 후행 RootComponentTypeList에서 OPTIONAL 또는 DEFAULT로 표시되지 않은 
		첫 번째 ComponentType(이 있는 경우 해당 ComponentType)까지 포함합니다.

25.8	The automatic tagging transformation of an occurrence of "ComponentTypeLists" is logically performed after the transformation specified by 25.5, 
		but only if 25.3 determines that it shall apply to that occurrence of "ComponentTypeLists". 
		"ComponentTypeLists"의 AUTOMATIC TAGS 변환은 25.5(COMPONENT OF 변환)에 의해 지정된 변환 후에 논리적으로 수행되지만, 
		25.3(전제항목 AUTOMATIC TAGS 변환)이 "ComponentTypeLists"에 적용해야 한다고 결정한 경우에만 수행됩니다.

		-> AUTOMATIC TAGS 변환을 할지 말지는 25.3에 기술한 조건에 부합할 때 적용하기로 결정 하지만, 25.5에 기술한 COMPONENTS OF 변환이 이루어진 후에 적용합니다.

		Automatic tagging transformation impacts each "ComponentType" of the "ComponentTypeLists" by replacing the "Type" originally 
		in the "NamedType" production with a replacement "TaggedType" occurrence specified in 25.10.
		AUTOMATIC TAGS 변환은 "NamedType"에 원래 있던 "Type"을 25.10에 지정된 대체용 "TaggedType"으로 대체하여 "ComponentTypeLists"의 각 "ComponentType"에 영향을 줍니다.

25.9	If automatic tagging is in effect and the "ComponentType"s in the extension root have no tags, then no "ComponentType" within the "ExtensionAdditionList" 
		shall be a textually tagged type.
		AUTOMATIC TAGS가 유효하고 RootComponentTypeList의 ComponentType에 태그가 없는 경우 ExtensionAdditionList 내의 ComponentType은 텍스트 태그 유형이 될 수 없습니다.

		-> AUTOMATIC TAGS변환이 적용 되도록 하려면 RootComponentsList와 ExtensionAdditionList모두 덱스트 태그로 지정된 것이 없어야 합니다.

25.10	If automatic tagging is in effect, the replacement "TaggedType" is specified as follows:
		AUTOMETIC TAGS가 유효한 경우 대체 "TaggedType"이 다음과 같이 지정됩니다.

		a)	the replacement "TaggedType" notation uses the "Tag Type" alternative;
			"TaggedType" 표기법은 "Tag Type" 대안으로 대체 합니다.

		b)	the "Class" of the replacement "TaggedType" is empty (i.e., tagging is context-specific);
			"TaggedType"의 "Class"를 비웁니다(즉, 태깅이 CONTEXT-SPECIFIC가 됩니다).

		c)	the "ClassNumber" in the replacement "TaggedType" is tag value zero for the first "ComponentType" in the "RootComponentTypeList", 
			one for the second, and so on, proceeding with increasing tag numbers;
			"TaggedType"의 "ClassNumber"는 "RootComponentTypeList"의 첫 번째 "ComponentType"에 대한 태그 값을 0으로, 
			두 번째에 대한 태그 값을 1로 대체 되는 식으로 태그 번호가 증가합니다.

		d)	the "ClassNumber" in the replacement "TaggedType" of the first "ComponentType" in the "ExtensionAdditionList" is zero if the "RootComponentTypeList" is missing, 
			else it is one greater than the largest "ClassNumber" in the "RootComponentTypeList", with the next "ComponentType" in the "ExtensionAdditionList" 
			having a "ClassNumber" one greater than the first, and so on, proceeding with increasing tag numbers;
			ExtensionAdditionList에 첫 번째 ComponentType에 설정한 TaggedType의 ClassNumber는 RootComponentTypeList에서 가장 큰 ClassNumber보다 하나 더 큽니다. 
			RootComponentTypeList가 없으면 0부터 시작합니다. "ExtensionAdditionList"의 다음 "ComponentType"들은 계속해서 태그 번호가 증가 합니다.

		e)	the "Type" in the replacement "TaggedType" is the original "Type" being replaced.
			대체된 "TaggedType"의 "Type"은 대체되는 원래 "Type"입니다.

		NOTE 1 -	The rules governing specification of implicit tagging or explicit tagging for replacement "TaggedType"s are provided by 31.2.7.
					교체된 "TaggedType"에 대한 IMPLICIT 또는 EXPLICIT 태깅의 사양을 제어하는 규칙은 31.2.7에 의해 제공됩니다.

		Automatic tagging is always implicit tagging unless the "Type" is a choice type or an open type notation, or a "DummyReference"(see Rec. ITU-T X.683 | ISO/IEC 8824-4, 8.3), 
		in which case it is explicit tagging.
		자동 태깅은 "Type"이 태그가 지정되지 않은 Choice Type 또는 Open Type 또는 "DummyReference"(Rec. ITU-T X.683 | ISO/IEC 8824-4, 8.3 참조)인 경우 EXPLICIT 태깅, 
		그 이외에는 항상 IMPLICIT 태깅입니다.

		NOTE 2 -	Once 25.8 is satisfied, the tags of the components are completely determined, and are not modified even when the sequence type is referenced 
					in the definition of a component within another "ComponentTypeLists" for which automatic tagging transformation applies. 
					25.8(AUTOMATIC TAGS 변환 결정과 적용 시기)이 충족되면 구성 요소의 태그가 완전히 결정되며 자동 태깅 변환이 적용되는 다른 "ComponentTypeLists" 
					내의 구성 요소 정의에서 시퀀스 유형을 참조하더라도 수정되지 않습니다.

					Thus, in the following case:
						T ::= SEQUENCE { a   Ta,  b   Tb,  c   Tc }
						E ::= SEQUENCE { f1  E1,  f2  T,   f3  E3 }
					automatic tagging applied to the components of E never affects the tags attached to components a, b and c of T, whatever the tagging environment of T.
					E의 구성요소에 적용된 AUTOMATIC TAGS는 T의 태깅 환경에 관계없이 T의 구성요소 a, b, c에 부착된 태그에 영향을 미치지 않습니다.

					If T is defined in an automatic tagging environment and E is not in an automatic tagging environment, automatic tagging is still applied to components a, b and c of T.
					T가 AUTOMATIC TAGS 환경에서 정의되고 E가 AUTOMATIC TAGS 환경에서 정의되지 않은 경우에도 AUTOMATIC TAGS는 여전히 T의 구성요소 a, b 및 c에 적용됩니다.

		NOTE 3 -	When a sequence type appears as the "Type" in "COMPONENTS OF Type", each occurrence of "ComponentType" in it is duplicated by 
					the application of 25.5 prior to the possible application of automatic tagging to the referencing sequence type. 
					SEQUENCE 유형이 "COMPONENTS OF Type"에서 "Type"으로 나타날 때 참조하는 SEQUENCE 유형에 AUTOMATIC TAGS를 적용할 수 있기 전에 
					25.5(COMPONENT OF 변환)를 적용하여 "ComponentType"이 나타날 때마다 복제됩니다.

					Thus, in the following case:
						T ::= SEQUENCE { a  Ta,  b  SEQUENCE { b1  T1,  b2  T2,  b3  T3},  c Tc }
						W ::= SEQUENCE { x  Wx,  COMPONENTS OF  T, y  Wy }
					the tags of a, b, and c within T need not be the same as the tags of a, b, and c within W if W has been defined in an automatic tagging environment, 
					but the tags of b1, b2 and b3 are the same in both T and W. 
					W가 AUTOMATIC TAGS 환경에서 정의된 경우 T 내의 a, b 및 c 태그가 W 내의 a, b 및 c 태그와 동일할 필요는 없지만 b1, b2와 b3은 T와 W 모두에서 동일합니다.

					In other words, the automatic tagging transformation is only applied once to a given "ComponentTypeLists".
					즉, AUTOMATIC TAGS 변환은 지정된 "ComponentTypeLists"에 한 번만 적용됩니다.

		NOTE 4 -	Subtyping has no impact on automatic tagging.
					Subtyping은 자동 태그 지정에 영향을 주지 않습니다.

		NOTE 5 -	When automatic tagging is in place, insertion of new components at any location other than the extension insertion point (see 3.8.35) may result 
					in changes to other components due to the side effect of modifying the tags thus causing inter-working problems with an older version of the specification.
					자동 태깅이 있는 경우 확장 삽입 지점(3.8.35 참조)이 아닌 다른 위치에 새 구성 요소를 삽입하면 태그 수정의 부작용으로 인해 다른 구성 요소가 변경되어 
					이전 버전과의 연동 문제가 발생할 수 있습니다.

25.11	If OPTIONAL or DEFAULT are present, the corresponding value may be omitted from a value of the new type.
		OPTIONAL 또는 DEFAULT가 있는 경우 해당 값은 새 유형의 값에서 생략될 수 있습니다.

25.12	If DEFAULT occurs, the omission of a value for that type shall be exactly equivalent to the insertion of the value defined by "Value", 
		which shall be a value notation for a value of the type defined by "Type" in the "NamedType" production sequence.
		DEFAULT가 발생하면 해당 유형에 대한 값의 생략은 "Value"에 의해 정의된 값의 삽입과 정확히 동일해야 하며, 이는 "NamedType"에서 "Type"에 
		의해 정의된 유형의 값에 대한 값 표기법이어야 합니다.

25.13	The value corresponding to an "ExtensionAdditionGroup" (all components together) is optional.  
		"ExtensionAdditionGroup"(의 모든 구성 요소)에 해당하는 값은 "OPTIONAL"입니다.

		-> "ExtensionAdditionGroup"은 하나의 묶음로 치부되며, 해당 묶음의 값은 OPTIONAL 입니다.

		However, if such a value is present, then the value corresponding to the components within the bracketed "ComponentTypeList" 
		that are not marked OPTIONAL or DEFAULT shall be present.
		그럼에도 불구하고 "ExtenseionAdditionGroup"이 값을 가지는 경우는 대괄호로 묶인 "ComponentTypeList" 내에 
		OPTIONAL 또는 DEFAULT로 표시되지 않은 구성 요소(Mandatory 구성 요소)에 값이 (모두) 있어야 합니다.

25.14	The "identifier"s in all "NamedType" production sequences of the "ComponentTypeLists" (together with those obtained by expansion of COMPONENTS OF) shall all be distinct.
		"ComponentTypeLists"에 등장하는 "NamedType"의 모든 "identifier"(COMPONENTS OF의 확장으로 얻은 것 포함)는 모두 고유해야 합니다.
		-> 변수명이 중복되면 안됩니다.

25.15	A value for a given extension addition type shall not be specified unless there are values specified for all extension addition types 
		not marked OPTIONAL or DEFAULT that lie logically between the extension addition type and the extension root.
		주어진 extension addition 유형에 대한 값은 extension addition 유형과 extension root 사이에 논리적으로 놓여 있는 OPTIONAL 또는 DEFAULT로 
		표시되지 않은 모든 extension addition 유형(모든 mandatory 요소)에 대해 지정된 값이 없으면 지정되지 않습니다.

		-> extension addition내의 요소들이 값을 가지려면 extension addition내의  모든 mandatory 항목에 값이 있어야 합니다.

		NOTE 1 -	Where the type has grown from the extension root (version 1) through version 2 to version 3 by the addition of extension additions, 
					the presence in an encoding of any addition from version 3 requires the presence of an encoding of all additions in version 2 
					that are not marked OPTIONAL or DEFAULT.
					extension root(버전 1) 유형이 Extension additions 를 추가하여 버전 2를 거쳐 버전 3으로 성장한 경우 버전 3의 추가 인코딩이 존재하려면 
					버전 2의 OPTIONAL 또는 DEFAULT로 표시되지 않은 모든 추가 인코딩이 있어야 합니다.

		NOTE 2 -	"ComponentType"s that are extension additions but not contained within an "ExtensionAdditionGroup" should always be encoded 
					if they are not marked OPTIONAL or DEFAULT, except when the abstract value is being relayed from a sender that is using 
					an earlier version of the abstract syntax in which the "ComponentType" is not defined.
					Extension additions 에 들어있지만 "ExtensionAdditionGroup"에 포함되지 않은 "ComponentType"은 OPTIONAL 또는 DEFAULT로 표시되지 
					않은 경우 항상 인코딩되어야 합니다. "ComponentType"이 정의되지 않은 이전 버전의 추상 구문을 사용하는 발신자로부터 AbstractValue가 
					릴레이되는 경우는 예외입니다.

		NOTE 3 -	Use of the "ExtensionAdditionGroup" production is recommended because:
					다음과 같은 이유로 "ExtensionAdditionGroup" 프로덕션을 사용하는 것이 좋습니다.
			a)	it can result in more compact encodings depending on the encoding rules (e.g., PER);
				인코딩 규칙에 따라 더 압축된 인코딩이 될 수 있습니다.

			b)	the syntax is more precise in that it clearly indicates that a value of a type defined in the "ExtensionAdditionList" 
				and not marked OPTIONAL or DEFAULT should always be present in an encoding if the extension addition group in which 
				it is defined is encoded (compare with Note 1);
				"ExtensionAdditionList"에 정의되고 OPTIONAL 또는 DEFAULT로 표시되지 않은 유형의 값이 정의된 확장 추가 그룹이 인코딩된 경우 
				인코딩에 항상 존재해야 함을 이 구문이 더 명확하게 나타냅니다(다음과 비교 Note 1)

			c)	the syntax makes it clear which types in an "ExtensionAdditionList" must as a group be supported by an application.
				"ExtensionAdditionList"의 어떤 유형이 애플리케이션에서 그룹으로 지원되어야 하는지를 이 구문이 더 분명히 합니다.

25.16	A "VersionNumber" shall be used only if all "ExtensionAdditions"s and "ExtensionAdditionAlternatives"  within the module are 
		"ExtensionAdditionGroup"s or "ExtensionAdditionAlternativesGroup"s with "VersionNumber"s.
		"VersionNumber"는 모듈 내의 모든 "ExtensionAdditions" 및 "ExtensionAdditionAlternatives"가 
		"ExtensionAdditionGroup"들 또는 "ExtensionAdditionAlternativesGroup"들에 있는 "VersionNumber"들 중 하나인 경우에만 사용됩니다.

		The "number" in each "VersionNumber" of an "ExtensionAdditionGroup" shall be greater than or equal to two, 
		and shall be greater than the "number" in any preceding "ExtensionAdditionGroup" within an insertion point.
		ExtensionAdditionGroup의 각 VersionNumber에 있는 "number"는 2보다 크거나 같아야 하며 
		삽입 지점 내에서 선행하는 "ExtensionAdditionGroup"의 "number"보다 커야 합니다.

		NOTE 1 -	The convention used here is that the specification with no extension addition groups is version 1,
					thus the first added extension addition group will have a number greater than or equal to 2.
					여기에 사용된 규칙은 Extension Addition Groups 가 없는 사양이 버전 1이므로 
					첫 번째로 추가된 Extension Addition Group 의 숫자는 2 이상이라는 것입니다.

					Where a single "ExtensionAddition" is needed for an "ExtensionAdditions", an "ExtensionAdditionGroup" can be used with a single "ExtensionAddition".
					"ExtensionAdditions"에 단일 "ExtensionAddition"이 필요한 경우 단일 "ExtensionAddition"과 함께 "ExtensionAdditionGroup"을 사용할 수 있습니다.

		NOTE 2 -	The restrictions on use of "VersionNumber" apply only within a single module and impose no constraints on imported types.
					"VersionNumber" 사용에 대한 제한 사항은 단일 모듈 내에서만 적용되며 가져온 유형에 대한 제한 사항이 없습니다.

25.17	All sequence types have a tag which is universal class, number 16.
		모든 시퀀스 유형에는 UNIVERSAL 클래스 번호 16인 태그가 있습니다.

		NOTE -	Sequence-of types have the same tag as sequence types (see 26.2).
				SEQUENCE-OF 유형은 시퀀스 유형과 동일한 태그를 갖습니다(26.2 참조).

				
31		Notation for prefixed types
31.2	The tagged type

52		The extension marker
52.7	Where this Recommendation | International Standard requires distinct tags (see 25.6 to 25.7, 27.3 and 29.3), 
		the following transformation shall conceptually be applied before performing the check for tag uniqueness:
		이 권장 표준이 별개의 태그를 요구하는 경우(25.6에서 25.7, 27.3 및 29.3 참조) 태그 고유성에 대한 검사를 수행하기 전에 
		다음 변환이 개념적으로 적용되어야 합니다.

52.7.1	A new element or alternative (called the conceptually-added element, see 52.7.2) is conceptually added at the extension insertion point if:
		새로운 element 또는 alternative(개념적으로 추가된 요소라고 함, 52.7.2 참조)는 다음과 같은 경우 확장 삽입 지점에 개념적으로 추가됩니다.

	a)	there are no extension markers but extensibility is implied in the module header, and then an extension marker is added 
		and the new element is added as the first addition after that extension marker; or
		ExtensionMarker는 없지만 모듈 헤더에 extensibility 가 암시된 다음 ExtensionMarker가 (해당 유형에)추가되고 
		새 요소가 해당 확장 마커(추가한 확장 마커) 다음에 첫 번째 추가로 추가됩니다.

	b)	there is a single extension marker in a CHOICE or SEQUENCE or SET, 
		and then the new element is added at the end of the CHOICE or SEQUENCE or SET immediately prior to the closing brace; or
		CHOICE 또는 SEQUENCE 또는 SET에 단일 ExtensionMarker가 있고 닫는 중괄호 바로 앞의 CHOICE 또는 SEQUENCE 또는 SET 끝에 새 요소가 추가됩니다.

	c)	there are two extension markers in a CHOICE or SEQUENCE or SET, and then the new element is added immediately before the second extension marker.
		CHOICE, SEQUENCE 또는 SET에 두 개의 ExtensionMarker가 있으며 두 번째 ExtensionMarker 바로 앞에 새 요소가 추가됩니다.

52.7.2	This conceptually-added element is solely for the purposes of checking legality through the application of rules requiring distinct tags (see 25.6 to 25.7, 27.3 and 29.3).
		It is conceptually-added after the application of automatic tagging (if applicable) and the expansion of COMPONENTS OF.
		이 개념적으로 추가된 요소는 고유한 태그를 요구하는 규칙의 적용을 통해 합법성을 확인하기 위한 목적으로만 사용됩니다(25.6~25.7, 27.3 및 29.3 참조).
		AUTOMATICS TAGS(해당되는 경우)의 적용 및 COMPONENTS OF의 확장 후에 개념적으로 추가됩니다.

52.7.3	The conceptually-added element is defined to have a tag which is distinct from the tag of all normal ASN.1 types,
		but which matches the tag of all such conceptually-added elements and matches the indeterminate tag of the open type, 
		as specified in Rec. ITU-T X.681 | ISO/IEC 8824-2, 14.2, Note 2.
		개념적으로 추가된 요소는 모든 일반 ASN.1 유형의 태그와 구별되지만 개념적으로 추가된 모든 요소의 태그와 일치하고 
		OpenType의 미정 태그와 일치하는 태그를 갖도록 정의됩니다.

		NOTE -	The rules concerning tag uniqueness relating to the conceptually added element and to the open type, 
				together with the rules requiring distinct tags (see 25.6 to 25.7, 27.3 and 29.3) are necessary and sufficient to ensure that:
				개념적으로 추가된 요소 및 OpenType과 관련된 태그 고유성에 관한 규칙은 
				고유한 태그를 요구하는 규칙(25.6~25.7, 27.3 및 29.3 참조)과 함께 다음을 보장하는 데 필요하고 충분합니다.

			a)	any unknown extension addition can be unambiguously attributed to a single insertion point when a BER encoding is decoded; and
				알 수 없는 ExtensionAddition은 BER 인코딩이 디코딩될 때 단일 삽입 지점에 명확하게 기인할 수 있습니다.

			b)	unknown extension additions can never be confused with OPTIONAL elements.
				알 수 없는 ExtensionAdditions는 OPTIONAL 요소와 혼동될 수 없습니다.

		In PER the above rules are sufficient but are not necessary to ensure these properties. 
		They are nonetheless imposed as rules of ASN.1 to ensure independence of the notation from encoding rules.
		PER에서 위의 규칙은 충분하지만 이러한 속성을 보장하는 데 필요한 것은 아닙니다. 
		그럼에도 불구하고 인코딩 규칙에서 표기법의 독립성을 보장하기 위해 ASN.1의 규칙으로 부과됩니다.

52.7.4	If, with these conceptually-added elements, the rules requiring distinct types are violated, then the specification has made illegal use of the extensibility notation.
		이러한 개념적으로 추가된 요소를 사용하여 고유한 유형을 요구하는 규칙을 위반하는 경우 사양에서 확장성 표기법을 불법적으로 사용한 것입니다.

		NOTE -	The purpose of the above rules is to make precise restrictions arising from the use of insertion points (particularly those 
				which are not at the end of SEQUENCEs or SETs or CHOICEs).
				위 규칙의 목적은 삽입 지점(특히 SEQUENCE, SET 또는 CHOICE의 끝에 있지 않은 경우)의 사용으로 인해 발생하는 정확한 제한을 만드는 것입니다.

				The restrictions are designed to ensure that in BER, DER and CER it is possible to attribute an unknown element 
				received by a version 1 system unambiguously to a specific insertion point. 
				이 규칙은 BER, DER 및 CER을 사용하는 버전 1 시스템에서 수신한 알 수 없는 요소를 특정 삽입 지점으로 명확하게 지정할 수 있도록 설계되었습니다.

				This would be important if the exception handling of such added elements was different for different insertion points.
				이러한 추가 요소의 예외 처리가 삽입 지점마다 다른 경우 이는 중요합니다.

### X.690
8.9		Encoding of a sequence value

8.9.1	The encoding of a sequence value shall be constructed.
		SEQUENCE 값의 인코딩은 constructed 여야 합니다.

8.9.2	The contents octets shall consist of the complete encoding of one data value from each of the types 
		listed in the ASN.1 definition of the sequence type, in the order of their appearance in the definition, 
		unless the type was referenced with the keyword OPTIONAL or the keyword DEFAULT.
		내용 옥텟은 SEQUENCE 유형의 ASN.1 정의에 나열된 각 유형의 완전한 인코딩으로 구성되어야 하고 
		유형에 키워드 OPTIONAL 또는 키워드 DEFAULT가 지정되지 않는 한 순서대로 나타나야 합니다.

8.9.3	The encoding of a data value may, but need not, be present for a type which was referenced with the keyword OPTIONAL or the keyword DEFAULT. 
		If present, it shall appear in the encoding at the point corresponding to the appearance of the type in the ASN.1 definition.
		데이터 값의 인코딩은 키워드 OPTIONAL 또는 키워드 DEFAULT로 참조된 유형에 대해 존재할 수 있지만 반드시 그럴 필요는 없습니다.
		존재하는 경우 ASN.1 정의에서 유형의 모양에 해당하는 지점에서 인코딩에 나타나야 합니다.

+-----------+---------------------------------------------------------------------------------------+
| SEQUENCE	| MODULE TAG OPTION																		|
+-----------+---------------------------+-----------------------+-----------------------------------+
| Element	| Explicit					| Implicit				| Automatic							|
+-----------+---------------------------+-----------------------+-----------------------------------+
| untagged	| element TLV				| element TLV			| context TL(element V or TLV)		|
| tagged	| context TL(element TLV)	| context TL(element V)	| context TL(element V or TLV)		|
+-----------+---------------------------+-----------------------+-----------------------------------+

->	SEQUENCE의 각 요소는 CONTEXT-SPECIFIC TAG를 명시했을때만 IMPLICIT나 EXPLICIT의 영향을 받는다.

	CONTEXT-SPECIFIC TAG를 모두 명시하지 않으면(untagged)
		EXPLICIT, IMPLICIT 모두 요소의 TAG, Length, Contents 를 인코딩 한다.
		AUTOMATIC TAGS는 각 요소에 자동으로 CONTEXT-SPECIFIC TAG를 할당하고, 이후 CONTEXT-SPECIFIC TAG를 명시한것과 동일하게 동작한다.

		EX/IMPLICIT	: { { element's class,	element's form, element's number }, IMPLICIT,	element's descriptor, __apply__ }
		AUTOMATIC	: { { CONTEXT_SPECIFIC, element's form, automated number }, automated,	element's descriptor, __apply__ }


	CONTEXT-SPECIFIC TAG를 모두 명시하면 
		EXPLICIT는 CONTEXT-SPECIFIC TAG를 이용하여 CONSTRUCT Form 으로 요소를 인코딩 하고, Contents 는 인코딩 되는 요소의 TAG, Length, Contents 를 포함한다.
		IMPLICIT는 CONTEXT-SPECIFIC TAG를 이용하여 요소의 형태에 따른 P/C Form 으로 인코딩한다. Contents 는 인코딩 되는 요소는 Contents 만 포함한다.
		AUTOMATIC TAGS는 IMPLICIT인 경우와 동일하게 동작하지만, 요소의 유형이 CHOICE, OpenType, DummyReference인 경우 EXPLICIT인 것 처럼 동작한다.

		EXPLICIT	: { { CONTEXT_SPECIFIC, CONSTRUCT,		assiged number },	EXPLICIT,	element's descriptor, __apply__ }
		IMPLICIT	: { { CONTEXT_SPECIFIC, element's form, assiged number },	IMPLICIT,	element's descriptor, __apply__ }
		AUTOMATIC	: { { CONTEXT_SPECIFIC, element's form, automated number },	automated,	element's descriptor, __apply__ }

	CONTEXT-SPECIFIC TAG를 일부만 명시하면 
		EXPLICIT, IMPLICIT 모두 CONTEXT-SPECIFIC TAG가 명시된 요소만 EXPLICIT및 IMPLICIT인 것 처럼 동작한다.
		AUTOMATIC TAGS는 CONTEXT-SPECIFIC TAG가 명시된 요소만 IMPLICIT인 것 처럼 동작하고, 그외에는 요소의 TAG, Length, Contents 를 인코딩한다.

	Total Case:
		untagged			: { { element's class,	element's form, element's number }, IMPLICIT,	element's descriptor, __apply__ }
		tagged EXPLICIT		: { { CONTEXT_SPECIFIC, CONSTRUCT,		assiged number },	EXPLICIT,	element's descriptor, __apply__ }
		tagged IMPLICIT		: { { CONTEXT_SPECIFIC, element's form, assiged number },	IMPLICIT,	element's descriptor, __apply__ }
		untagged AUTOMATIC	: { { CONTEXT_SPECIFIC, element's form, automated number }, automated,	element's descriptor, __apply__ }
*/

///////////////////////////////////////////////////////////////////////////////
// Encoder
// Dz1Asn1TypeDescr *descr, Dz1Asn1BerEncoder *encoder, Dz1ElasticBuf *dst, void *_src, bool_t *ret_is_constructed_form, void *param, Dz1Error *err
bool_t Dz1Asn1Sequence_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	int idx = 0;
	void *child_ptr = NULL;
	Dz1Asn1TypeDescrChild *i = NULL;
	Dz1Asn1TypeDescr *c_descr = NULL;

	for (idx = 0, i = descr->childs; errp->code == 0 && i->descr_tag != Dz1Asn1TagOpt_max; i++, idx++)
	{
		c_descr = NULL;
		if ((child_ptr = i->get_child(_src, &c_descr)) != NULL)
		{
			bool_t is_constructed = FALSE;
			if (c_descr == NULL) c_descr = i->descr;

			if (Dz1Asn1BerDecoderDataCtx_enc_child(dst, i, c_descr, child_ptr, NULL, &is_constructed, param, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1Asn1TypeDescrChild_isOptional(i, NULL) == FALSE) ERR_SET_OUT(errp, EPERM);	// is it OPTIONAL?? or in Extension Addition?
		else Dz1Error_set(errp, 0);
	}
	*ret_is_constructed_form = TRUE;

	return errp->code == 0 ? TRUE : FALSE;
}
// Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Decoder
static bool_t _seq_child_apply(Dz1Asn1WipValue *wip, Dz1Asn1BerDecoderStk *ret_stk, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
{
	Dz1Asn1WipCst *wip_seq = NULL;
	Dz1Asn1WipValue *ret_data = NULL;
	Dz1Asn1TypeDescrChild *child = NULL;
	if (0) { }
	else if ((wip_seq = wip->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((child = ret_stk->child) == NULL)
	{	// unknown element TAG
		if (ret_data->present != Dz1Asn1WipValuePresent_any) ERR_SET_OUT(errp, EFAULT);
		else if (_Dz1Asn1WipOpenTypeList_addOpenType(wip_seq->unknowns, (u32_t)(++dst->idx), &ret_data->x.any, errp) == FALSE) ERR_OUT(errp);
	}
	else
	{	// known element TAG
		Dz1Asn1Custom *wip_sto = NULL;

		Dz1Asn1BerDecoderCtx *ret_ctx = NULL;
		Dz1Asn1BerDecoderDataCtx *ret_data_ctx = NULL;

		if ((ret_ctx = ret_stk->ctx) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (ret_ctx->present != Dz1Asn1BerDecoderCtxPresent_data) ERR_SET_OUT(errp, EFAULT);
		else if ((ret_data_ctx = ret_ctx->x.data) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (ret_data_ctx->idx <= dst->idx)
			ERR_SET_OUT(errp, EPERM);													// sequence element should be in order

		else if ((wip_sto = wip_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (wip_sto->data == NULL) ERR_SET_OUT(errp, EFAULT);

		else if (child->apply_data(wip, child->descr, ret_data, (u32_t)(dst->idx = ret_data_ctx->idx), errp) == FALSE) ERR_OUT(errp);		// apply data
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Sequence_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1TypeDescr *descr = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0), called from ARRAY decoder
		Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : Meet EOC\n");
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{	// construct form, length is either soc or specific value
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
				indirect->tag = descr->tag;
				indirect->childs = descr->childs;
				indirect->ber_dec = Dz1Asn1BerDecoderDataCtx_dec_indirect;

				dst->idx = -1;		// initialize index
				dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			}
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
			else if ((wip_seq = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if ((wip_sto = wip_seq->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if (wip_sto->data == NULL)					ERR_SET_OUT(errp, EFAULT);
			else if (wip_seq->indirect == NULL)				ERR_SET_OUT(errp, EFAULT);
			// all structure is ready
			else if (stk->len == 0)
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : Zero Length Sequence\n");
				dst->state = Dz1Asn1BerDecoderDataState_max;
				ret = Dz1Asn1BerLength_ssoc;
			}
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_seq->indirect, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : Indirect explicit nested\n");
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
				{
					Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : receive EOC\n");
					dst->state = Dz1Asn1BerDecoderDataState_max;	// return EOC -> End of Constructed Decoding
					ret = Dz1Asn1BerLength_ssoc;
				}
				else
				{
					Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : receive DATA\n");

					// resolve destination data struct
					if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if (_seq_child_apply(wip, ret_stk, dst, errp) == FALSE) ERR_OUT(errp);
					else if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)
					{	// decode next element. (include EOC)
						if ((wip_seq = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
						else if (wip_seq->indirect == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_seq->indirect, errp) == FALSE) ERR_OUT(errp);
						else
						{
							Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : Indirect nested\n");
							ret = Dz1Asn1BerLength_ssoc;
						}
					}
					else if (stk->len == dst->u64data)
					{
						Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SEQUENCE : Reach to END\n");
						dst->state = Dz1Asn1BerDecoderDataState_max;	// reach end
						ret = Dz1Asn1BerLength_ssoc;
					}
					else ERR_SET_OUT(errp, EFAULT); // size fault
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	// primitive form
	else ERR_SET_OUT(errp, EPERM);			// sequence can't be primitive

	return errp->code == 0 ? ret : -1;
}
// Decoder
///////////////////////////////////////////////////////////////////////////////

