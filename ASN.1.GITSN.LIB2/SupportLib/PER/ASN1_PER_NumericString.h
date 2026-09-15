#ifndef _ASN1_PER_NumericString_H
#define _ASN1_PER_NumericString_H

#include "ASN1_PER_STRING.h"

/*NumericString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_NumericString (ASN1WorkSpace *ws,NumericString *value,
									   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_NumericString (ASN1WorkSpace *ws,NumericString *value,
										 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_NumericString (ASN1WorkSpace *ws,NumericString *value,
									   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_NumericString (ASN1WorkSpace* ws,NumericString* value, 
										 Asn1ConsInfo *consinfo);

#endif
