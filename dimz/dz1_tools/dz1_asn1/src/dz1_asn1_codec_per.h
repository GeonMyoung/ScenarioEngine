#ifndef DZ1_ASN1_CODEC_PER_H_LOCAL
#define DZ1_ASN1_CODEC_PER_H_LOCAL

#include "dz1_asn1_codec.h"
#include <dz1_asn1_codec_per.h>

DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_2cbi(u64_t *dst, u64_t src, Dz1Error *err);						// return bits size
DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_nnbi(u64_t *dst, u64_t src, bool_t mode_bits, Dz1Error *err);	// return bits size

///////////////////////////////////////////////////////////////////////////////
// Whole-Number
typedef enum Dz1Asn1PerIntSizePresent
{
	Dz1Asn1PerIntSizePresent_bits,
	Dz1Asn1PerIntSizePresent_octet1,
	Dz1Asn1PerIntSizePresent_octet2,
	Dz1Asn1PerIntSizePresent_indefinite,
	Dz1Asn1PerIntSizePresent_max
} Dz1Asn1PerIntSizePresent;

typedef struct Dz1Asn1PerIntSize
{
	Dz1Asn1PerIntSizePresent	 present;
	union
	{
		size_t					 bits;			// unit : bit
		void					*octet1;
		void					*octet2;
		size_t					 indefinite;	// unit : octet
	} x;
} Dz1Asn1PerIntSize;
#define Dz1Asn1PerIntSize_NULL		{ Dz1Asn1PerIntSizePresent_max, { 0 } }

typedef struct Dz1Asn1PerIntInfo
{
	Dz1Asn1PerIntSize			 size;
	u64_t						 value;
} Dz1Asn1PerIntInfo;
#define Dz1Asn1PerIntInfo_NULL		{ Dz1Asn1PerIntSize_NULL, 0 }

DZ1_CPPLINK bool_t Dz1Asn1CodecPer_mk_cwn( Dz1Asn1PerIntInfo *dst, s64_t src, s64_t lb, s64_t ub, Dz1Asn1PerMode mode, Dz1Error *err); // constrained whole number
DZ1_CPPLINK bool_t Dz1Asn1CodecPer_mk_scwn(Dz1Asn1PerIntInfo *dst, s64_t src, s64_t lb,								   Dz1Error *err); // semi-constrained whole number
DZ1_CPPLINK bool_t Dz1Asn1CodecPer_mk_ucwn(Dz1Asn1PerIntInfo *dst, s64_t src,										   Dz1Error *err); // unconstrained whole number
// Whole-Number
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Normally Small None-Negative-Whole-Number
typedef enum Dz1Asn1PerNormallySmallNNBIPresent
{
	Dz1Asn1PerNormallySmallNNBIPresent_small_num,
	Dz1Asn1PerNormallySmallNNBIPresent_big_num,
	Dz1Asn1PerNormallySmallNNBIPresent_max
} Dz1Asn1PerNormallySmallNNBIPresent;

typedef struct Dz1Asn1PerNormallySmallNNBI
{
	Dz1Asn1PerNormallySmallNNBIPresent	 present;
	union
	{
		u8_t							 small_num;
		Dz1Asn1PerIntInfo				 big_num;
	} x;
} Dz1Asn1PerNormallySmallNNBI;
DZ1_CPPLINK bool_t Dz1Asn1CodecPer_mk_nsnnwn(Dz1Asn1PerNormallySmallNNBI *dst, u64_t src, Dz1Error *err);
// Normally Small None-Negative-Whole-Number
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Length Determinant
// ----------------------------------
// encode length data if necessary and return length what need to be encoded
DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_length_enc(Dz1Asn1Stream *dst, u64_t len, u64_t lb, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err);	// return determinant length
DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_length_dec(Dz1Asn1Stream *src, u64_t lb, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err);				// return determinant length

DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_NS_length_enc(Dz1Asn1Stream *dst, u64_t len, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err);			// return determinant length
DZ1_CPPLINK ssize_t Dz1Asn1CodecPer_NS_length_dec(Dz1Asn1Stream *src, u64_t *_ub, Dz1Asn1PerMode mode, Dz1Error *err);						// return determinant length
// Length Determinant
///////////////////////////////////////////////////////////////////////////////

#endif	// DZ1_ASN1_CODEC_PER_H_LOCAL
