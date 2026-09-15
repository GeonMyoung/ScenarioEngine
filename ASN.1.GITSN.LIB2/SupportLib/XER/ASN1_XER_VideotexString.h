#ifndef _ASN1_XER_VideotexString_H
#define _ASN1_XER_VideotexString_H

#include "ASN1_XER_STRING.h"

/*VideotexString */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_VideotexString(ASN1WorkSpace * ws, VideotexString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_VideotexString(ASN1WorkSpace * ws, VideotexString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_VideotexString(ASN1WorkSpace * ws, VideotexString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_VideotexString(ASN1WorkSpace * ws, VideotexString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);

#endif
