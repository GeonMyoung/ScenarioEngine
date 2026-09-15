#ifndef ISO14827DZ1_CODEC_H_LOCAL
#define ISO14827DZ1_CODEC_H_LOCAL

#include <dz1_asn1.h>
#include <Iso14827dz1.h>
//#include "Iso14827dz1.h"

#if defined(GITSN_GENERAL_ASN_TOOL)

#include <C2CAuthenticatedMessage.h>

//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decodeBer(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp);
//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encodeBer(C2CAuthenticatedMessage_t *src, u8_t **dst, Dz1Error *errp);

//DZ1_CPPLINK ssize_t Dz1Asn1OctetStr_decodeBer(Dz1Asn1OctetStr **dst, u8_t *src, size_t size, Dz1Error *errp);
//DZ1_CPPLINK ssize_t Dz1Asn1OctetStr_encodeBer(u8_t **dst, Dz1Asn1OctetStr *src, Dz1Error *errp);

#elif defined(GITSN_NEW_ASN_TOOL)

#include "Iso14827dz1_assist.h"

//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decodeBer(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp);
//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encodeBer(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp);

//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decodeUper(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp);
//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encodeUper(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp);

//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_decodeAper(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp);
//DZ1_CPPLINK ssize_t Iso14827C2CAuthMsg_encodeAper(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp);

#include <dz1_gasn_support.h>
#endif

#endif