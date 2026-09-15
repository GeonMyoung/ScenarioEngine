#include "dz1_asn1_codec_ber.h"

/*
8.2		Encoding of a boolean value
8.2.1	The encoding of a boolean value shall be primitive. The contents octets shall consist of a single octet.
8.2.2	If the boolean value is:
			FALSE
		the octet shall be zero.
		If the boolean value is
			TRUE
		the octet shall have any non-zero value, as a sender's option.

		If of type BOOLEAN, the value TRUE can be encoded as:
			Boolean	Length	Contents
			0x01	0x01	0xFF

11.1	Boolean values
		If the encoding represents the boolean value TRUE, its single contents octet shall have all eight bits set to one. (Contrast with 8.2.2.)
*/

bool_t Dz1Asn1Bool_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Bool *src = (Dz1Asn1Bool *)_src;

	u8_t v = *src ? 0xFF : 0x00;

	if (0) { }
	else if (_Dz1ElasticBuf_push(dst, &v, 1, errp) == FALSE) ERR_OUT(errp);
	else
	{
		*ret_is_constructed_form = FALSE;
		Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Bool_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0, sz;
	Dz1Asn1WipValue *wip = NULL;
	u8_t v = 0;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)	ERR_SET_OUT(errp, EPERM);		// boolean can't be constructed form
	else if (stk->len == Dz1Asn1BerLength_soc)			ERR_SET_OUT(errp, EPERM);		// primitive form length can't soc
	else
	{
		bool_t done = FALSE;
		while(errp->code == 0 && done == FALSE)
		{
			switch(dst->state)
			{
			case Dz1Asn1BerDecoderDataState_initial:
				if ((wip = dst->wip) == NULL && (wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_boolean, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
				else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
				// fall through
			case Dz1Asn1BerDecoderDataState_data_wait:
				if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);	// critical
//				else if ((sz = Dz1Stream_read1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else if ((sz = Dz1Asn1Stream_popOctet(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
				else
				{
					Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< BOOL : %02X\n", v);

					ret += sz;
					dst->u64data += sz;

					if (v != 0xFF && v != 0x00) Dz1Thread_tlog(DZ1_THREAD_LOG_MESSAGE, stk->tab, "!!! Boolean BER Data incorrect = %02X\n", v);

					wip->x.boolean = v ? TRUE : FALSE;

					if (dst->u64data <= stk->len)
					{
						if (dst->u64data == stk->len) dst->state = Dz1Asn1BerDecoderDataState_max;
						done = TRUE;
					}
					else ERR_SET_OUT(errp, EFAULT);
				}
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
		}
	}
	return errp->code == 0 ? ret : -1;
}

