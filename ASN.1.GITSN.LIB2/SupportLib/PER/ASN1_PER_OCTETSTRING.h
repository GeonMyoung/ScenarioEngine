#ifndef _ASN_PER_Octstr_H_
#define _ASN_PER_Octstr_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_PER_STRING.h"


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, 
									    Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value,
									    Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, 
										  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value,
										  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_OCTETSTRING_Value(ASN1WorkSpace* ws,OCTETSTRING* value,
									    ASNUINT32 length,struct PER_Flag *per_flag,
									    ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_OCTETSTRING_Value(ASN1WorkSpace* ws,OCTETSTRING* value,
									    ASNUINT32 length,struct PER_Flag *per_flag,
									    ASN1PERAlign Align_Flag);

#endif
