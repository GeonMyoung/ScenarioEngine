#ifndef _ASN1_XER_GeneralizedTime_H
#define _ASN1_XER_GeneralizedTime_H

#include "ASN1_XER_STRING.h"
#include "ASN1_XER_SET.h"

/*GeneralizedTime */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *value,
												ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *value,
									        ASNUINT8 *name,ASNINT32 tab_value);


#endif
