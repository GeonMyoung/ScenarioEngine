#ifndef _ASN1_XER_UTCTime_H
#define _ASN1_XER_UTCTime_H

#include "ASN1_XER_STRING.h"
#include "ASN1_XER_SET.h"

/*UTCTime */
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_UTCTime(ASN1WorkSpace * ws, UTCTime *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_UTCTime(ASN1WorkSpace * ws, UTCTime *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_UTCTime(ASN1WorkSpace * ws, UTCTime *value,
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_UTCTime(ASN1WorkSpace * ws, UTCTime *value,
									ASNUINT8 *name,ASNINT32 tab_value);

#endif
