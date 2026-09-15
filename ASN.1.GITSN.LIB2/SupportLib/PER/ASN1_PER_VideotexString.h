#ifndef _ASN1_PER_VideotexString_H
#define _ASN1_PER_VideotexString_H

#include "ASN1_PER_STRING.h"

/*VideotexString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
									 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
									   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
									 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_VideotexString (ASN1WorkSpace* ws,VideotexString* value, 
									   Asn1ConsInfo *consinfo);

#endif
