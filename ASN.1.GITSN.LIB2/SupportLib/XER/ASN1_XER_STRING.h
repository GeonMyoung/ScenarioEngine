#ifndef _ASN1_XER_STRING_H_
#define _ASN1_XER_STRING_H_

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "ASN1_XER_Name.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *value,
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *value,
									ASNUINT8 *name,ASNINT32 tab_value);


#endif /*_ASN1_XER_STRING_H_*/
