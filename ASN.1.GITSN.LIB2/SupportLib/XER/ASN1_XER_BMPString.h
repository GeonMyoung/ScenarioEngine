#ifndef _ASN_XER_Bmpstr_H_
#define _ASN_XER_Bmpstr_H_

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "ASN1_XER_STRING.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_BMPString(ASN1WorkSpace * ws, BMPString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_BMPString(ASN1WorkSpace * ws, BMPString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_BMPString(ASN1WorkSpace * ws, BMPString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_BMPString(ASN1WorkSpace * ws, BMPString *value,
											ASNUINT8 *name,ASNINT32 tab_value);


#endif /*_ASN_Bmpstr_H_*/

