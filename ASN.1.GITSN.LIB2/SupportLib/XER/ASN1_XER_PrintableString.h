#ifndef _ASN1_XER_PrintableString_H
#define _ASN1_XER_PrintableString_H

#include "ASN1_XER_STRING.h"

/*PrintableString */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_PrintableString(ASN1WorkSpace * ws, PrintableString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_PrintableString(ASN1WorkSpace * ws, PrintableString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_PrintableString(ASN1WorkSpace * ws, PrintableString *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_PrintableString(ASN1WorkSpace * ws, PrintableString *value,
									        ASNUINT8 *name,ASNINT32 tab_value);

#endif
