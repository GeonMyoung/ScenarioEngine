#ifndef _ASN_PER_OID_H_
#define _ASN_PER_OID_H_
/*
  Name: OBJECT IDENTIFIER
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode OBJECT IDENTIFIER
*/
#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../PER/ASN1_PER_STRING.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo);


#endif /*_ASN_ROID_H_*/

