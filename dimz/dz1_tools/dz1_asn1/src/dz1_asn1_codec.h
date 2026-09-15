#ifndef DZ1_ASN1_CODEC_H_LOCAL
#define DZ1_ASN1_CODEC_H_LOCAL

#include "dz1_asn1_types.h"
#include <dz1_asn1_codec.h>

DZ1_CPPLINK_VAR u32_t dz1Asn1EncoderFragSize;

///////////////////////////////////////////////////////////////////////////////
// Foundational Stream Read handling
#define DZ1_ASN1_STREAM_ERROR_OR_DONE(_sz, _ep, _doneflag) \
do \
{ \
	if (_sz == 0) { Dz1Error_set(_ep, 0); _doneflag = TRUE; } \
	else if ((_ep)->code != EAGAIN) ERR_OUT(_ep); \
	else \
	{ \
		Dz1Error_set(_ep, 0); \
		_doneflag = TRUE; \
	} \
} while(0)
// Foundational Stream Read handling
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// dz1_asn1_codec_def_util

// dz1_asn1_codec_def_util
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK ssize_t	 Dz1Asn1_2sComplementPacking(u8_t *dst, size_t sz, s64_t v, Dz1Error *err);

#endif // DZ1_ASN1_CODEC_H_LOCAL
