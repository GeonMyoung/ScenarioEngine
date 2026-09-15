#ifndef DZ1_ASN1_CODEC_PER_H
#define DZ1_ASN1_CODEC_PER_H

#include <dz1_asn1_codec_stream.h>
#include <dz1_asn1_typedescr.h>
#include <dz1_asn1_codec_per_def.h>

///////////////////////////////////////////////////////////////////////////////
// PER Encoder - Parameter & Arguments
#define				 Dz1Asn1PerEncoder_contentsEncArgs \
						Dz1Asn1Stream *dst, Dz1Asn1TypeDescr *descr, void *_src, Dz1Asn1PerEncoderArg *param, Dz1Error *err
#define				 Dz1Asn1PerEncoder_contentsEncParams\
						dst, descr, _src, param, errp
// PER Encoder - Parameter & Arguments
///////////////////////////////////////////////////////////////////////////////

#define				 Dz1Asn1PerDecoder_contentsDecArgs\
						Dz1Asn1PerDecoderDataCtx *dst, \
						Dz1Asn1Stream *src, Dz1Asn1PerDecoderStk *stk, \
						Dz1Asn1PerDecoder *decoder, Dz1Error *errp

#endif
