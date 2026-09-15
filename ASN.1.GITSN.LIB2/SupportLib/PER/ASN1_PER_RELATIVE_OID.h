#ifndef _ASN_PER_RELATIVE_OID_H_
#define _ASN_PER_RELATIVE_OID_H_
/*
  Name: Relative-oid
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode Relative-oid
*/
#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../PER/ASN1_PER_SET.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo);


#endif /*_ASN_RELATIVE_OID_H_*/

