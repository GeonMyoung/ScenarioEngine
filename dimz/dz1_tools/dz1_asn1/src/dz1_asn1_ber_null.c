#include "dz1_asn1_codec_ber.h"

/*
8.8		Encoding of a null value
8.8.1	The encoding of a null value shall be primitive.
8.8.2	The contents octets shall not contain any octets.
		NOTE - The length octet is zero.
*/
//Dz1Asn1BerEncoder_contentsEncArgs
bool_t Dz1Asn1Null_enc_BER(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Null *src = (Dz1Asn1Null *)_src;

	if (ret_is_constructed_form) *ret_is_constructed_form = FALSE;
	// nothing to encode

	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1Null_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1Tag *tag = stk->tag;

	Dz1Error_set(errp, 0);

	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else if (tag->flag != Dz1Asn1TagFlag_primitive)	ERR_SET_OUT(errp, EPERM);	// don't use constructed encoding
	else if (stk->len != 0)								ERR_SET_OUT(errp, EPERM);	// don't be indefinite or positive size
	else
	{
		Dz1Asn1WipValue *wip = NULL;
		Dz1Error_set(errp, 0);
		switch(dst->state)
		{
		case Dz1Asn1BerDecoderDataState_initial:
			if ((dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_nul, NULL, errp)) == NULL) ERR_OUT(errp);
			else dst->state = Dz1Asn1BerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				wip->x.nul = 0;
				dst->state = Dz1Asn1BerDecoderDataState_max;
				ret = Dz1Asn1BerLength_ssoc;
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? ret : -1;
}

///////////////////////////////////////////////////////////////////////////////
// EOC
bool_t Dz1Asn1BerDecoderDataCtx_enc_EOC(Dz1Asn1BerEncoder_contentsEncArgs)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Null *src = (Dz1Asn1Null *)_src;

	u8_t eoc[] = { 0x00, 0x00 };
	if (_Dz1ElasticBuf_push(dst, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1BerDecoderDataCtx_dec_EOC(Dz1Asn1BerDecoder_contentsDecArgs)
{
	ssize_t ret = 0;
	Dz1Asn1Tag *tag = stk->tag;
	Dz1Error_set(errp, 0);
	if (tag == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1Tag_isEndOfContents(tag))
	{	// End-of-Contents (length is 0)
		if ((ret = Dz1Asn1BerDecoderDataCtx_setEOC(dst, errp)) < 0) ERR_OUT(errp);
	}
	else ERR_SET_OUT(errp, EPERM);
	return errp->code == 0 ? ret : -1;
}

// EOC
///////////////////////////////////////////////////////////////////////////////
