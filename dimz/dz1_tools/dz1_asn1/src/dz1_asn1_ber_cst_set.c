#include "dz1_asn1_codec_ber.h"

/*
### X.680
25.3	When the "ComponentTypeLists" production occurs within the definition of a module for which automatic tagging is selected (see 13.3), 
		and none of the occurrences of "NamedType" in any of the first three alternatives for "ComponentType" is a textually tagged type (see 25.2), 
		then the automatic tagging transformation is selected for the entire "ComponentTypeLists", otherwise it is not.

		AUTOMATIC TAGS가 선택된 모듈(13.3 참조)의 정의 내에서 "ComponentTypeLists" 생성이 발생하고 "ComponentType"에 대한 처음 세 가지 대안에서 
		NamedType이 텍스트로 태깅된 유형(25.2 참조)이 아닌 경우 전체 "ComponentTypeLists"에 대해 AUTOMATIC TAGS 변환이 선택되고 그렇지 않으면 선택되지 않습니다. 

		-> AUTOMATIC TAGS가 적용된 모듈 내에서, 단일 ComponentTypeLists에서 나타나는 모든 CompomentType이 처음 세가지 방법중 하나로 기술될 때 
		나타나는 NamedType에 텍스트로 지정한 테그가 없는 경우 AUTOMATIC TAGS가 적용 됩니다.

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

27	Notation for set types

27.2	 "Type" in the "COMPONENTS OF Type" notation shall be a set type.  
		"COMPONENTS OF Type" 표기법의 "Type"은 SET 유형이어야 합니다.

		The "COMPONENTS OF Type" notation shall be used to define the inclusion, at this point in the list of components, of all the component types of the referenced type, 
		except for any extension marker and extension additions that may be present in the "Type". 
		"COMPONENTS OF Type" 표기법은 해당 "Type"에 "..." 및 ExtensionAddition을 제외한 모든 구성 요소 유형을 구성 요소 목록의 이 지점에서 포함하는 것을 정의하는 데 사용됩니다.

		(Only the "RootComponentTypeList" of the "Type" in the "COMPONENTS OF Type" is included; extension markers and extension additions, 
		if any, are ignored by the "COMPONENTS OF Type" notation.)
		("COMPONENTS OF Type"에서 "Type"의 "RootComponentTypeList"만 포함됩니다. "..." 및 ExtensionAddition이 있는 경우 
		"COMPONENTS OF Type" 표기법에서는 무시됩니다.) 

		Any subtype constraint applied to the referenced type is ignored by this transformation.
		참조된 유형에 적용된 모든 하위 유형 제약 조건은 이 변환에서 무시됩니다.

		NOTE -	This transformation is logically completed prior to the satisfaction of the requirements in the following subclauses.
				이 변환은 다음 하위 절의 요구 사항이 충족되기 전에 논리적으로 완료됩니다.

27.3	The "ComponentType" types in a set type shall all have different tags (see 31.2). 
		SET 유형의 "ComponentType" 유형은 모두 다른 태그를 가져야 합니다(31.2 참조). 

		The tag of each new "ComponentType" added to the "ExtensionAdditions" shall be canonically greater (see 8.6) than those of the other components in the "ExtensionAdditions".
		"ExtensionAdditions"에 추가된 각각의 새로운 "ComponentType"의 태그는 "ExtensionAdditions"에 있는 다른 구성요소의 태그보다 표준적으로 더 커야 합니다(8.6 참조).

		NOTE -	Where the "TagDefault" for the module in which this notation appears is AUTOMATIC TAGS, this is achieved regardless of the actual "ComponentType"s,
				as a result of the application of 25.8.  (See also 52.7.)
				이 표기법이 나타나는 모듈에 대한 "TagDefault"가 AUTOMATIC TAGS인 경우 25.8의 적용 결과로 실제 "ComponentType"에 관계없이 달성됩니다. (52.7 참조.)

27.4	Subclauses 25.3 and 25.8 to 25.14 also apply to set types.
		하위 조항 25.3 및 25.8 ~ 25.14도 SetType에 적용됩니다.

		25.3  : AUTOMATIC TAGS가 적용된 모듈에서 AUTOMATIC TAGS를 적용 할지 말지 판단하는 기준(수동 태그가 없어야 함)
		25.8  : AUTOMATIC TAGS를 적용 적용하는 시점
		25.9  : Root ComponentTypeList에 수동 태그가 없으면 ExtenstionAddition에도 수동 태그가 없어야 함
		25.10 : AUTOMATIC TAGS 적용 방법
		25.11 : OPTIONAL, DEFAULT 처리 방법
		25.12 : 유효한 OPTIONAL, DEFAULT 요소 처리 방법
		25.13 : ExtensionAdditionGroup 처리 방법
		25.14 : 변수명 중복 금지

27.5	All set types have a tag which is universal class, number 17.
		모든 세트 유형에는 UNIVERSAL 17인 태그가 있습니다.
		NOTE -	Set-of types have the same tag as set types (see 28.2).
				SET-OF 유형은 Set Types 과 동일한 태그를 갖습니다(28.2 참조).

27.6	There shall be no semantics associated with the order of values in a set type.
		Set Type 의 값 순서와 관련된 의미 체계는 없습니다.

### X.690

8.11	Encoding of a set value

8.11.1	The encoding of a set value shall be constructed.
		SET 값의 인코딩은 constructed 여야 합니다.

8.11.2	The contents octets shall consist of the complete encoding of a data value from each of the types listed in the ASN.1 definition of the set type, 
		in an order chosen by the sender, unless the type was referenced with the keyword OPTIONAL or the keyword DEFAULT.
		내용 옥텟은 ASN.1 SET 유형 정의에 나열된 각 유형의 데이터 값을 유형이 키워드 OPTIONAL 또는 키워드 DEFAULT로 참조되지 않는 한 
		보낸 사람이 선택한 순서대로 완전히 인코딩하는 것으로 구성되어야 합니다.

8.11.3	The encoding of a data value may, but need not, be present for a type which was referenced with the keyword OPTIONAL or the keyword DEFAULT.
		데이터 값의 인코딩은 키워드 OPTIONAL 또는 키워드 DEFAULT로 참조된 유형에 대해 존재할 수 있지만 반드시 그럴 필요는 없습니다.
		NOTE -	The order of data values in a set value is not significant, and places no constraints on the order during transfer.
				SET 값에서 데이터 값의 순서는 중요하지 않으며 전송하는 동안 순서에 제약을 두지 않습니다.

9		Canonical encoding rules

9.3		Set components
		The encodings of the component values of a set value shall appear in an order determined by their tags as specified in 8.6 of Rec. ITU-T X.680 | ISO/IEC 8824-1. 
		설정 값의 구성 요소 값의 인코딩은 X.680의 8.6에 지정된 대로 해당 태그에 의해 결정된 순서로 나타납니다.

		Additionally, for the purposes of determining the order in which components are encoded when one or more component is an untagged choice type, 
		each untagged choice type is ordered as though it has a tag equal to that of the smallest tag in that choice type or any untagged choice types nested within.
		또한, 하나 이상의 구성 요소가 태그가 지정되지 않은 Choice Type 일 때 구성 요소가 인코딩되는 순서를 결정하기 위해 태그가 지정되지 않은 각 Choice Type 은 
		마치 해당 Choice Type 또는 중첩된 태그가 없는 Choice Type 들 내에서 가장 작은 태그 값의 태그와 동일한 태그가 있는 것처럼 정렬됩니다. 

		EXAMPLE
		In the following which assumes a tagging environment of IMPLICIT TAGS:
		IMPLICIT TAGS의 태깅 환경을 가정하는 다음에서:
		A ::= SET
		{
			a	[3] INTEGER,
			b	[1] CHOICE
			{
				c	[2] INTEGER,
				d	[4] INTEGER
			},
			e	CHOICE
			{
				f	CHOICE
				{
					g	[5] INTEGER,
					h	[6] INTEGER
				},
				i	CHOICE
				{
					j	[0] INTEGER
				}
			}
		}
		the order in which the components of the set are encoded will always be e, b, a, since the tag [0] sorts lowest, then [1], then [3].
		위의 Set Type 의 구성 요소가 인코딩 되는 순서는 항상 e, b, a 가 됩니다. 태그 [0]이 가장 낮은 순서로 정렬되고 그 다음 [1], [3]이 정렬되기 때문입니다.

10		Distinguished encoding rules

10.3	Set components
		The encodings of the component values of a set value shall appear in an order determined by their tags as specified in 8.6 of Rec. ITU-T X.680 | ISO/IEC 8824-1.
		Set Type 구성 요소의 인코딩은 X.680의 8.6에 지정된 대로 해당 태그에 의해 결정된 순서로 나타납니다.
		NOTE -	Where a component of the set is an untagged choice type, the location of that component in the ordering will depend on the tag of the choice component being encoded.
				Set Type 의 구성 요소가 태그가 지정되지 않은 Choice Type 인 경우 순서에서 해당 구성 요소의 위치는 인코딩 되는 CHOICE 구성 요소의 태그에 따라 달라집니다.
*/

static bool_t _set_child_apply(Dz1Asn1WipValue *wip, Dz1Asn1BerDecoderStk *ret_stk, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
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

																						// set element : no means to order

		else if ((wip_sto = wip_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (wip_sto->data == NULL) ERR_SET_OUT(errp, EFAULT);

		else if (child->apply_data(wip, child->descr, ret_data, (u32_t)(dst->idx = ret_data_ctx->idx), errp) == FALSE) ERR_OUT(errp);		// apply data
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Set_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1TypeDescr *descr = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : Meet EOC\n");
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{	// constructed form, length is SOC or some value
		Dz1Asn1WipValue *wip = NULL;
		Dz1Asn1WipCst *wip_set = NULL;
		Dz1Asn1Custom *wip_sto = NULL;
		Dz1Asn1TypeDescr *indirect = NULL;

		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_cst_seq, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
			else if ((wip_set = wip->x.cst_seq = Dz1Asn1WipCst_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((wip_sto = wip_set->storage = Dz1Asn1TypeDescr_genWipCustom(descr, errp)) == NULL) ERR_OUT(errp);
			else if ((indirect = wip_set->indirect = Dz1Asn1TypeDescr_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				indirect->childs = descr->childs;
				indirect->ber_dec = Dz1Asn1BerDecoderDataCtx_dec_indirect;

				dst->idx = -1;
				dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			}
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
			else if ((wip_set = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if ((wip_sto = wip_set->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if (wip_sto->data == NULL)					ERR_SET_OUT(errp, EFAULT);
			else if (wip_set->indirect == NULL)				ERR_SET_OUT(errp, EFAULT);
			// all structure is ready
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_set->indirect, errp) == FALSE) ERR_OUT(errp);
			else 
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : Indirect explicit nested\n");
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
				{	// return EOC -> End of Constructed Decoding
					Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : receive EOC\n");
					dst->state = Dz1Asn1BerDecoderDataState_max;
					ret = Dz1Asn1BerLength_ssoc;
				}
				else
				{	// return DATA
					Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : receive DATA\n");

					// resolve destination data struct
					if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if (_set_child_apply(wip, ret_stk, dst, errp) == FALSE) ERR_OUT(errp);
					else if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)
					{	// call next element decoder
						if ((wip_set = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
						else if (wip_set->indirect == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_set->indirect, errp) == FALSE) ERR_OUT(errp);
						else
						{
							Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : Indirect nested\n");
							ret = Dz1Asn1BerLength_ssoc;
						}
					}
					else if (stk->len == dst->u64data)
					{
						Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ SET : Reach to END\n");
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
	else ERR_SET_OUT(errp, EPERM);		// SET can't be primitive
	return errp->code == 0 ? ret : -1;
}
