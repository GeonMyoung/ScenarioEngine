#ifndef ASN_PER_Enum_H
#define ASN_PER_Enum_H

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_PER_INTEGER.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ENUMERATED(ASN1WorkSpace * ws, ENUMERATED index, Asn1ConsInfo *conss);
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ENUMERATED_child(ASN1WorkSpace * ws, ENUMERATED index,ASNBOOL extbit, Asn1ConsInfo *conss);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ENUMERATED(ASN1WorkSpace * ws, ENUMERATED index, Asn1ConsInfo *conss);
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ENUMERATED_child(ASN1WorkSpace * ws, ENUMERATED value,ASNBOOL extbit, Asn1ConsInfo *conss);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ENUMERATED(ASN1WorkSpace * ws, ENUMERATED *value, Asn1ConsInfo *conss);
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ENUMERATED_child(ASN1WorkSpace * ws, ENUMERATED *value,ASNBOOL *extbit, Asn1ConsInfo *conss);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ENUMERATED(ASN1WorkSpace * ws, ENUMERATED *value, Asn1ConsInfo *conss);
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ENUMERATED_child(ASN1WorkSpace * ws, ENUMERATED *value,ASNBOOL *extbit, Asn1ConsInfo *conss);


#endif
