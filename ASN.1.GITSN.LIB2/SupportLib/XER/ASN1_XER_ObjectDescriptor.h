#ifndef _ASN1_XER_ObjectDescriptor_H
#define _ASN1_XER_ObjectDescriptor_H

#include "ASN1_XER_STRING.h"

/*IA5String */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ObjectDescriptor(ASN1WorkSpace * ws, ObjectDescriptor *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ObjectDescriptor(ASN1WorkSpace * ws, ObjectDescriptor *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ObjectDescriptor(ASN1WorkSpace * ws, ObjectDescriptor *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ObjectDescriptor(ASN1WorkSpace * ws, ObjectDescriptor *value,
									        ASNUINT8 *name,ASNINT32 tab_value);


#endif
