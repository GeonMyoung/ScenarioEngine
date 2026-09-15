#ifndef _ASN1_XER_GeneralString_H
#define _ASN1_XER_GeneralString_H

#include "ASN1_XER_STRING.h"

/*GeneralString*/
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_GeneralString(ASN1WorkSpace * ws, GeneralString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_GeneralString(ASN1WorkSpace * ws, GeneralString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_GeneralString(ASN1WorkSpace * ws, GeneralString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_GeneralString(ASN1WorkSpace * ws, GeneralString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);


#endif
