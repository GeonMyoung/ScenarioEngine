#ifndef _ASN_XER_UnString_H_
#define _ASN_XER_UnString_H_


#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "ASN1_XER_STRING.h"


/*UniversalString*/
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_UniversalString(ASN1WorkSpace * ws, UniversalString *tvalue, 
										        ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_UniversalString(ASN1WorkSpace * ws, UniversalString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_UniversalString(ASN1WorkSpace * ws, UniversalString *value,
										        ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_UniversalString(ASN1WorkSpace * ws, UniversalString *value,
											ASNUINT8 *name,ASNINT32 tab_value);

#endif /*_ASN_UnString_H_*/

