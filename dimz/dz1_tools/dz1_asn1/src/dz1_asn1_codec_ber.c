#include "dz1_asn1_codec_ber.h"

u32_t dz1Asn1EncoderFragSize = 1000;


bool_t _get_encode_length(u64_t *ret_len, s64_t contents_sz, bool_t is_construct, Dz1Asn1BerEncoderOpt codec_opt, bool_t *need_eoc, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	ssize_t sz = 0;
	Dz1Error_set(errp, 0);

	(*ret_len) = 0;
	(*need_eoc) = FALSE;

	if (is_construct)
	{
		switch(codec_opt)
		{
		case Dz1Asn1BerEncoderOpt_cer:
			(*ret_len) = Dz1Asn1BerLength_soc; 
			(*need_eoc) = TRUE; 
			break;
		case Dz1Asn1BerEncoderOpt_der: 
//			if ((sz = Dz1ElasticBuf_getDataSize(contents, errp)) < 0) ERR_OUT(errp); 
//			else (*ret_len) = (u64_t)sz;
			(*ret_len) = contents_sz;
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	// simple form should has length
// 	else if ((sz = Dz1ElasticBuf_getDataSize(contents, errp)) < 0) ERR_OUT(errp); 
// 	else (*ret_len) = (u64_t)sz;
	else (*ret_len) = (u64_t)contents_sz;

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1BerEncoder_enc(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *src, Dz1Asn1TagOpt tag_opt, bool_t *__is_constructed, Dz1Asn1BerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *contents = NULL;
	bool_t _is_constructed, *is_constructed = __is_constructed ? __is_constructed : &_is_constructed;
	pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&contents);

	if (Dz1Asn1TypeDescr_chkConformance(descr, src, NULL) == FALSE)
	{
		char str_name[64];
		Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Conformance Violation [%s]\n", str_name);
		ERR_SET_OUT(errp, EPERM);
	}
	else if (Dz1Asn1Tag_isVoid(descr->tag) || tag_opt == Dz1Asn1TagOpt_implicit)
	{	// no own tag or implicit -> Data Only
		if (descr->ber_enc(dst, descr, src, is_constructed, param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	// EXPLICIT
	else if ((contents = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else if (descr->ber_enc(contents, descr, src, is_constructed, param, errp) == FALSE) ERR_OUT(errp);
	else
	{
		u64_t length = 0;
		ssize_t contents_sz = 0;
		bool_t encode_eoc = FALSE;
		u8_t eoc[] = { 0x00, 0x00 };

		if (0) { }
		else if (Dz1Asn1Tag_enc_BER(dst, descr->tag, *is_constructed, param, errp) < 0) ERR_OUT(errp);		// Tag

		else if ((contents_sz = Dz1ElasticBuf_getDataSize(contents, errp)) < 0) ERR_OUT(errp);
		else if (_get_encode_length(&length, contents_sz, *is_constructed, param->opt, &encode_eoc, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1BerLength_enc_BER(dst, length, param, errp) < 0) ERR_OUT(errp);							// Length

		else if (Dz1ElasticBuf_move(dst, contents, errp) == FALSE) ERR_OUT(errp);								// Contents

		else if (encode_eoc && _Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);		// EOC(Optional)
		else Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&contents);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
static bool_t _Dz1Asn1BerEncoder_retrive(Dz1Asn1BerEncoder *p, Dz1Asn1BerEncoderStk *stk, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (stk->next != NULL)
	{
		if (_Dz1Asn1BerEncoder_retrive(p, stk->next, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);

	if (errp->code == 0)
	{
		if (p->result == NULL)
		{
			p->result = stk->elb;
			stk->elb = NULL;
			Dz1Error_set(errp, 0);
		}
		else
		{
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&stk->elb);

			if (Dz1ElasticBuf_move(p->result, stk->elb, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&stk->elb);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Binary *Dz1Asn1BerEncoder_retrive(Dz1Asn1BerEncoder *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_Dz1Asn1BerEncoder_retrive(p, p->stk, errp) == FALSE) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&p->result);

		if ((ret = Dz1ElasticBuf_flattenAndPurge(p->result, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&p->result);
	}
	return ret;
}
*/

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoder
Dz1Asn1BerDecoder *Dz1Asn1BerDecoder_generate(Dz1Asn1TypeDescr *descr_ref, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1Asn1BerDecoder *decoder = Dz1Asn1BerDecoder_new(descr_ref, NULL, errp);
	if (decoder == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		Dz1Asn1BerDecoderStk *stk = NULL;
		pthread_cleanup_push(Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
		if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, descr_ref, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
	}
	return decoder;
}

static bool_t Dz1Asn1BerDecoder_stackPOP(Dz1Asn1BerDecoder *p, Dz1Asn1BerDecoderStk **node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->stk == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1Asn1BerDecoderStk *ret = (*node) = p->stk;
		p->stk = ret->next;
		ret->next = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#define _stackPUSH(decoder_p, stk_node_p)\
	do {\
		if ((decoder_p)->stk != NULL) (stk_node_p)->tab = (decoder_p)->stk->tab + 1;\
		(stk_node_p)->next = (decoder_p)->stk;\
		(decoder_p)->stk = (stk_node_p);\
		(stk_node_p) = NULL;\
	} while(0)\

bool_t Dz1Asn1BerDecoder_stackPushExplicit(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr_ref, Dz1Error *errp)
{
	if (p == NULL || descr_ref == NULL)
		ERR_SET_OUT(errp, EFAULT);
	else 
	{
		Dz1Asn1BerDecoderStk *node = NULL;
		if ((node = Dz1Asn1BerDecoderStk_new(descr_ref, Dz1Asn1TagOpt_explicit, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1BerDecoderCtx *ctx = NULL;
			pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&node);

			if ((ctx = node->ctx = Dz1Asn1BerDecoderCtx_new(Dz1Asn1BerDecoderCtxPresent_tag, NULL, errp)) == NULL) ERR_OUT(errp);			// start from TAG decoder
			else if ((ctx->x.tag = Dz1Asn1BerDecoderTagCtx_new(Dz1Asn1BerDecoderTagState_first_byte, NULL, errp)) == NULL) ERR_OUT(errp);	// prepare TAG decoder context
			else
			{
				_stackPUSH(p, node);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1BerDecoder_stackPushImplicit(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr_ref, Dz1Asn1Tag *caller_tag, u64_t caller_len, Dz1Error *errp)
{
	if (p == NULL || descr_ref == NULL || caller_tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else 
	{
		Dz1Asn1BerDecoderStk *node = NULL;
		if (caller_tag == NULL) ERR_SET_OUT(errp, EFAULT);																			// don't care about P/C flag
		else if ((node = Dz1Asn1BerDecoderStk_new(descr_ref, Dz1Asn1TagOpt_implicit, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1BerDecoderCtx *ctx = NULL;
			pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&node);

			if ((ctx = node->ctx = Dz1Asn1BerDecoderCtx_new(Dz1Asn1BerDecoderCtxPresent_data, NULL, errp)) == NULL) ERR_OUT(errp);	// start from CONTENTX OCTET decoder
			else if ((ctx->x.data = Dz1Asn1BerDecoderDataCtx_new(errp)) == NULL) ERR_OUT(errp);										// prepare CONTENTX OCTET decoder context

			else if ((node->tag = Dz1Asn1Tag_clone(caller_tag, errp)) == NULL) ERR_OUT(errp);									// parent tag is needed to CONTENTX OCTET decoder
			else
			{
				node->len = caller_len;																								// parent length is needed to CONTENTX OCTET decoder

				_stackPUSH(p, node);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1BerDecoder_stackPushChild(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr, Dz1Asn1TagOpt tag_opt, Dz1Asn1Tag *parent_tag, u64_t parent_len, Dz1Error *errp)
{
	if (p == NULL || descr == NULL || parent_tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else 
	{
		Dz1Asn1BerDecoderStk *node = NULL;
		switch(tag_opt)
		{
		case Dz1Asn1TagOpt_explicit:																									// member is EXPLICIT
			if (parent_tag->flag == Dz1Asn1TagFlag_primitive) ERR_SET_OUT(errp, EINVAL);												// parent context should have CONSTRUCT flag
			else if (Dz1Asn1BerDecoder_stackPushExplicit(p, descr, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1Asn1TagOpt_implicit:																									// member is IMPLICIT
			if (Dz1Asn1BerDecoder_stackPushImplicit(p, descr, parent_tag, parent_len, errp) == FALSE) ERR_OUT(errp);					// parent TAG & Length is my TAG & Length
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

////////////////////////////////////////
// TAG
ssize_t Dz1Asn1Tag_enc_BER(Dz1ElasticBuf *elb, Dz1Asn1Tag *tag, bool_t flag_is_construct, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (elb == NULL || tag == NULL)
		ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t front = (((u8_t)tag->cls & 0x3) << 6) | (u8_t)(flag_is_construct ? 0x20 : 0x00);

		char buf[64];
		Dz1Asn1Tag dump_tag = { tag->cls, flag_is_construct ? Dz1Asn1TagFlag_construct : Dz1Asn1TagFlag_primitive, tag->numb };
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "Dz1Asn1Tag_enc_BER() : %s\n", Dz1Asn1TagA_printable(&dump_tag, buf, sizeof(buf)));

		if (tag->numb < 31)
		{
			front |=  (u8_t)(tag->numb & 0x1F);
			if (_Dz1ElasticBuf_push(elb, &front, 1, errp) == FALSE) { ERR_OUT(errp); return -1; }
			else ret += 1;
		}
		else
		{
			u8_t buf[10] = { 0, }, v;
			u32_t cnt = 0, idx = 9, i;
			u64_t numb = tag->numb;
			front |= 0x1F;
			while((v = numb & 0x7F) != 0)
			{
				buf[idx] = v;
				numb >>= 7;

				if (numb) break;
				else idx--;
			}

			for (i = 0; idx < 10; i++, idx++) buf[i] = buf[idx];

			if (_Dz1ElasticBuf_push(elb, &front, 1, errp) == FALSE) { ERR_OUT(errp); return -1; } else ret += 1;
			if (_Dz1ElasticBuf_push(elb, buf, i, errp) == FALSE) { ERR_OUT(errp); return -1; } else ret += i;
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? ret : -1;
}

static ssize_t Dz1Asn1BerDecoderTagCtx_dec(Dz1Asn1BerDecoderTagCtx *dst, Dz1Asn1Stream *src, void *param, int tab, Dz1Error *errp)
{
	ssize_t ret = 0;
	Dz1Asn1Tag *tag = NULL;
	if ((tag = dst->wip) == NULL && (tag = dst->wip = Dz1Asn1Tag_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t v;
		ssize_t sz;
		bool_t done = FALSE;
		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, tab, "<<< TAG : ");
		while(done == FALSE && errp->code == 0)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderTagState_first_byte:
//				if ((sz = Dz1Stream_read1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);
					ret += sz;

					tag->cls = (Dz1Asn1TagClass)(v >> 6);
					tag->flag = (v & 0x20) ? Dz1Asn1TagFlag_construct : Dz1Asn1TagFlag_primitive;

					if ((v & 0x1F) < 0x1F)
					{	// complete tag number
						tag->numb = (u64_t)(v & 0x1F);
						dst->state = Dz1Asn1BerDecoderTagState_max;
						done = TRUE;
					}
					else dst->state = Dz1Asn1BerDecoderTagState_tag_nums;
				}
				break;
			case Dz1Asn1BerDecoderTagState_tag_nums:
//				if ((sz = Dz1Stream_read1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);
					ret += sz;

					tag->numb <<= 7;
					tag->numb += (v & 0x7F);

					if ((v & 0x80) == 0x00)
					{	// complete tag number
						dst->state = Dz1Asn1BerDecoderTagState_max;
						done = TRUE;
					}
				}
				break;
			default:
				ERR_SET_OUT(errp, EFAULT);
				break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}
// TAG
////////////////////////////////////////

////////////////////////////////////////
// LENGTH
ssize_t Dz1Asn1BerLength_enc_BER(Dz1ElasticBuf *elb, u64_t len, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	u8_t v = 0;
	if (len == Dz1Asn1BerLength_soc)
	{	// SOC
		v = 0x80;
		if (_Dz1ElasticBuf_push(elb, &v, 1, errp) == FALSE) ERR_OUT(errp); else ret += 1;
	}
	else if (len <= 0x7F)
	{	// short form
		v = (u8_t)(len & 0x7F);
		if (_Dz1ElasticBuf_push(elb, &v, 1, errp) == FALSE) ERR_OUT(errp); else ret += 1;
	}
	else
	{
		u8_t buf[8] = { 0, };
		u32_t sz = 8, cnt = 0;

		while((len & DZ1UINT64(0xFF80000000000000)) == 0) { len <<= 8; sz--; }
		while(sz)
		{
			buf[cnt++] = (u8_t)((len >> 56) & 0xFF);
			len <<= 8;
			sz--;
		}
		
		v = 0x80 | (u8_t)(cnt & 0x7F);
		if (_Dz1ElasticBuf_push(elb, &v, 1, errp) == FALSE) ERR_OUT(errp);
		else if (_Dz1ElasticBuf_push(elb, buf, cnt, errp) == FALSE) ERR_OUT(errp);
		else ret = 1 + cnt;
	}
	return errp->code == 0 ? ret : -1;
}

static ssize_t Dz1Asn1BerDecoderLengthCtx_dec(Dz1Asn1BerDecoderLengthCtx *dst, Dz1Asn1Stream *src, void *param, int tab, Dz1Error *errp)
{
	ssize_t ret = 0;
	ssize_t sz;
	u8_t v;
	bool_t done = FALSE;
	Dz1Error_set(errp, 0);
	Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, tab, "<<< LEN : ");
	while(errp->code == 0 && done == FALSE)
	{
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderLengthState_initial:
//			if ((sz = Dz1Stream_read1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
			if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);
				ret += sz;

				if ((v & 0x80) == 0x00)
				{	// single octet length
					dst->remain_bytes = 0;
					dst->wip = (u64_t)(v & 0x7F);					// 0 ~ 127
					dst->state = Dz1Asn1BerDecoderLengthState_max;
					done = TRUE;
				}
				// 0b1??? ????
				else if ((v & 0x7F) == 0x00)
				{	// SOC
					dst->wip = Dz1Asn1BerLength_soc;				// Maximum value of u64_t
					dst->state = Dz1Asn1BerDecoderLengthState_max;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
				else
				{
					dst->remain_bytes = (size_t)(v & 0x3F);
					dst->state = Dz1Asn1BerDecoderLengthState_data_wait;
				}
			}
			break;
		case Dz1Asn1BerDecoderLengthState_data_wait:
//			if ((sz = Dz1Stream_read1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
			if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", v);
				ret += sz;

				dst->wip = (dst->wip << 8) + v;
				dst->remain_bytes--;

				if (dst->remain_bytes == 0)
				{
					dst->state = Dz1Asn1BerDecoderLengthState_max;
					done = TRUE;
				}
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	return errp->code == 0 ? ret : -1;
}
// LENGTH
////////////////////////////////////////

ssize_t Dz1Asn1BerDecoderDataCtx_setEOC(Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->wip == NULL && (dst->wip = Dz1Asn1WipValue_gen(errp)) == NULL) ERR_OUT(errp);	// critical
	else
	{
		dst->state = Dz1Asn1BerDecoderDataState_max;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? Dz1Asn1BerLength_ssoc : -1;
}

ssize_t Dz1Asn1BerDecoder_dec(Dz1Asn1BerDecoder *p, Dz1Asn1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1Asn1BerDecoderStk *stk = NULL;
	if (p == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->ret != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		bool_t done = FALSE;
		Dz1Asn1TypeDescr *descr = NULL;
		Dz1Asn1BerDecoderCtx *ctx = NULL;
		while(done == FALSE && errp->code == 0)
		{
			if ((stk = p->stk) == NULL) ERR_OUT(errp);
			else if ((descr = stk->descr) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((ctx = stk->ctx) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ssize_t sz;
				Dz1Asn1BerDecoderTagCtx *ctx_tag = NULL;
				Dz1Asn1BerDecoderLengthCtx *ctx_len = NULL;
				Dz1Asn1BerDecoderDataCtx *ctx_data = NULL;
				Dz1Asn1BerDecoderStk *ret_stk = NULL;

//				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "stk->descr = %p\n", stk->descr);

				switch(ctx->present)
				{
				case Dz1Asn1BerDecoderCtxPresent_tag:
					if ((ctx_tag = ctx->x.tag) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((sz = Dz1Asn1BerDecoderTagCtx_dec(ctx_tag, src, param, stk->tab, errp)) < 0) ERR_OUT(errp);
					else
					{
						ret += sz;
						stk->consumed += sz;

						if (ctx_tag->state != Dz1Asn1BerDecoderTagState_max) done = TRUE; // we need more data
						else
						{	// complete tag
							Dz1Asn1Tag *descr_tag = NULL;
							Dz1Asn1Tag *stk_tag = stk->tag = ctx_tag->wip;
							ctx_tag->wip = NULL;

							// descr->tag == NULL : descr is CHOICE Descriptor
							if (0) { }
							/*
							else if (Dz1Asn1Tag_isEndOfContents(stk_tag) == FALSE &&			// not End of Contents
									 (descr_tag = descr->tag) != NULL &&						// descriptor has TAG
									 Dz1Asn1Tag_isCompatible(descr_tag, stk_tag) == FALSE)
							{
								char str_descr_tag[64], str_stk_tag[64];
								Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "Descriptor = %s : Income = %s\n", 
												Dz1Asn1TagA_printable(descr_tag, str_descr_tag, 64), 
												Dz1Asn1TagA_printable(stk_tag, str_stk_tag, 64));
								ERR_SET_OUT(errp, ENOENT);
							}
							*/
							else if ((ctx_len = Dz1Asn1BerDecoderLengthCtx_new(Dz1Asn1BerDecoderLengthState_initial, 0, 0, errp)) == NULL) ERR_OUT(errp);
							else
							{
								Dz1Asn1BerDecoderTagCtx_delAndSetNull(&ctx->x.tag);
								ctx->present = Dz1Asn1BerDecoderCtxPresent_len;
								ctx->x.len = ctx_len;
							}
						}
					}
//					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[T] stk->descr = %p\n", stk->descr);
					ctx_tag = NULL;
					break;
				case Dz1Asn1BerDecoderCtxPresent_len:
					if ((ctx_len = ctx->x.len) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((sz = Dz1Asn1BerDecoderLengthCtx_dec(ctx_len, src, param, stk->tab, errp)) < 0) ERR_OUT(errp);
					else
					{
						ret += sz;
						stk->consumed += sz;

						if (ctx_len->state != Dz1Asn1BerDecoderLengthState_max) done = TRUE;	// we need more data
						else
						{	// complete length;
							stk->len = ctx_len->wip;
							ctx_len->wip = 0;

							if (0) { }
#if 1
							else if (Dz1Asn1Tag_isEndOfContents(stk->tag) && stk->len == 0)
							{
								Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "Dz1Asn1BerDecoder_dec() : End of Contents\n");
								if ((stk->data = Dz1Asn1WipValue_gen(errp)) == NULL) ERR_OUT(errp);
								else if (Dz1Asn1BerDecoder_stackPOP(p, &ret_stk, errp) == FALSE) ERR_OUT(errp);	// isolate current stack
								else
								{
									pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&ret_stk);
									if ((stk = p->stk) == NULL)													// get caller stack
									{	// top of stack -> finalize
										p->ret = ret_stk->data;
										ret_stk->data = NULL;
										done = TRUE;
									}
									// attach to caller stack as return
									else
									{
//										Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[0] stk->descr = %p\n", stk->descr);
										stk->ret_stk = ret_stk;
										ret_stk = NULL;
									}

									pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&ret_stk);
								}
							}
#endif
							else if ((ctx_data = Dz1Asn1BerDecoderDataCtx_new(errp)) == NULL) ERR_OUT(errp);
							else
							{
								Dz1Asn1BerDecoderLengthCtx_delAndSetNull(&ctx->x.len);
								ctx->present = Dz1Asn1BerDecoderCtxPresent_data;
								ctx->x.data = ctx_data;
							}
						}
					}
//					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[L] stk->descr = %p\n", stk->descr);
					ctx_len = NULL;
					break;
				case Dz1Asn1BerDecoderCtxPresent_data:
					if ((ctx_data = ctx->x.data) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((sz = descr->ber_dec(ctx_data, src, stk, p, errp)) <= 0)
					{
						DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
						if (errp->code)
						{
							Dz1Thread_printf(Dz1T("Stack = ")); Dz1Asn1BerDecoderStk_dump(stk, 0);
						}
					}
					else
					{
						if (sz == Dz1Asn1BerLength_ssoc) sz = 0;

						ret += sz;
						stk->consumed += sz;

						switch(ctx_data->state)
						{
						case Dz1Asn1BerDecoderDataState_nested:
							// data decoder call sub-decoder
							break;
						case Dz1Asn1BerDecoderDataState_max:
							// complete data decoding
							stk->data = ctx_data->wip;
							ctx_data->wip = NULL;	

							if (0) { }
							else if (Dz1Asn1BerDecoder_stackPOP(p, &ret_stk, errp) == FALSE) ERR_OUT(errp);	// isolate current stack
							else
							{
								pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&ret_stk);
								if ((stk = p->stk) == NULL)													// get caller stack
								{	// top of stack -> finalize
									p->ret = ret_stk->data;
									ret_stk->data = NULL;
									done = TRUE;
								}
								// attach to caller stack as return
								else
								{ 
	//								Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[1] stk->descr = %p\n", stk->descr);
									stk->ret_stk = ret_stk; 
									ret_stk = NULL;
								}

								pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&ret_stk);
							}
							break;
						default: // we need more data
							done = TRUE;
							break;
						}
					}
					break;
				default: ERR_SET_OUT(errp, EFAULT); break;
				}
			}
		}
	}
	return errp->code == 0 ? ret : -1;
}

void *Dz1Asn1BerDecoder_retrive(Dz1Asn1BerDecoder *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1TypeDescr *descr = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;
	void *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->ret == NULL)
	{
		Dz1Thread_printf(Dz1T("Stack = ")); Dz1Asn1BerDecoderStk_dump(p->stk, 0);
		Dz1Error_set(errp, EAGAIN);
	}
	else if ((descr = p->target) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((user_api = descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(user_api->delAndSetNull, (void *)&ret);

		if (descr->finalize(ret, p->ret, descr, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (user_api->delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1Asn1BerDecoder
///////////////////////////////////////////////////////////////////////////////
