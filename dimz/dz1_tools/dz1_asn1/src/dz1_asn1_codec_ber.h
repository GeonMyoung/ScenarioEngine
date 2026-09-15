#ifndef DZ1_ASN1_CODEC_BER_H_LOCAL
#define DZ1_ASN1_CODEC_BER_H_LOCAL

#include <dz1_asn1_codec_ber.h>

#include "dz1_asn1_constraint.h"
#include "dz1_asn1_typedescr.h"
#include "dz1_asn1_codec.h"

///////////////////////////////////////////////////////////////////////////////
// TAG Macros
#define Dz1Asn1TagVarName(type_name)		berTag##type_name
#define Dz1Asn1TagVarDeclare(type_name)		Dz1Asn1Tag Dz1Asn1TagVarName(type_name) = BerTagValue##type_name
// TAG Macros
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Length Macros
#define Dz1Asn1BerLength_soc				DZ1UINT64(0xFFFFFFFFFFFFFFFF)
#define Dz1Asn1BerLength_ssoc				DZ1UINT64(0x7FFFFFFF)
// Length Macros
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// dz1_asn1_ber
DZ1_CPPLINK bool_t _get_encode_length(u64_t *ret_len, s64_t contents_sz, bool_t is_construct, Dz1Asn1BerEncoderOpt codec_opt, bool_t *need_eoc, Dz1Error *err);

///////////////////////////////////////
// Decoder Stack
//DZ1_CPPLINK bool_t					 Dz1Asn1BerEncoder_pushStack(Dz1Asn1BerEncoder *encoder, Dz1Asn1TypeDescrChild *child, Dz1Asn1BerEncoderOpt codec_opt, Dz1Error *err);
//DZ1_CPPLINK Dz1Asn1BerEncoderStk	*Dz1Asn1BerEncoder_popStack(Dz1Asn1BerEncoder *p, Dz1Error *err);
// Decoder Stack
///////////////////////////////////////

///////////////////////////////////////
// Encoder Stack
DZ1_CPPLINK bool_t	 Dz1Asn1BerDecoder_stackPushExplicit(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr_ref, Dz1Error *errp);
DZ1_CPPLINK bool_t	 Dz1Asn1BerDecoder_stackPushImplicit(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr_ref, Dz1Asn1Tag *caller_tag, u64_t caller_len, Dz1Error *errp);
DZ1_CPPLINK bool_t	 Dz1Asn1BerDecoder_stackPushChild(Dz1Asn1BerDecoder *p, Dz1Asn1TypeDescr *descr, Dz1Asn1TagOpt tag_opt, Dz1Asn1Tag *context_tag, u64_t context_len, Dz1Error *errp);
// Encoder Stack
///////////////////////////////////////


DZ1_CPPLINK ssize_t	 Dz1Asn1Tag_enc_BER(Dz1ElasticBuf *elb, Dz1Asn1Tag *tag, bool_t flag_is_construct, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t	 Dz1Asn1BerLength_enc_BER(Dz1ElasticBuf *elb, u64_t len, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t	 Dz1Asn1BerDecoderDataCtx_setEOC(Dz1Asn1BerDecoderDataCtx *dst, Dz1Error *err);
// dz1_asn1_ber
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderDataCtx
DZ1_CPPLINK Dz1ElasticBuf	*_get_child_contents(Dz1Asn1TypeDescr *descr, void *src, bool_t *ret_is_constructed_form, Dz1Asn1BerEncoderArg *param, Dz1Error *errp);
DZ1_CPPLINK Dz1ElasticBuf	*_get_child_tag_length(Dz1Asn1TypeDescr *descr, bool_t is_constructed, Dz1ElasticBuf *data, bool_t *ret_encode_eoc, Dz1Asn1BerEncoderArg *param, Dz1Error *errp);;
DZ1_CPPLINK bool_t			 _encode_tag_length(Dz1ElasticBuf *dst, Dz1Asn1Tag *tag, bool_t is_constructed, ssize_t child_sz, bool_t *ret_my_eoc, Dz1Asn1BerEncoderArg *param, Dz1Error *errp);

DZ1_CPPLINK bool_t	 Dz1Asn1BerDecoderDataCtx_enc_child(Dz1ElasticBuf *dst, Dz1Asn1TypeDescrChild *child, Dz1Asn1TypeDescr *c_descr,  void *src, Dz1Asn1Tag *tag_alt, bool_t *ret_is_complete_form, Dz1Asn1BerEncoderArg *param, Dz1Error *errp);
DZ1_CPPLINK ssize_t	 Dz1Asn1BerDecoderDataCtx_dec_indirect(Dz1Asn1BerDecoder_contentsDecArgs);
// Dz1Asn1BerDecoderDataCtx
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK bool_t Dz1Asn1BerDecoderDataCtx_enc_EOC(Dz1Asn1BerEncoder_contentsEncArgs);
DZ1_CPPLINK ssize_t Dz1Asn1BerDecoderDataCtx_dec_EOC(Dz1Asn1BerDecoder_contentsDecArgs);

#endif
