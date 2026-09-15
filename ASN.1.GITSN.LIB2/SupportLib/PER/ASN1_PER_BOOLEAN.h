#ifndef _ASN_PER_BOOL_H_
#define _ASN_PER_BOOL_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../TOOL/ASN1_Operate_Byte.h"



ASN1_CPPLINK ASNINT32  ASN1_PER_Align_Enc_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo);


#endif /*_ASN_BOOL_H_*/



