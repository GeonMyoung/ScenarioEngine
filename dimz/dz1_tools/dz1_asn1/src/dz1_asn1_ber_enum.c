#include "dz1_asn1_codec_ber.h"

/*
8.4		Encoding of an enumerated value
		The encoding of an enumerated value shall be that of the integer value with which it is associated.
		ENUMERATED 값의 인코딩은 연관된 정수 값의 인코딩입니다.
		NOTE -	It is primitive
				프리미티브 인코딩
*/
bool_t Dz1Asn1Enum_enc_BER(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *_src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	tag_Dz1Asn1Enum en_temp = *(tag_Dz1Asn1Enum *)_src;
	Dz1Asn1Int int_temp = (Dz1Asn1Int)en_temp;
	return Dz1Asn1Int_enc_BER(dst, descr, &int_temp, ret_is_constructed_form, param, errp);
}


