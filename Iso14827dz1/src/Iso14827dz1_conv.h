#ifndef ISO14827DZ1_CONV_H_LOCAL
#define ISO14827DZ1_CONV_H_LOCAL

#include <Iso14827dz1.h>


#if defined(GITSN_GENERAL_ASN_TOOL)

#include "Iso14827dz1_assistGeneralAsn.h"

DZ1_CPPLINK Dz1Error Iso14827C2CAuthMsg_fromASN(Iso14827C2CAuthMsg **dst, C2CAuthenticatedMessage_t *src);
DZ1_CPPLINK Dz1Error Iso14827C2CAuthMsg_toASN(C2CAuthenticatedMessage_t **dst, Iso14827C2CAuthMsg *src);


#elif defined(GITSN_NEW_ASN_TOOL)

#include <ISO14827_1.h>
#include <ISO14827_2.h>

DZ1_CPPLINK Dz1Error Iso14827C2CAuthMsg_toASN(C2CAuthenticatedMessage **dst, Iso14827C2CAuthMsg *src, ASN1WorkSpace *ws);
DZ1_CPPLINK Dz1Error Iso14827C2CAuthMsg_fromASN(Iso14827C2CAuthMsg **dst, C2CAuthenticatedMessage *src);

DZ1_CPPLINK Dz1Error Iso14827DatexDataPacket_toASN(DatexDataPacket **dst, Iso14827DatexDataPacket *src, ASN1WorkSpace *ws);
DZ1_CPPLINK Dz1Error Iso14827DatexDataPacket_fromASN(Iso14827DatexDataPacket **dst, DatexDataPacket *src);

#endif

#endif