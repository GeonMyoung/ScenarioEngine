#include "dz1_asn1_codec_ber.h"

///////////////////////////////////////////////////////////////////////////////
// Contents Encoder
Dz1ElasticBuf *_get_child_contents(Dz1Asn1TypeDescr *descr, void *src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *errp)
{
	Dz1ElasticBuf *ret = Dz1ElasticBuf_new(512, FALSE, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);

		if (Dz1Asn1TypeDescr_chkConformance(descr, src, NULL) == FALSE)
		{
			char str_name[512];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, sizeof(str_name), NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Conformance Violation [%s]\n", str_name);
			ERR_SET_OUT(errp, EPERM);
		}
		else if (descr->ber_enc(ret, descr, src, ret_is_constructed_form, param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Contents Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Tag + Length Encoder for child
Dz1ElasticBuf *_get_child_tag_length(Dz1Asn1TypeDescr *descr, bool_t is_constructed, Dz1ElasticBuf *data, bool_t *ret_encode_eoc, Dz1Asn1BerEncoderArg *param, Dz1Error *errp)
{
	Dz1ElasticBuf *ret = NULL;
	if (descr == NULL || data == NULL || param == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		s64_t length = 0;
		ssize_t data_sz = 0;
		
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);

		if (Dz1Asn1Tag_enc_BER(ret, descr->tag, is_constructed, param, errp) < 0) ERR_OUT(errp);
		else if ((data_sz = Dz1ElasticBuf_getDataSize(data, errp)) < 0) ERR_OUT(errp);
		else if (_get_encode_length(&length, data_sz, is_constructed, param->opt, ret_encode_eoc, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1BerLength_enc_BER(ret, length, param, errp) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Tag + Length Encoder for child
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Tag + Length Encoder
bool_t _encode_tag_length(Dz1ElasticBuf *dst, Dz1Asn1Tag *tag, bool_t is_constructed, ssize_t child_sz, bool_t *ret_my_eoc, Dz1Asn1BerEncoderArg *param, Dz1Error *errp)
{
	u64_t length = 0;
	if (0) { }
	else if (Dz1Asn1Tag_enc_BER(dst, tag, is_constructed, param, errp) < 0) ERR_OUT(errp);
	else if (_get_encode_length(&length, child_sz, is_constructed, param->opt, ret_my_eoc, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1Asn1BerLength_enc_BER(dst, length, param, errp) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Tag + Length Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prefixed Target Encoder
bool_t Dz1Asn1BerDecoderDataCtx_enc_child(Dz1ElasticBuf *dst, Dz1Asn1TypeDescrChild *child, Dz1Asn1TypeDescr *c_descr,  void *src, Dz1Asn1Tag *tag_alt, bool_t *ret_is_complete_form, Dz1Asn1BerEncoderArg *param, Dz1Error *errp)
{
	u8_t eoc[] = { 0x00, 0x00 };
	bool_t is_complete = FALSE;

	Dz1Asn1TypeDescr _child_descr = *c_descr, *child_descr = &_child_descr;

	Dz1ElasticBuf *child_tl_elb = NULL;
	Dz1ElasticBuf *child_data_elb = NULL;
	bool_t child_eoc = FALSE, my_eoc = FALSE;

	char str_name[512];

	pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&child_data_elb);
	pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&child_tl_elb);

	if (tag_alt != NULL) *child_descr->tag = *tag_alt;

	Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, sizeof(str_name), NULL);
	Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "_enc_child() : %s\n", str_name);

	if (0) { }
	// Check Some Element Constraints
	else if (Dz1Asn1TypeDescrChild_isDefault(child, src) == TRUE) { }	// is it same as DEFAULT??
	else if ((child_data_elb = _get_child_contents(child_descr, src, &is_complete, param, errp)) == NULL) ERR_OUT(errp);
	else if (child->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE &&
			(child_tl_elb = _get_child_tag_length(child_descr, is_complete, child_data_elb, &child_eoc, param, errp)) == NULL) ERR_OUT(errp);

	else if (Dz1Asn1Tag_isVoid(&child->tag) == FALSE)
	{
		ssize_t child_data_sz = 0;
		if ((child_data_sz = Dz1ElasticBuf_getDataSize(child_data_elb, errp)) < 0) ERR_OUT(errp);
		else if (child->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE)
		{	// OWN_TAG_LENGTH CHILD_TAG_LEN CHILD_DATA [CHILD_EOC] [OWN_EOC] -> double complete form
			ssize_t child_tl_sz = 0;
			if ((child_tl_sz = Dz1ElasticBuf_getDataSize(child_tl_elb, errp)) < 0) ERR_OUT(errp);
			else if (_encode_tag_length(dst, &child->tag, TRUE,
							child_tl_sz + child_data_sz + (child_eoc ? 2 : 0), &my_eoc, param, errp) == FALSE) ERR_OUT(errp);		// OWN_TAG_LENGTH
			else if (Dz1ElasticBuf_move(dst, child_tl_elb, errp) == FALSE) ERR_OUT(errp);											// CHILD_TAG_LEN
			else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);											// CHILD_DATA
			else if (child_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);							// [CHILD_EOC]
			else if (my_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);							// [OWNEOC]
			else
			{
				Dz1Error_set(errp, 0);
				if (ret_is_complete_form) *ret_is_complete_form = TRUE;
			}
		}
		else
		{	// OWN_TAG_LENGTH CHILD_DATA [CHILD_EOC] -> complete form
			if (_encode_tag_length(dst, &child->tag, is_complete, child_data_sz, &my_eoc, param, errp) == FALSE) ERR_OUT(errp);		// OWN_TAG_LENGTH
			else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);											// CHILD_DATA
			else if (my_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);							// [OWNEOC]
			{
				Dz1Error_set(errp, 0);
				if (ret_is_complete_form) *ret_is_complete_form = TRUE;
			}
		}
	}
	else if (child->descr_tag == Dz1Asn1TagOpt_explicit && Dz1Asn1Tag_isVoid(child_descr->tag) == FALSE)
	{	// CHILD_TAG_LEN CHILD_DATA [CHILD_EOC] -> complete form
		if (0) { }
		else if (Dz1ElasticBuf_move(dst, child_tl_elb, errp) == FALSE) ERR_OUT(errp);												// CHILD_TAG_LEN
		else if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);												// CHILD_DATA
		else if (child_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);								// [CHILD_EOC]
		else
		{
			Dz1Error_set(errp, 0);
			if (ret_is_complete_form) *ret_is_complete_form = TRUE;
		}
	}
	else
	{	// CHILD_DATA -> constructed_form : depend on CHILD_DATA
		if (Dz1ElasticBuf_move(dst, child_data_elb, errp) == FALSE) ERR_OUT(errp);													// CHILD_DATA
		else
		{
			Dz1Error_set(errp, 0);
			if (ret_is_complete_form) *ret_is_complete_form = is_complete;
		}
	}
	pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&child_tl_elb);
	pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&child_data_elb);

	return errp->code == 0 ? TRUE : FALSE;
}
// Child Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prefixed Type Encoder
// Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err
bool_t Dz1Asn1Prefixed_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t eoc[] = { 0x00, 0x00 };
	bool_t is_constructed = FALSE;

	Dz1Asn1TypeDescrChild *child = descr->childs; // fist child
	if (Dz1Asn1BerDecoderDataCtx_enc_child(dst, child, child->descr, _src, descr->tag, &is_constructed, param, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		if (ret_is_constructed_form) *ret_is_constructed_form = is_constructed;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Prefixed Type Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Decoder Post Process
static bool_t _dec_indirect_post_proc(Dz1Asn1BerDecoderDataCtx *dst, Dz1Asn1BerDecoderStk *stk, Dz1Asn1BerDecoder *decoder, str_t log_prefix, Dz1Error *errp)
{
	if (stk->len == Dz1Asn1BerLength_soc)
	{	// this object need EOC
		Dz1Asn1TagOpt it_was = (Dz1Asn1TagOpt)dst->u32data;
		if (it_was == Dz1Asn1TagOpt_explicit)
		{	// EOC is belonged this Object
			if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrEOC, errp) == FALSE) ERR_OUT(errp);
			else 
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ %s : Indirect nested(EOC)\n", log_prefix);
				dst->state = Dz1Asn1BerDecoderDataState_nested;
				Dz1Error_set(errp, 0);
			}
		}
		else
		{	// EOC is not mine
			Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ %s : Complete\n", log_prefix);
			dst->state = Dz1Asn1BerDecoderDataState_max;
			Dz1Error_set(errp, 0);
		}
	}
	else if (stk->len == dst->u64data)
	{	// Size Check
		Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ %s : Reach to END\n", log_prefix);
		dst->state = Dz1Asn1BerDecoderDataState_max;
		Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EFAULT);	// size fault
	return errp->code == 0 ? TRUE : FALSE;
}
// Decoder Post Process
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prefixed type Decoder
static bool_t _prefix_child_apply(Dz1Asn1TypeDescrChild *child, Dz1Asn1WipValue *wip, Dz1Asn1BerDecoderStk *ret_stk, Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *errp)
{
	Dz1Asn1WipValue *ret_data = NULL;
	if (0) { }
	else if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (child->apply_data(wip, child->descr, ret_data, -1, errp) == FALSE) ERR_OUT(errp);		// apply data

	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Prefixed_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
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
		Dz1Asn1WipValue *wip = NULL;
		Dz1Asn1WipCst *wip_seq = NULL;
		Dz1Asn1Custom *wip_sto = NULL;

		Dz1Asn1BerDecoderStk *ret_stk = NULL;
		Dz1Asn1TypeDescrChild *child = NULL;
		Dz1Asn1TypeDescr *child_descr = NULL;
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			else if ((wip = dst->wip = Dz1Asn1WipValue_gen(errp)) == NULL) ERR_OUT(errp);	// critical
			else
			{
				dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			}
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL)				ERR_SET_OUT(errp, EFAULT);
			// resolve child & call decoder
			else if (descr->childs == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((child = stk->child = descr->childs) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{	// always nesting
				char str_prefix[64], str_origin[64], str_tag[64];
				Dz1Asn1TagOpt tag_opt = child->descr_tag;
				dst->u32data = (u32_t)tag_opt;
				child_descr = child->descr;

				Dz1Asn1TagA_printable(descr->tag, str_tag, sizeof(str_tag));
				Dz1Asn1UTF8StrA_printable(descr->name, str_prefix, 64, NULL);
				Dz1Asn1UTF8StrA_printable(child_descr->name, str_origin, 64, NULL);
				Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ PREFIXED : [%s] %s -> %s = %s nested\n", str_tag, str_prefix, str_origin, Dz1Asn1TagOptStrA(tag_opt));

				if (Dz1Asn1BerDecoder_stackPushChild(decoder, child_descr, tag_opt, tag, stk->len, errp) == FALSE) ERR_OUT(errp);
				else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
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
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ PREFIXED : receive EOC\n");
					if (dst->wip == NULL) ERR_SET_OUT(errp, EFAULT);
					else { dst->state = Dz1Asn1BerDecoderDataState_max; ret = Dz1Asn1BerLength_ssoc; }
				}
				else 
				{	// return DATA
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ PREFIXED : receive DATA(%s)\n", Dz1Asn1TagOptStrA((Dz1Asn1TagOpt)dst->u32data));

					if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if (_prefix_child_apply(stk->child, wip, ret_stk, dst, errp) == FALSE) ERR_OUT(errp);
					// in INDIRECT decoder, Here should be End of Encoding or expect EOC
					else if (_dec_indirect_post_proc(dst, stk, decoder, "PREFIXED", errp) == FALSE) ERR_OUT(errp);
					else ret = Dz1Asn1BerLength_ssoc;
				}
				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? ret : -1;
}
// Prefixed type Decoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Indirected Decoder
// Dz1Asn1BerDecoderDataCtx *dst, Dz1Asn1Stream *src, Dz1Asn1BerDecoderStk *stk, Dz1Asn1BerDecoder *decoder, Dz1Error *errp
ssize_t Dz1Asn1BerDecoderDataCtx_dec_indirect(Dz1Asn1BerDecoder_contentsDecArgs)
{	// called from SEQUENCE or SET??
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
		char str_tag[64], str_name[512];
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
			else if ((child = stk->child = Dz1Asn1TypeDescr_findChild(descr, tag, &dst->idx)) == NULL)
			{	// unknown child -> OpenType with IMPLICIT
				dst->idx = -1;

				child_descr = &dz1Asn1TypeDescrOpenType;
				Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, sizeof(str_name), NULL);

				if (tag->flag == Dz1Asn1TagFlag_primitive)
				{	// primitive form
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : Unknown Child = %s : %s : switched\n", Dz1Asn1TagA_printable(tag, str_tag, sizeof(str_tag)), str_name);

					stk->descr = child_descr;
					dst->state = Dz1Asn1BerDecoderDataState_initial;
					return child_descr->ber_dec(dst, src, stk, decoder, errp);
				}
				else
				{	// constructed form
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : Unknown Child = %s : %s : explicit nested\n", Dz1Asn1TagA_printable(tag, str_tag, sizeof(str_tag)), str_name);

					dst->u32data = (u32_t)Dz1Asn1TagOpt_explicit;
					if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, child_descr, errp) == FALSE) ERR_OUT(errp);
					else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
				}
			}
			else
			{	// known child -> Child Descriptor(and their Tag Mode)
				if ((child_descr = child->descr) == NULL)
				{
					Dz1Asn1BerDecoderStk *caller_stk = stk->next;
					Dz1Asn1BerDecoderCtx *caller_ctx = caller_stk->ctx;
					Dz1Asn1BerDecoderDataCtx *data_ctx = NULL;
					Dz1Asn1WipValue *parent_data = NULL;
					Dz1Asn1WipCst *cst_seq = NULL;
					Dz1Asn1Custom *storage = NULL;
					void *data = NULL;
					if (caller_ctx->present != Dz1Asn1BerDecoderCtxPresent_data) ERR_SET_OUT(errp, EFAULT);
					else if ((data_ctx = caller_ctx->x.data) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((parent_data = data_ctx->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
					else if ((cst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((storage = cst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((data =storage->data) == NULL) ERR_SET_OUT(errp, EFAULT);
					else child->get_child(data, &child_descr);
				}

				if (child_descr == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					Dz1Asn1UTF8StrA_printable(child_descr->name, str_name, sizeof(str_name), NULL);

					if (tag->flag == Dz1Asn1TagFlag_primitive)
					{	// primitive : don't care PREFIXED or not
						Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : Known Child = %s : %s : switched\n", Dz1Asn1TagA_printable(tag, str_tag, sizeof(str_tag)), str_name);

						stk->descr = child_descr;
						dst->state = Dz1Asn1BerDecoderDataState_initial;
						return child_descr->ber_dec(dst, src, stk, decoder, errp);
					}
					// constructed form
					else if (Dz1Asn1Tag_isVoid(&child->tag))
					{	// NON-PREFIXED -> implicit
						dst->u32data = (u32_t)Dz1Asn1TagOpt_implicit;
						Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : Known Child = %s : %s : implicit nested\n",
									   Dz1Asn1TagA_printable(tag, str_tag, sizeof(str_tag)), str_name);

						if (Dz1Asn1BerDecoder_stackPushImplicit(decoder, child_descr, tag, stk->len, errp) == FALSE) ERR_OUT(errp);
						else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
					}
					else 
					{	// PREFIXED [IMPLICIT | EXPLICIT] -> depend on child->descr_tag
						Dz1Asn1TagOpt tag_opt = child->descr_tag;
						dst->u32data = (u32_t)tag_opt;

						Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : Known Child = %s : %s : %s nested\n",
									   Dz1Asn1TagA_printable(tag, str_tag, sizeof(str_tag)), str_name, Dz1Asn1TagOptStrA(tag_opt));

						if (Dz1Asn1BerDecoder_stackPushChild(decoder, child_descr, tag_opt, tag, stk->len, errp) == FALSE) ERR_OUT(errp);
						else { dst->state = Dz1Asn1BerDecoderDataState_nested; ret = Dz1Asn1BerLength_ssoc; }
					}
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
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : receive EOC\n");
					if (dst->wip == NULL) ERR_SET_OUT(errp, EFAULT);
					else { dst->state = Dz1Asn1BerDecoderDataState_max; ret = Dz1Asn1BerLength_ssoc; }
				}
				else 
				{	// return DATA
					Dz1Thread_tlog(DZ1_THREAD_LOG_INDIRECT, stk->tab, "@@@ IND : receive DATA(%s)\n", Dz1Asn1TagOptStrA((Dz1Asn1TagOpt)dst->u32data));

					if (dst->wip != NULL) ERR_SET_OUT(errp, EFAULT);
					// applying source data to destination data
					else if ((dst->wip = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);	// toss data to parent
					else 
					{
						ret_stk->data = NULL;
						// in INDIRECT decoder, Here should be End of Encoding or expect EOC
						if (_dec_indirect_post_proc(dst, stk, decoder, "IND", errp) == FALSE) ERR_OUT(errp); else ret = Dz1Asn1BerLength_ssoc;
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
// Indirected Decoder
///////////////////////////////////////////////////////////////////////////////

