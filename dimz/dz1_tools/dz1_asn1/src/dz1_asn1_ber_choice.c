#include "dz1_asn1_codec_ber.h"

/*
8.13	Encoding of a choice value
		The encoding of a choice value shall be the same as the encoding of a value of the chosen type.
		CHOICE 값의 인코딩은 선택한 유형의 값 인코딩과 동일해야 합니다.

		NOTE 1 - The encoding may be primitive or constructed depending on the chosen type.
		인코딩은 선택한 유형에 따라 PRIMITIVE 또는 CONSTRUCTED일 수 있습니다.

		NOTE 2 - The tag used in the identifier octets is the tag of the chosen type, as specified in the ASN.1 definition of the choice type.
		식별자 옥텟에 사용된 태그는 CHOICE 유형의 ASN.1 정의에 지정된 대로 선택된 유형의 태그입니다.

->	모듈의 Tag Option 은 요소에 TAG를 설정했을때만 영향을 준다.
	요소에 TAG를 지정하지 않으면 모듈의 TAG 설정은 의미가 없다.
	요소에는 TAG에는 EXPLICIT, IMPLICIT을 쓸 수 없다. 따라서 모듈의 TAG 설정의 영향을 받는다.

	모듈이 IMPLICIT 또는 AUTOMATIC TAGS인 경우, 요소에 지정한 TAG 는 모두 IMPLICIT이 되지만,
	요소의 Type 이 CHOICE, OPEN, DummyReference인 경우 EXPLICIT이 된다.

	AUTOMATIC TAGS설정에서 요소에 일부만 태그를 할당한 경우, Class Number 는 자동할당하지 않는다.
	하지만 태그를 할당한 요소는 IMPLICIT/EXPLICIT 자동 설정이 적용된다.

*/
///////////////////////////////////////////////////////////////////////////////
// Choice Encoder
// Dz1ElasticBuf *dst, Dz1Asn1BerEncoderOpt enc_opt, void *_src, bool_t *ret_is_constructed_form, struct Dz1Asn1TypeDescr *descr, Dz1Asn1BerEncoder *encoder, void *param, Dz1Error *err
bool_t Dz1Asn1Choice_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	bool_t encoded = FALSE;

	void *child_ptr = NULL;
	Dz1Asn1TypeDescrChild *i = NULL;

	for (i = descr->childs; errp->code == 0 && encoded == FALSE && i->descr_tag != Dz1Asn1TagOpt_max; i++)
	{
		if ((child_ptr = i->get_child(_src, NULL)) != NULL)		// selected child
		{
			bool_t is_constructed = FALSE;
#if 1
			if (Dz1Asn1BerDecoderDataCtx_enc_child(dst, i, i->descr, child_ptr, NULL, &is_constructed, param, errp) == FALSE) ERR_OUT(errp);
			else
			{
				encoded = TRUE;
				if (ret_is_constructed_form) *ret_is_constructed_form = is_constructed;
				Dz1Error_set(errp, 0);
			}
#else
			Dz1Asn1TypeDescr *child_descr = i->descr;
			u8_t eoc[] = { 0x00, 0x00 };

			Dz1ElasticBuf *child_tl_elb = NULL;
			Dz1ElasticBuf *child_data_elb = NULL;
			bool_t child_eoc = FALSE, my_eoc = FALSE;

			char str_name[64];
			Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, ">>> CHOICE :  %s\n", str_name);

			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&child_data_elb);
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&child_tl_elb);

			if (0) { }
			// Check Some Element Constraints
			else if ((child_data_elb = _get_child_contents(child_descr, child_ptr, &is_constructed, param, errp)) == NULL) ERR_OUT(errp);
			else if (i->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE &&
					(child_tl_elb = _get_child_tag_length(child_descr, is_constructed, child_data_elb, &child_eoc, param, errp)) == NULL) ERR_OUT(errp);

			else if (Dz1Asn1Tag_isVoid(&i->tag) == FALSE)
			{
				ssize_t child_data_sz = 0;
				if ((child_data_sz = Dz1ElasticBuf_getDataSize(child_data_elb, errp)) < 0) ERR_OUT(errp);
				else if (i->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE)
				{	// OWN_TAG_LENGTH CHILD_TAG_LEN CHILD_DATA [CHILD_EOC] [OWN_EOC]
					ssize_t child_tl_sz = 0;
					if ((child_tl_sz = Dz1ElasticBuf_getDataSize(child_tl_elb, errp)) < 0) ERR_OUT(errp);
					else if (_encode_tag_length(dst, &i->tag, is_constructed,
							 child_tl_sz + child_data_sz + (child_eoc ? 2 : 0), &my_eoc, param, errp) == FALSE) ERR_OUT(errp);	// OWN_TAG_LENGTH
					else if (Dz1ElasticBuf_move(dst, child_tl_elb, errp) == FALSE) ERR_OUT(errp);								// CHILD_TAG_LEN
					else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);								// CHILD_DATA
					else if (child_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);				// [CHILD_EOC]
					else if (my_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);				// [OWNEOC]
					else 
					{ 
						encoded = TRUE; Dz1Error_set(errp, 0); 
					}
				}
				else
				{	// OWN_TAG_LENGTH CHILD_DATA [CHILD_EOC]
					if (_encode_tag_length(dst, &i->tag, is_constructed, child_data_sz, &my_eoc, param, errp) == FALSE) ERR_OUT(errp);	// OWN_TAG_LENGTH
					else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);										// CHILD_DATA
					else if (my_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);						// [OWNEOC]
					else { encoded = TRUE; Dz1Error_set(errp, 0); }
				}
			}
			else if (i->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE)
			{	// CHILD_TAG_LEN CHILD_DATA [CHILD_EOC]
				if (0) { }
				else if (Dz1ElasticBuf_move(dst, child_tl_elb, errp) == FALSE) ERR_OUT(errp);						// CHILD_TAG_LEN
				else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);						// CHILD_DATA
				else if (child_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);		// [CHILD_EOC]
				else { encoded = TRUE; Dz1Error_set(errp, 0); }
			}
			// CHILD_DATA
			else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);							// CHILD_DATA
			else { encoded = TRUE; Dz1Error_set(errp, 0); }

			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&child_tl_elb);
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&child_data_elb);
			break;
#endif
		}
	}

	if (encoded == FALSE) ERR_SET_OUT(errp, ENOENT);

	return errp->code == 0 ? TRUE : FALSE;
}
// Choice Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Choice Decoder
static bool_t _choice_child_apply(Dz1Asn1WipValue *wip, Dz1Asn1BerDecoderStk *ret_stk, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
{
	Dz1Asn1WipValue *ret_data = NULL;
	Dz1Asn1WipCst *wip_seq = NULL;
	Dz1Asn1Custom *storage = NULL;
	Dz1Asn1TypeDescrChild *child = NULL;

	if (0) { }
	else if ((wip_seq = wip->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((child = ret_stk->child) == NULL)
	{	// unknown element TAG -> append to OpenType List
		if (ret_data->present != Dz1Asn1WipValuePresent_any) ERR_SET_OUT(errp, EFAULT);
		else if (_Dz1Asn1WipOpenTypeList_addOpenType(wip_seq->unknowns, (u32_t)-1, &ret_data->x.any, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{	// known element TAG -> apply to WIP
		Dz1Asn1BerDecoderCtx *ret_ctx = NULL;
		Dz1Asn1BerDecoderDataCtx *ret_data_ctx = NULL;
		if ((ret_ctx = ret_stk->ctx) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (ret_ctx->present != Dz1Asn1BerDecoderCtxPresent_data) ERR_SET_OUT(errp, EFAULT);
		else if ((ret_data_ctx = ret_ctx->x.data) == NULL) ERR_SET_OUT(errp, EFAULT);

		else if ((storage = wip_seq->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
		else if (storage->data == NULL)					ERR_SET_OUT(errp, EFAULT);

		else if (child->apply_data(wip, child->descr, ret_data, (u32_t)(dst->s32data = ret_data_ctx->s32data), errp) == FALSE) ERR_OUT(errp);		// apply data
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#if 0
static ssize_t _Dz1Asn1BerDecoderDataCtx_dec_choice(Dz1Asn1BerDecoder_contentsDecArgs)
{	// Always called from CHOICE
	ssize_t ret = 0;

	Dz1Asn1Tag *tag = stk->tag;
	Dz1Asn1TypeDescr *descr = NULL;

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0), called from CONSTRUCT decoder & at end of OPTIONAL CHOICE
		Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ INDIRECT : Meet EOC\n");
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
	// primitive or construct form, length is either soc or specific value
	else
	{	
		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		Dz1Asn1TypeDescrChild *child = NULL;
		Dz1Asn1TypeDescr *child_descr = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			// no wip
			else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if (dst->wip != NULL) ERR_SET_OUT(errp, EFAULT);
			// resolve child & call decoder
			else if ((child = stk->child = Dz1Asn1TypeDescr_findChild(descr, tag, &dst->idx)) == NULL /*&& (child = stk->child = Dz1Asn1TypeDescr_findChildOpenType(descr, &dst->idx)) == NULL*/)
			{	// unknown child -> OpenType with IMPLICIT
				char str_tag[64], str_name[64];					

				dst->idx = -1;

				child_descr = &dz1Asn1TypeDescrOpenType;
				Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, 64, NULL);

				if (tag->flag == Dz1Asn1TagFlag_primitive)
				{	// primitive form
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Unknown Child = %s : %s : switched\n", Dz1Asn1TagA_printable(tag, str_tag, 64), str_name);

					stk->descr = child_descr;
					dst->state = Dz1Asn1BerDecoderDataState_initial;
					return child_descr->ber_dec(dst, src, stk, decoder, errp);
				}
				else
				{	// constructed form
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Unknown Child = %s : %s : explicit nested\n", Dz1Asn1TagA_printable(tag, str_tag, 64), str_name);

					dst->u32data = (u32_t)Dz1Asn1TagOpt_explicit;
					if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, child_descr, errp) == FALSE) ERR_OUT(errp);
					else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
				}
			}
			else
			{	// known child -> Child Descriptor(and their Tag Mode)
				char str_tag[64], str_name[64];

				child_descr = child->descr;
				Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, 64, NULL);

				if (tag->flag == Dz1Asn1TagFlag_primitive || Dz1Asn1Tag_isVoid(&child->tag))
				{	// primitive
					Dz1Thread_tlog(DZ1_THREAD_LOG_SEQUENCE, stk->tab, "@@@ _CHOICE : Known Child = %s : %s : switched\n", Dz1Asn1TagA_printable(tag, str_tag, 64), str_name);

					stk->descr = child_descr;
					dst->state = Dz1Asn1BerDecoderDataState_initial;
					return child_descr->ber_dec(dst, src, stk, decoder, errp);
				}
				// constructed form
				else
				{	// prefixed -> depend on child->descr_tag
					Dz1Asn1TagOpt tag_opt = child->descr_tag;
					dst->u32data = (u32_t)tag_opt;

					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Known Child = %s : %s : %s nested\n",
								   Dz1Asn1TagA_printable(tag, str_tag, 64), str_name, Dz1Asn1TagOptStrA(tag_opt));

					if (Dz1Asn1BerDecoder_stackPushChild(decoder, child_descr, tag_opt, tag, stk->len, errp) == FALSE) ERR_OUT(errp);
					else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
				}
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
				{	// return EOC -> dst->wip should made
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : receive EOC\n");
					if (dst->wip == NULL) ERR_SET_OUT(errp, EFAULT);
					else { dst->state = Dz1Asn1BerDecoderDataState_max; ret = Dz1Asn1BerLength_ssoc; }
				}
				else 
				{	// return DATA
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : receive DATA(%s)\n", Dz1Asn1TagOptStrA((Dz1Asn1TagOpt)dst->u32data));

					if (dst->wip != NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if ((dst->wip = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);	// toss data to parent
					else 
					{
						ret_stk->data = NULL;
						// in INDIRECT decoder, Here should be End of Encoding or expect EOC
						if (stk->len == Dz1Asn1BerLength_soc)
						{	// this object need EOC
							Dz1Asn1TagOpt it_was = (Dz1Asn1TagOpt)dst->u32data;
							if (it_was == Dz1Asn1TagOpt_explicit)
							{	//  EOC is belonged this Object
								if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrEOC, errp) == FALSE) ERR_OUT(errp);
								else 
								{
									Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Indirect nested(EOC)\n");
									dst->state = Dz1Asn1BerDecoderDataState_nested;
									ret = Dz1Asn1BerLength_ssoc;
								}
							}
							else
							{	// EOC is not mine
								Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Complete\n");
								dst->state = Dz1Asn1BerDecoderDataState_max;
								ret = Dz1Asn1BerLength_ssoc;
							}
						}
						else if (stk->len == dst->u64data)
						{	// Size Check
							Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ _CHOICE : Reach to END\n");
							dst->state = Dz1Asn1BerDecoderDataState_max;
							ret = Dz1Asn1BerLength_ssoc;
						}
						else ERR_SET_OUT(errp, EFAULT);	// size fault
					}
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? ret : -1;
}
#endif
ssize_t Dz1Asn1Choice_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1TypeDescr *descr = NULL;
	Dz1Asn1Tag *tag = stk->tag;
	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0), called from CONSTRUCT decoder & at end of OPTIONAL CHOICE
		if (dst->wip == NULL && (dst->wip = Dz1Asn1WipValue_gen(errp)) == NULL) ERR_OUT(errp);	// critical
		else
		{
			dst->state = Dz1Asn1BerDecoderDataState_max;
			ret = Dz1Asn1BerLength_ssoc;
		}
	}
	else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{	// primitive form or construct form, length is either soc or specific value
		Dz1Asn1TagOpt tag_opt = (tag->flag == Dz1Asn1TagFlag_construct) ? Dz1Asn1TagOpt_explicit : Dz1Asn1TagOpt_implicit;

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
//				indirect->ber_dec = _Dz1Asn1BerDecoderDataCtx_dec_choice;
				indirect->ber_dec = Dz1Asn1BerDecoderDataCtx_dec_indirect;
				dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			}
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if (dst->wip == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
			else if ((wip_seq = wip->x.cst_seq) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if ((wip_sto = wip_seq->storage) == NULL)	ERR_SET_OUT(errp, EFAULT);
			else if (wip_sto->data == NULL)					ERR_SET_OUT(errp, EFAULT);
			else if (wip_seq->indirect == NULL)				ERR_SET_OUT(errp, EFAULT);
			// resolve child & call decoder
//			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, wip_seq->indirect, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1Asn1BerDecoder_stackPushImplicit(decoder, wip_seq->indirect, stk->tag, stk->len, errp) == FALSE) ERR_OUT(errp);
//			else if (Dz1Asn1BerDecoder_stackPushChild(decoder, wip_seq->indirect, tag_opt, stk->tag, stk->len, errp) == FALSE) ERR_OUT(errp);
			else 
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_CHOICE, stk->tab, "@@@ CHOICE : Indirect nested\n");
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
				{	// return EOC -> dst->wip should made
					Dz1Thread_tlog(DZ1_THREAD_LOG_CHOICE, stk->tab, "@@@ CHOICE : receive EOC\n");
					if (dst->wip == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst->state = Dz1Asn1BerDecoderDataState_max;
						ret = Dz1Asn1BerLength_ssoc;
					}
				}
				else
				{	// return DATA
					Dz1Thread_tlog(DZ1_THREAD_LOG_CHOICE, stk->tab, "@@@ CHOICE : receive DATA\n");

					if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if (_choice_child_apply(wip, ret_stk, dst, errp) == FALSE) ERR_OUT(errp);
#if 0
					// in CHOICE decoder, Here should be End of Encoding or expect EOC
					else if (stk->len == Dz1Asn1BerLength_soc)
					{	// handling EOC : CHOICE always call child decoder with EXPLICIT
						if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrEOC, errp) == FALSE) ERR_OUT(errp);
						else
						{
							Dz1Thread_tlog(DZ1_THREAD_LOG_CHOICE, stk->tab, "@@@ CHOICE : Indirect nested(EOC)\n");
							ret = Dz1Asn1BerLength_ssoc;
						}
					}
					else if (dst->u64data == stk->len)
					{
						Dz1Thread_tlog(DZ1_THREAD_LOG_CHOICE, stk->tab, "@@@ CHOICE : Reach to END\n");
						dst->state = Dz1Asn1BerDecoderDataState_max;
						ret = Dz1Asn1BerLength_ssoc;
					}
					else ERR_SET_OUT(errp, EFAULT);	// size fault
#else
					else
					{	// CHOICE does not need to handling EOC
						ret = Dz1Asn1BerLength_ssoc;
						dst->state = Dz1Asn1BerDecoderDataState_max;
					}
#endif
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? ret : -1;
}
// Choice Decoder
///////////////////////////////////////////////////////////////////////////////
