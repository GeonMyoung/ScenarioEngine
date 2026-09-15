#include "dz1_asn1_codec_per.h"

/*
12			Encoding the boolean type
12.1		A value of the boolean type shall be as a bit-field consisting of a single bit.
12.2		The bit shall be set to 1 for TRUE and 0 for FALSE.
12.3		The bit-field shall be appended to the field-list with no length determinant
			-> 길이 결정자를 가지지 않는 1개의 single bit로 인코딩 : 1 = TRUE, 0 = FALSE
*/


//bool_t Dz1Asn1Bool_enc_PER(Dz1Asn1PerEncoder_contentsEncArgs) // Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, void *_src, Dz1Asn1PerEncoderArg *param, Dz1Error *err
bool_t Dz1Asn1Bool_enc_PER(Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, void *_src, Dz1Asn1PerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Bool *src = (Dz1Asn1Bool *)_src;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		bool_t v = *src ? TRUE : FALSE;
		if (Dz1Asn1Stream_pushBit1(dst, v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

// Dz1Asn1PerDecoderDataCtx *dst, Dz1Asn1Stream *src, Dz1Asn1PerDecoderStk *stk, Dz1Asn1PerDecoder *decoder, Dz1Error *errp
ssize_t Dz1Asn1Bool_dec_PER(Dz1Asn1PerDecoder_contentsDecArgs)
{
	ssize_t ret = 0, sz;
	Dz1Asn1WipValue *wip = NULL;
	bool_t v = FALSE;

	Dz1Error_set(errp, 0);

	bool_t done = FALSE;
	while(errp->code == 0 && done == FALSE)
	{
		switch(dst->state)
		{
		case Dz1Asn1PerDecoderDataState_initial:
			if ((wip = dst->wip) == NULL && (wip = dst->wip = Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_boolean, NULL, errp)) == NULL) ERR_OUT(errp);	// critical
			else dst->state = Dz1Asn1PerDecoderDataState_data_wait;
			// fall through
		case Dz1Asn1BerDecoderDataState_data_wait:
			if ((wip = dst->wip) == NULL) ERR_SET_OUT(errp, EFAULT);	// critical
			else if ((sz = Dz1Asn1Stream_popBit1(src, &v, errp)) <= 0) DZ1_ASN1_STREAM_ERROR_OR_DONE(sz, errp, done);
			else
			{
				Dz1Thread_tlog(DZ1_THREAD_LOG_DEBUG, stk->tab, "<<< BOOL : %02X\n", v);

				ret += sz;
				dst->u64data += sz;

				wip->x.boolean = v;

				dst->state = Dz1Asn1BerDecoderDataState_max;
				done = TRUE;
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return errp->code == 0 ? ret : -1;
}
