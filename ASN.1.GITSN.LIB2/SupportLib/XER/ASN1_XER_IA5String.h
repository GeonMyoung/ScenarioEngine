#ifndef _ASN1_XER_IA5String_H
#define _ASN1_XER_IA5String_H

#include "ASN1_XER_STRING.h"

/*IA5String */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_IA5String(ASN1WorkSpace * ws, IA5String *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_IA5String(ASN1WorkSpace * ws, IA5String *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_IA5String(ASN1WorkSpace * ws, IA5String *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_IA5String(ASN1WorkSpace * ws, IA5String *value,
									        ASNUINT8 *name,ASNINT32 tab_value);


#endif
