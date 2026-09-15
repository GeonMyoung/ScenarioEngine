#ifndef DZ1_ASN1_CODEC_STREAM_H
#define DZ1_ASN1_CODEC_STREAM_H

#include <dz1_elastic_buf.h>

#define DZ1_ASN1_STREAM_QUEUE_TYPE			u32_t
typedef struct Dz1Asn1Stream
{
	DZ1_ASN1_STREAM_QUEUE_TYPE	 ingress;
	s32_t						 ingress_bits;

	Dz1ElasticBuf		*elb;

	DZ1_ASN1_STREAM_QUEUE_TYPE	 egress;
	s32_t						 egress_bits;
} Dz1Asn1Stream;

DZ1_CPPLINK Dz1Asn1Stream	*Dz1Asn1Stream_new(u32_t frag_size, Dz1Error *err);
DZ1_CPPLINK void			 Dz1Asn1Stream_del(Dz1Asn1Stream *p);
static __inline__ void		 Dz1Asn1Stream_delAndSetNull(void *pptr)
{
	Dz1Asn1Stream **p = (Dz1Asn1Stream **)pptr;
	if (p != NULL)
	{
		Dz1Asn1Stream_del(*p);
		*p = NULL;
	}
}

DZ1_CPPLINK bool_t Dz1Asn1Stream_pushBits(Dz1Asn1Stream *dst, u8_t *bits, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushBitsI64(Dz1Asn1Stream *dst, u64_t src, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushBitsI32(Dz1Asn1Stream *dst, u32_t src, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushBitsI16(Dz1Asn1Stream *dst, u16_t src, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushBit1(Dz1Asn1Stream *dst, bool_t bit, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushAlign(Dz1Asn1Stream *dst, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Asn1Stream_pushOctet(Dz1Asn1Stream *dst, u8_t octet, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_pushOctets(Dz1Asn1Stream *dst, u8_t *octets, u32_t octets_len, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Asn1Stream_popOctets(Dz1Asn1Stream *src, u8_t *buf, u32_t buf_octet_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popOctet(Dz1Asn1Stream *src, u8_t *buf, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBits(Dz1Asn1Stream *src, u8_t *bits_buf, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBitsI64(Dz1Asn1Stream *src, u64_t *dst, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBitsI32(Dz1Asn1Stream *src, u32_t *dst, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBitsI16(Dz1Asn1Stream *src, u16_t *dst, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBitsI8(Dz1Asn1Stream *src, u8_t *dst, s32_t bits_len, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Asn1Stream_popBit1(Dz1Asn1Stream *src, bool_t *bit, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1Asn1Stream_popAlign(Dz1Asn1Stream *src, Dz1Error *err);


#endif // DZ1_ASN1_CODEC_STREAM_H
