#ifndef _ASN1_XER_GraphicString_H
#define _ASN1_XER_GraphicString_H

#include "ASN1_XER_STRING.h"

/*GraphicString */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_GraphicString(ASN1WorkSpace * ws, GraphicString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_GraphicString(ASN1WorkSpace * ws, GraphicString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_GraphicString(ASN1WorkSpace * ws, GraphicString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_GraphicString(ASN1WorkSpace * ws, GraphicString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);

#endif
