#ifndef _ASN1_XER_NumericString_H
#define _ASN1_XER_NumericString_H

#include "ASN1_XER_STRING.h"

/*NumericString */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_NumericString(ASN1WorkSpace * ws, NumericString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_NumericString(ASN1WorkSpace * ws, NumericString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_NumericString(ASN1WorkSpace * ws, NumericString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_NumericString(ASN1WorkSpace * ws, NumericString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);

#endif
