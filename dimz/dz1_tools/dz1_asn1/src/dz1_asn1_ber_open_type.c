#include "dz1_asn1_codec_ber.h"

/*
8.15	Encoding of an open type
		The value of an open type is also a value of some (other) ASN.1 type. The encoding of such a value shall be 
		the complete encoding herein specified for the value considered as being of that other type.
		OpenType의 값은 또한 일부(기타) ASN.1 유형의 값입니다. 그러한 값의 인코딩은 다른 유형의 것으로 간주되는 
		값에 대해 여기에 지정된 완전한 인코딩이어야 합니다.
*/
// Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err
bool_t Dz1Asn1Any_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OctetStr *src = (Dz1Asn1OctetStr *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_Dz1ElasticBuf_push(dst, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		*ret_is_constructed_form = TRUE;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// Dz1Asn1BerDecoderDataCtx *dst, Dz1Asn1Stream *src, Dz1Asn1BerDecoderStk *stk, Dz1Asn1BerDecoder *decoder, void *param, Dz1Error *errp
ssize_t Dz1Asn1Any_dec_BER(Dz1Asn1BerDecoderDataCtx *dst, Dz1Asn1Stream *src, Dz1Asn1BerDecoderStk *stk, Dz1Asn1BerDecoder *decoder, Dz1Error *errp)
{
	ssize_t ret = 0;
	Dz1Asn1WipValue *wip = NULL;
	Dz1Asn1WipOpenType *any = NULL;
	Dz1Asn1WipOpenData *contents = NULL;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag == Dz1Asn1TagFlag_construct)
	{
		Dz1Asn1BerDecoderStk *ret_stk = NULL;

		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if (0) { }
			// initialize destination data struct
			else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_any, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((any = wip->x.any = Dz1Asn1WipOpenType_new(tag->cls, tag->numb, stk->len, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((any->contents = contents = Dz1Asn1WipOpenData_new(Dz1Asn1WipOpenDataPresent_construct, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((contents->x.construct = Dz1Asn1WipOpenTypeList_new(errp)) == NULL) ERR_OUT(errp);
			else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if (0) { }
			// resolve destination data struct
			else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((any = wip->x.any) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((contents = any->contents) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (contents->x.construct == NULL) ERR_SET_OUT(errp, EFAULT);
			// all struct ready
			else if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrOpenType, errp) == FALSE) ERR_OUT(errp);
			else
			{
				dst->state = Dz1Asn1BerDecoderDataState_nested;
				ret = Dz1Asn1BerLength_ssoc;
			}
			break;
		case Dz1Asn1BerDecoderDataState_nested:
			if ((ret_stk = stk->ret_stk) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Dz1Asn1WipValue *ret_data = NULL;

				Dz1Asn1WipOpenTypeList *construct = NULL;
				pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);

				dst->u64data += ret_stk->consumed;
				stk->consumed += ret_stk->consumed;

				if ((ret_data = ret_stk->data) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (ret_data->present == Dz1Asn1WipValuePresent_max)
				{
					dst->state = Dz1Asn1BerDecoderDataState_max;	// return EOC -> End of Constructed Decoding
					ret = Dz1Asn1BerLength_ssoc;
				}
				else if (ret_data->present != Dz1Asn1WipValuePresent_any) ERR_SET_OUT(errp, EFAULT);
				// resolve source data struct
				else if (ret_data->x.any == NULL) ERR_SET_OUT(errp, EFAULT);
				// resolve destination data struct
				else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((any = wip->x.any) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((contents = any->contents) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((construct = contents->x.construct) == NULL) ERR_SET_OUT(errp, EFAULT);
				// applying source data to destination data
				else if (Dz1Asn1WipOpenTypeList_addOpenType(construct, &ret_data->x.any, errp) == FALSE) ERR_OUT(errp);
				else if (stk->len == Dz1Asn1BerLength_soc || dst->u64data < stk->len)
				{
					if (Dz1Asn1BerDecoder_stackPushExplicit(decoder, &dz1Asn1TypeDescrOpenType, errp) == FALSE) ERR_OUT(errp);
					else ret = Dz1Asn1BerLength_ssoc;
				}
				else if (dst->u64data == stk->len)
				{
					dst->state = Dz1Asn1BerDecoderDataState_max;
					ret = Dz1Asn1BerLength_ssoc;
				}
				else ERR_SET_OUT(errp, EFAULT); // size fault

				pthread_cleanup_pop(1); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&stk->ret_stk);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive) ERR_SET_OUT(errp, EFAULT);
	else if (stk->len == Dz1Asn1BerLength_soc) ERR_SET_OUT(errp, EPERM);	// length of primitive form can't be SOC
	else
	{
		ssize_t sz = 0;
		bool_t done = FALSE;

		u8_t buf[1024] = { 0, };
		Dz1ElasticBuf *elb = NULL;
		u32_t copy_sz = 0;
		Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< ANY : ");
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if (0) { }
				// initialize destination data struct
				else if ((wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_any, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((any = wip->x.any = Dz1Asn1WipOpenType_new(tag->cls, tag->numb, stk->len, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((contents = any->contents = Dz1Asn1WipOpenData_new(Dz1Asn1WipOpenDataPresent_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((elb = contents->x.primitive = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
				else
				{
					dst->u32data = 0;
					dst->s32data = (s32_t)(stk->len & 0x7FFFFFFF);
					dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				}
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
// 				if (stk->len == 0)
// 				{
// 					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[E]");
// 					dst->state = Dz1Asn1BerDecoderDataState_max;
// 					ret = Dz1Asn1BerLength_ssoc;
// 					done = TRUE;
// 				}
// 				else
				{
					copy_sz = (dst->s32data > sizeof(buf)) ? sizeof(buf) : (u32_t)dst->s32data;
					if (0) { }
					// resolve destination data struct
					else if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((any = wip->x.any) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((contents = any->contents) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((elb = contents->x.primitive) == NULL) ERR_SET_OUT(errp, EFAULT);
					// read from STREAM
					else if (copy_sz > 0 && (sz = Dz1Asn1Stream_popOctets(src, buf, copy_sz, errp)) <= 0)
						DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
					// apply buffer to destination data struct
					else if (_Dz1ElasticBuf_push(elb, buf, (size_t)sz, errp) == FALSE) ERR_OUT(errp);
					else
					{
						u32_t log_lv = 0;
						Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
						if (log_lv & DZ1_THREAD_LOG_DEBUG)
						{
							ssize_t i;
							for (i = 0; i < sz; i++) Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "%02X ", buf[i]);
						}

						ret += sz;
						dst->u64data += sz;

						dst->s32data -= sz;
						dst->u32data += sz;

						if (dst->u32data == stk->len)
						{
							Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "[E]");
							dst->state = Dz1Asn1BerDecoderDataState_max;
							if (copy_sz == 0)
								ret = Dz1Asn1BerLength_ssoc;
							done = TRUE;
						}
						else if (dst->u32data > stk->len) ERR_SET_OUT(errp, EFAULT); // size fault
					}
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "\n");
	}
	return errp->code == 0 ? ret : -1;
}

