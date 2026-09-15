#ifndef _ASN1_XER_VisibleString_H
#define _ASN1_XER_VisibleString_H

#include "ASN1_XER_STRING.h"

/*VisibleString */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_VisibleString(ASN1WorkSpace * ws, VisibleString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_VisibleString(ASN1WorkSpace * ws, VisibleString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_VisibleString(ASN1WorkSpace * ws, VisibleString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_VisibleString(ASN1WorkSpace * ws, VisibleString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);

#endif
