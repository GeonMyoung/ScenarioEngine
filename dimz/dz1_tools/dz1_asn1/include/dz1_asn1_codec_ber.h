#ifndef DZ1_ASN1_CODEC_BER_H
#define DZ1_ASN1_CODEC_BER_H

#include <dz1_asn1_typedescr_def.h>
#include <dz1_asn1_codec_ber_def.h>

///////////////////////////////////////////////////////////////////////////////
// BER Encoder - Parameter & Arguments
#define				 Dz1Asn1BerEncoder_contentsEncArgs \
						Dz1ElasticBuf *dst, \
						Dz1Asn1TypeDescr *descr, void *_src, \
						bool_t *ret_is_constructed_form, \
						Dz1Asn1BerEncoderArg *param, Dz1Error *err

#define				 Dz1Asn1BerEncoder_contentsEncParams	dst, descr, _src, ret_is_constructed_form, param, errp
// BER Encoder - Parameter & Arguments
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BER Decoder - Parameter & Arguments
#define				 Dz1Asn1BerDecoder_contentsDecArgs\
						Dz1Asn1BerDecoderDataCtx *dst, \
						Dz1Asn1Stream *src, Dz1Asn1BerDecoderStk *stk, \
						Dz1Asn1BerDecoder *decoder, Dz1Error *errp

#define				 Dz1Asn1BerDecoderDataCtx_dec_params	dst, src, stk, decoder, errp
// BER Decoder - Parameter & Arguments
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoder
DZ1_CPPLINK Dz1Asn1BerDecoder	*Dz1Asn1BerDecoder_generate(Dz1Asn1TypeDescr *descr_ref, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1Asn1BerDecoder_dec(Dz1Asn1BerDecoder *p, Dz1Asn1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK void				*Dz1Asn1BerDecoder_retrive(Dz1Asn1BerDecoder *p, Dz1Error *err);
// Dz1Asn1BerDecoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoder
DZ1_CPPLINK bool_t	Dz1Asn1BerEncoder_enc(Dz1ElasticBuf *dst, Dz1Asn1TypeDescr *descr, void *src, Dz1Asn1TagOpt tag_opt, bool_t *is_constructed, Dz1Asn1BerEncoderArg *param, Dz1Error *err);
// Dz1Asn1BerEncoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Special Type
DZ1_CPPLINK bool_t	Dz1Asn1Prefixed_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);
DZ1_CPPLINK ssize_t	Dz1Asn1Prefixed_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1PrimitiveStr_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);
DZ1_CPPLINK ssize_t	Dz1Asn1PrimitiveStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1Any_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);
DZ1_CPPLINK ssize_t	Dz1Asn1Any_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK ssize_t	Dz1Asn1Choice_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);
DZ1_CPPLINK ssize_t	Dz1Asn1Choice_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);
// Special Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Type
DZ1_CPPLINK bool_t	Dz1Asn1Bool_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 1
DZ1_CPPLINK ssize_t	Dz1Asn1Bool_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1Int_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 2
DZ1_CPPLINK ssize_t	Dz1Asn1Int_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1BitStr_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);		// 3
DZ1_CPPLINK ssize_t	Dz1Asn1BitStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1OctetStr_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);		// 4
DZ1_CPPLINK ssize_t	Dz1Asn1OctetStr_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1Null_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 5
DZ1_CPPLINK ssize_t	Dz1Asn1Null_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1OID_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 6
DZ1_CPPLINK ssize_t	Dz1Asn1OID_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

#define				Dz1Asn1ObjDescr_enc_BER			Dz1Asn1OctetStr_enc_BER			// 7
#define				Dz1Asn1ObjDescr_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1External_enc_BER			Dz1Asn1Sequence_enc_BER			// 8
#define				Dz1Asn1External_dec_BER			Dz1Asn1Sequence_dec_BER
#define				Dz1Asn1InstanceOf_enc_BER		Dz1Asn1Sequence_enc_BER
#define				Dz1Asn1InstanceOf_dec_BER		Dz1Asn1Sequence_dec_BER

DZ1_CPPLINK bool_t	Dz1Asn1Real_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 9
DZ1_CPPLINK ssize_t	Dz1Asn1Real_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1Enum_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 10
#define				Dz1Asn1Enum_dec_BER				Dz1Asn1Int_dec_BER

#define				Dz1Asn1EmbPdv_enc_BER			Dz1Asn1Sequence_enc_BER			// 11
#define				Dz1Asn1EmbPdv_dec_BER			Dz1Asn1Sequence_dec_BER

#define				Dz1Asn1UTF8Str_enc_BER			Dz1Asn1OctetStr_enc_BER			// 12
#define				Dz1Asn1UTF8Str_dec_BER			Dz1Asn1OctetStr_dec_BER

DZ1_CPPLINK bool_t	Dz1Asn1RelOID_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);		// 13
DZ1_CPPLINK ssize_t	Dz1Asn1RelOID_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

#define				Dz1Asn1Time_enc_BER				Dz1Asn1PrimitiveStr_enc_BER		// 14
#define				Dz1Asn1Time_dec_BER				Dz1Asn1PrimitiveStr_dec_BER
																					// 15 : Reserved
DZ1_CPPLINK bool_t	Dz1Asn1Sequence_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);		// 16 : Sequence
DZ1_CPPLINK ssize_t	Dz1Asn1Sequence_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);
DZ1_CPPLINK bool_t	Dz1Asn1SequenceOf_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);	// 16 : Sequence-Of
DZ1_CPPLINK ssize_t	Dz1Asn1SequenceOf_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

DZ1_CPPLINK bool_t	Dz1Asn1Set_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);			// 17 : Set
DZ1_CPPLINK ssize_t	Dz1Asn1Set_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);
DZ1_CPPLINK bool_t	Dz1Asn1SetOf_enc_BER(Dz1Asn1BerEncoder_contentsEncArgs);		// 17 : Set-Of
DZ1_CPPLINK ssize_t	Dz1Asn1SetOf_dec_BER(Dz1Asn1BerDecoder_contentsDecArgs);

#define				Dz1Asn1DigitStr_enc_BER			Dz1Asn1OctetStr_enc_BER			// 18
#define				Dz1Asn1DigitStr_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1PrintStr_enc_BER			Dz1Asn1OctetStr_enc_BER			// 19
#define				Dz1Asn1PrintStr_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1TeletexStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 20
#define				Dz1Asn1TeletexStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1VideotexStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 21
#define				Dz1Asn1VideotexStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1IA5Str_enc_BER			Dz1Asn1OctetStr_enc_BER			// 22
#define				Dz1Asn1IA5Str_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1UTCTime_enc_BER			Dz1Asn1OctetStr_enc_BER			// 23
#define				Dz1Asn1UTCTime_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1GeneralTime_enc_BER		Dz1Asn1OctetStr_enc_BER			// 24
#define				Dz1Asn1GeneralTime_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1GraphicStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 25
#define				Dz1Asn1GraphicStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1VisibleStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 26
#define				Dz1Asn1VisibleStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1GeneralStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 27
#define				Dz1Asn1GeneralStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1UniversalStr_enc_BER		Dz1Asn1OctetStr_enc_BER			// 28
#define				Dz1Asn1UniversalStr_dec_BER		Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1CharStr_enc_BER			Dz1Asn1Sequence_enc_BER			// 29
#define				Dz1Asn1CharStr_dec_BER			Dz1Asn1Sequence_dec_BER

#define				Dz1Asn1BMPStr_enc_BER			Dz1Asn1OctetStr_enc_BER			// 30
#define				Dz1Asn1BMPStr_dec_BER			Dz1Asn1OctetStr_dec_BER

#define				Dz1Asn1Date_enc_BER				Dz1Asn1PrimitiveStr_enc_BER		// 31
#define				Dz1Asn1Date_dec_BER				Dz1Asn1PrimitiveStr_dec_BER

#define				Dz1Asn1TimeOfDay_enc_BER		Dz1Asn1PrimitiveStr_enc_BER		// 32
#define				Dz1Asn1TimeOfDay_dec_BER		Dz1Asn1PrimitiveStr_dec_BER

#define				Dz1Asn1DateTime_enc_BER			Dz1Asn1PrimitiveStr_enc_BER		// 33
#define				Dz1Asn1DateTime_dec_BER			Dz1Asn1PrimitiveStr_dec_BER

#define				Dz1Asn1Duration_enc_BER			Dz1Asn1PrimitiveStr_enc_BER		// 34
#define				Dz1Asn1Duration_dec_BER			Dz1Asn1PrimitiveStr_dec_BER
// ASN.1 Type
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK Dz1Asn1Any		*Dz1Asn1Any_newFromBER(Dz1Asn1TypeDescr *descr, void *ptr, Dz1Error *err);
DZ1_CPPLINK bool_t			 Dz1Asn1Any_BER_initFromWIP(Dz1Asn1Any *dst, Dz1Asn1WipOpenType *src, Dz1Error *err);

#endif
