#ifndef DZ1_ASN1_TYPES_H_LOCAL
#define DZ1_ASN1_TYPES_H_LOCAL

#include <dz1_asn1_types.h>

typedef enum tag_Dz1Asn1Enum
{
	tag_Dz1Asn1Enum_first = 0xFFFFFFFF
} tag_Dz1Asn1Enum;

DZ1_CPPLINK bool_t	 Dz1Asn1Tag_isVoid(Dz1Asn1Tag *p);
DZ1_CPPLINK bool_t	 Dz1Asn1Tag_isEndOfContents(Dz1Asn1Tag *tag);
DZ1_CPPLINK bool_t	 Dz1Asn1Tag_isCompatible(Dz1Asn1Tag *a, Dz1Asn1Tag *b);

DZ1_CPPLINK bool_t	_Dz1Asn1WipOpenTypeList_addOpenType(Dz1Asn1WipOpenTypeList *dst, u32_t order, Dz1Asn1WipOpenType **_data, Dz1Error *err);
DZ1_CPPLINK bool_t	 Dz1Asn1WipOpenTypeList_addOpenType(Dz1Asn1WipOpenTypeList *dst, Dz1Asn1WipOpenType **_data, Dz1Error *err);

DZ1_CPPLINK bool_t	 Dz1Asn1WipOid_append(Dz1Asn1WipOid *dst, u32_t arc, Dz1Error *err);
DZ1_CPPLINK ssize_t	 Dz1Asn1_encOidArc(Dz1ElasticBuf *dst, u64_t v, Dz1Error *err);

#endif
